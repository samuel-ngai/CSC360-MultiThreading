# Average temperature parser

Assignment 2 for UVic CSC360, Introduction to Operating Systems
Samuel Ngai, V00917462

## How to run:
Compile data_av.c with "*make*".
Execute with "*./data_av*" or "*./data_av -m*" for multithreading mode.

## Implementation
This program makes use of threads to parse maximum and minimum yearly temperatures of ten data files given in our *data_files* folder to calculate the overall maximum, minimum, and average overall temperatures of each city. The number of total entries we have for each city can also be calculated by taking the over line count of our file, subtracting one for our header, and multiplying the value by two for the maximum and minimum temperatures present in each line.

In singlethreaded mode, we simply utilize a single thread to parse a file, and then reuse the same thread to parse and calculate the next. 

In multithreaded mode, we utilize ten threads (one for each city). To avoid overlapping of editing our global variables, we utilize mutexes as well as critical sections in our code so that at most only one thread can be calculating, updating, and printing our global maximum, minimum, and average temperatures.

In addition to simply calculating maximum, minimum, and average temperatures and entry counts, we calculate the number of clock cycles utilizing  *clock()* and the overall time our system takes to complete all our tasks. We achieve this by taking the number of clock cycles at the beginning of our regular or multithreading tasks and subtracting it from our ending number of clock cycles. We then divide this number by *CLOCKS_PER_SEC* to obtain the total time taken for our computation.

## Observations (Execution time/clock cycles, results)

When observing the execution time in clocks, this number (implemented as start_t, end_t, total_t, and elapsed_t) varies differently whenever you execute it. This program has been tested on Windows, MacOS, and Linux operating systems. 

### MacOS, Intel i5 Quad-Core CPU

When executing with regular mode, the range of values for our elapsed time is ~110000 clocks and a total time of ~0.11s when dividing our total clocks by *CLOCKS_PER_SEC*

Executing with multitheading mode gives us roughly ~120000 clocks and a total time of ~0.12s when dividing our total clocks by *CLOCKS_PER_SEC*

### Linux, UVic Linux Server, specs unknown

When executing with regular mode, the range of values for our elapsed time is ~165000 clocks and a total time of ~0.165s when dividing our total clocks by *CLOCKS_PER_SEC*

Executing with multitheading mode gives us roughly ~200000 clocks and a total time of ~0.2s when dividing our total clocks by *CLOCKS_PER_SEC*

### Windows, AMD Ryzen 5 3600 6-Core 12-Thread CPU

When executing with regular mode, the range of values for our elapsed time is ~110 clocks and a total time of ~0.11s when dividing our total clocks by *CLOCKS_PER_SEC*

Executing with multitheading mode gives us roughly ~114 clocks and a total time of ~0.114s when dividing our total clocks by *CLOCKS_PER_SEC*

### Conclusion

Theoretically, multithreading should be faster than regular mode, which uses a single main thread for our operations, but when testing our program on different operating systems, majority of them end up having our multithreading solution having more clock cycles than regular mode. However, this depends on many factors. There may be ways our program can be implemented better or a better way to parallelize our tasks so that every task can truly be running in parallel with multiple threads.

Differences in thread execution can also be noticed by the different orderings that our city data prints at. With regular mode, we can expect our results to appear in the exact order that we pass through our filepaths but with multithreading mode, the ordering varies. This may be caused by different threads being created and going into our critical sections before its predecessors can.
