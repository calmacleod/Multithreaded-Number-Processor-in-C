Author : Callum MacLeod
Student # : 101109519
Date of Submission : 04-12-2019

Purpose of Software:
    -multiFactor.c
        -Accept a binary file with unsigned long ints and figure out how many prime factors all of the number have in total using forking and morphing
    -prime_threads.c
        -Accepts a binary file with unsigned long and specified line numbers and computes the sum of all the number of prime factors of all the numbers
         using threads.
    -numPrimeFactors.c
        -Accepts a unsigned long as an argument and determines how many prime factors it has
    
Organization:
    numPrimeFactors.c is needed for multiFactor to run, while prime_threads is able to run on it's own

Issues / Limitations:
    - For Part II of the assignment I did not check to make sure the requested numbers were inside the range
        -It was not requested as part of the specs so I assumed that the input entered would be within range
    
Extra Information:
    - I implemented the Bonus marks on Part I and Part II 
    - I tried to account for as many NULL checks as I could, but it's very possible I missed a couple

Running The Software:
    - To generate multiSpawn
        -Run : make -f Makefile1

    - And to Run multiSpawn
        -Run : ./multiSpawn file.bin

    - To genereate multiThread
        -Run : make -f Makefile2

    - And to Run multiThread
        -Run : ./multiThread file.bin [arguments...]