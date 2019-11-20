/* 
File is numFactors.c

Purpose:
a program that returns the number of prime factors that a given number has.  For example 24 will have 4 prime 
factors 2, 2, 2, 3 because 2*2*2*3 == 24

input:
number - a positive unsigned long integer  entered via the command line parameters.  For example numFactors 1234

output:
none

return:
number of prime factora excluding the 1 for example when called with 5 the program returns 1 
-2 - if the command line parameter is not correct 

Assumption:
the program does not check if the number is a positive long integer


Notice:
Code can be used only for the assignment.  Other usages are not allowed

Copyright 2018 Doron Nussbaum
*/ 

/**************************************************************/
// INCLUDE FILES
//
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <unistd.h>


/*************************************************************/
// PROTYPES
//
int numPrimeFactors(unsigned long number);


/*************************************************************/


int main(int argc, char *argv[])

{
	int i;

	unsigned long number;
	int rc;

	if (argc < 2) return(-2);
	else number = strtoul(argv[1],NULL, 0);
	rc = numPrimeFactors(number);
	//printf("number = %lu factors = %d\n", number, rc);
	exit(rc);
}


/*************************************************************/
/*
Purpose: retrurn the number of factors of a given unsigned long integer 
input:
number - the number to be checked

return:
number of factora excluding the 1 for example when called with 5 the program returns 1 
-2 - if the command line parameter is not correct 
*/ 

/*************************************************************/
int numPrimeFactors(unsigned long number)
{
	unsigned long i;
	unsigned long quot;
	int numFactors = 0;

	// boundary conditions
	if (number == 1) return(0);
	if (number == 2 || number == 3) return(1);

	// check for the first factor 
	for (i = 2; i <= number; i++) {
		if (i % 1000 == 0) {
			if (number / i == 1) {
				return(1);   // cannot have any more factrs other than self therefore return(1);
			}
		}
		if (number % i == 0) {
			quot = number / i;
			if (quot == 1) {
				return(1);   // cannot have any more factrs other than self
			}
			return(1 + numPrimeFactors(quot));
		}
	}
	return(0);
}

