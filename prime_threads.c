// file is prime_threads.c
/********************************************************************/


/****************************************************************/
// Includes

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

/***************************************************************/
// Structures


// holds the thread information for each thread
typedef struct threadData { 
    pthread_t thread_id;			// system thread id
    int tid;                        // inernal id assigned by the program
} ThreadData; 


/******************************************************************/
// Define


#define NUM_THREADS 5


/******************************************************************/
// Function Prototypes

int numPrimeFactors(unsigned long number);

void handlesignal(int);

/***************************************************************/
// Global Variables
unsigned long totalNumPrimeFactors = 0;		// global value that holds the final result
unsigned long *recordsToProcess = NULL;     // array that will hold al the numbers to be processed
int numRecords = 0;                         // number of records in the array recordsToProcess

int finishedThreads = 0;

pthread_mutex_t sumLock, arrayLock, toProcessLock, finishedLock; 
int mutexCount = 4;

/*************************************************************/
/*
Purpose compute the number of prime factors of a given number
input:
number - the number to be processed

output: 
None

Return:
the number of prime factors of number
*/
int numPrimeFactors(unsigned long number)
{
    unsigned long i;
    unsigned long quot;
    int numFactors = 0;

    // base case
    if (number == 1) return(0);
    if (number == 2 || number == 3) return(1);

    // check for the first factor until integer is less then number 
    for (i = 2; i <= number; i++) {
        if (i % 1000 == 0) {        
            if (number / i == 1) return(1);   // cannot have any more factrs other than self
        }
        if (number % i == 0) {
            quot = number / i;
            if (quot == 1) return(1);   // cannot have any more factrs other than self
            numFactors = 1 + numPrimeFactors(quot);
            return(numFactors);
        }
    }
    return(0);
}
/*************************************************************************/
//Purpose: the main function of the threads

void *threadMain(void *argvp)
{
    while(1){

        //Var to hold value from array
        unsigned long valToProcess;

        //Lock number of records to be processed
        pthread_mutex_lock(&toProcessLock);

        //Only process if there are more values to be processed
        if(numRecords > 0){

            
            //Get the value from the array
            pthread_mutex_lock(&arrayLock);

            valToProcess = recordsToProcess[numRecords-1];
            numRecords--;

            //Unlock process count
            pthread_mutex_unlock(&toProcessLock);

            //Unclock array of values
            pthread_mutex_unlock(&arrayLock);

        }

        else{
            pthread_mutex_unlock(&toProcessLock);
            break;
        }

        int returnVal = numPrimeFactors(valToProcess);

        pthread_mutex_lock(&sumLock);
        totalNumPrimeFactors += returnVal;
        pthread_mutex_unlock(&sumLock);

    }
    
    //Increase whenever a thread finishes
    pthread_mutex_lock(&finishedLock);
    finishedThreads++;
    pthread_mutex_unlock(&finishedLock);


}

/*************************************************************************/
int main(int argc, char ** argv)
{

    signal(SIGUSR1, handlesignal);

    //Holds all threads;
    pthread_t tid[NUM_THREADS];


    if(argc <= 2){
        printf("Proper Usage: ./prime_threads filename.bin numeric_args\n");
        exit(1);
    }


    //Open file
    FILE * primeNum;

    if((primeNum = fopen(argv[1], "rb")) == NULL){
        printf("Error opening file.. Please try again\n");
    }

    int iden = atoi(argv[2]);

    //If -1 is the first numeric argument then read all the numbers
    if(iden == -1){
        fseek(primeNum, 0, SEEK_END);
        int size = ftell(primeNum);
        size/=sizeof(unsigned long);
        fseek(primeNum, 0, SEEK_SET);

        numRecords = size;
        recordsToProcess = malloc(sizeof(unsigned long) * size);

        fread(recordsToProcess, sizeof(unsigned long), size, primeNum);
    }

    //Other wise read only the ones specified
    else{
        recordsToProcess = malloc(sizeof(unsigned long) * (argc-2));

        numRecords = argc-2;

        for(int i = 0; i<argc-2; i++){
            int pos1 = atoi(argv[i+2]);
            int pos2 = pos1 * sizeof(unsigned long);

            fseek(primeNum, pos2, SEEK_SET);
            fread(&recordsToProcess[i], sizeof(unsigned long), 1, primeNum);
        }
    }

    fclose(primeNum);


    //After this point /count/ holds how many numbers we have and /arr/ holds alll of the numbers

    
    //Array to hold all mutex
    pthread_mutex_t mutexArr[4] = {sumLock, arrayLock, toProcessLock, finishedLock};

    //Initalize all my mutex
    for(int i = 0; i<mutexCount; i++){
        if(pthread_mutex_init(&mutexArr[i], NULL)){
            printf("Error occured in init for mutex!\n");
            exit(1);
        }
    }

    //Start the threads
    for(int i = 0; i<NUM_THREADS; i++){
        pthread_create(&tid[i], NULL, threadMain, NULL);
    }

    //Join all the threads
    for(int i = 0; i<NUM_THREADS; i++){
        pthread_join(tid[i], NULL);
    }

    //Destroy all mutex
    for(int i = 0; i<mutexCount; i++){
        pthread_mutex_destroy(&mutexArr[i]);
    }

    //Print Results
    printf("Total number of Prime Factors: %lu\n", totalNumPrimeFactors);

    //Free Memory
    free(recordsToProcess);

    exit(0);
}

void handlesignal(int sig){
    pthread_mutex_lock(&finishedLock);
    printf("So far %d threads have finished and %d are still running\n", finishedThreads, ((NUM_THREADS) - 5));
    pthread_mutex_unlock(&finishedLock);
}


