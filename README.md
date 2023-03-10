# Average temperature parser

Assignment 2 for UVic CSC360, Introduction to Operating Systems
Samuel Ngai, V00917462

## How to run:
Compile data_av with "*make*".
Execute with "*./data_av*" or "*./data_av -m*" for multithreading mode.

This program makes use of threads to parse maximum and minimum yearly temperatures of ten data files given in our *data_files* folder to calculate the overall maximum, minimum, and average overall temperatures of each city.

In singlethreaded mode, we simply utilize a single thread to parse a file, and then reuse the same thread to parse the next. 

In multithreaded mode, we utilize ten threads (one for each city). To avoid overlapping of editing our global variables, we utilize mutexes as well as critical sections in our code so that at most only one thread can be calculating, updating, and printing our global maximum, minimum, and average temperatures.

In addition to simply calculating maximum, minimum, and average temperatures and entry counts, we calculate the number of clock cycles our system takes to complete all our tasks. We achieve this by taking the number of clock cycles at the beginning and subtracting it from our ending number of clock cycles. We then divide this number by *CLOCKS_PER_SEC* to obtain the total time taken for our computation.