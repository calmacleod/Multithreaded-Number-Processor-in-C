#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BINARY_LENGTH 10


/*

PURPOSE: Write program that will spawn multiple child processes. Each child process
will morph itself into the numPrimeFactor program, The parent program will wait until 
all the cild process have completed their work and then print shte ottal number of prime factors
of ALL of the input numbers

ASSUMPTIONS: Binary file exists, and contains at least 10 unsigned long numbers.
                -program only needs to process first 10, anything after is bonus



-Accepts binary file name as a single command line parameter

PROTOTYPES

Prototype int morph(char *number);


*/

int morph(char * number);


int main(int argc, char * argv[]){
    
    //Only 1 argument supplies
    if(argc == 1){
        printf("Please enter a binary file to be tested\nProper useage: ./multiFactor file \n");
        exit(1);
    }


    FILE *primeNum;
    
    //If NULL then file doesn't exist
    if( (primeNum = fopen(argv[1], "rb")) == NULL){
        printf("File does not exist please try again with valid file\n");
        exit(1);
    }

    //Determine Size
    fseek(primeNum, 0, SEEK_END);
    int size = ftell(primeNum);
    size/=sizeof(unsigned long);
    fseek(primeNum, 0, SEEK_SET);

    //Allocate memory for numbers
    unsigned long * arr = malloc(sizeof(unsigned long) * size);

    fread(arr, sizeof(unsigned long), size, primeNum);
    
    fclose(primeNum);
    //Finished reading file


    //Create all of our child proccesses
    for(int i = 0; i<size; i++){
        char buffer[20];
        sprintf(buffer, "%lu", arr[i]);

        if( morph(buffer) == -1){
            printf("Error has occured in one of the proccesses\n");
            exit(1);
        }
    }

    //Wait for all child proccesses to finish, and everytime one does, add it to the sum
    int wpid, status, sum;
    sum = 0;
    while((wpid = waitpid(-1,&status,0)) > 0){
        sum += WEXITSTATUS(status);
    }

    printf("Children Finished, SUM = %d \n", sum);
    free(arr);
    exit(0);
}


int morph(char * number){
    
    //Make a permanent string containing file name
    char buff[80];

    strcpy(buff, "./numPrimeFactors");

    //Make arguments array
    char * args[3];
    args[0] = "numPrimeFactors";
    args[1] = number;
    args[2] = NULL;

    //Fork program
    int childPID = fork();

    //If it is the child program, then morph into numPrimeFactors
    if(childPID == 0){
        execvp(buff, args);
        //Child process shouldn't reach here, and if it does that means something went wrong so return -1
        return -1;
    }
    else{
        return 0;
    }
    
    
    
}