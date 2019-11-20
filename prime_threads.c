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

/***************************************************************/
// Global Variables
unsigned long totalNumPrimeFactors = 0;		// global value that holds the final result
unsigned long *recordsToProcess = NULL;     // array that will hold al the numbers to be processed
int numRecords = 0;                         // number of records in the array recordsToProcess


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
Purpose: the main function of the threads

void *threadMain(/*add parameters as needed */)

{

    // add code 
}

/*************************************************************************/
int main(int argc, char ** argv)
{
    pthread_t tid[NUM_THREADS];

    
    // check command line is correct - if not show how to use the program
    
    // init mutex 


    // read the records from the file


    // initialize the threads


    // wait for the threads to terminate

    // destroy the mutex 
    
    
    // print the numer of prime factors

}




