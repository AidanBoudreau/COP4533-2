# Programming Assignment 2 - Cache Replacement
Aidan Boudreau  
UFID: 22043059


## Overview
This program simulates FIFO (First In First Out), LRU (Least Recently Used), and OPTFF (Optimal farthest in future) cache replacement.

## Input format
The input file is "input.txt" the structure is that the first line contains two integers containing a space in the middle. The first integer represents the number of caches in the program (k) and the second integer represents the amount of cache requests that the program will make (m).  
The second line is a list of size m that has the cache requests that will be made in the order written (r). Each request is an integer that is seperated by a space.

example input:  
3 5  
1 2 3 4 1

## Compile Program
open terminal and go into the PROGASSIGN2 folder, optionally you can change input.txt to the specifications above, then use command  
g++ main.cpp -o cache

## Run Program
to then run the program use the command  
./cache

## View output
The output will be written into the "output.txt" file where it will display 3 rows showcasing the number of misses that FIFO, LRU, and OPTFF respectively have made.

example output:  
FIFO  : 5  
LRU   : 5  
OPTFF : 4

## Assumptions
The file input always has 2 lines,  
The first line contains exactly k and m,  
The second line contains m values,  
k must be >= 1,  
Requests are seperated by a space,  
Assumes input.txt exists.

## Report
### Question 1

| Input File | k | m | FIFO | LRU | OPTFF |
|-----------|---|---|------|-----|-------|
| File 1 | 3 | 60 | 45 | 50 | 31 |
| File 2 | 4 | 56 | 44 | 48 | 23 |
| File 3 | 5 | 64 | 52 | 56 | 23 |
| File 4 | 4 | 60 | 41 | 32 | 23 |
| File 5 | 3 | 60 | 49 | 43 | 26 |

Try them!  
File 1 requests = 1 2 3 4 1 2 5 1 2 3 4 5 1 2 3 4 1 2 5 1 2 3 4 5 1 2 3 4 1 2 5 1 2 3 4 5 1 2 3 4 1 2 5 1 2 3 4 5 1 2 3 4 1 2 5 1 2 3 4 5  
File 2 requests = 1 2 3 4 5 1 2 6 1 2 3 4 5 6 1 2 3 4 5 1 2 6 1 2 3 4 5 6 1 2 3 4 5 1 2 6 1 2 3 4 5 6 1 2 3 4 5 1 2 6 1 2 3 4 5 6  
File 3 requests = 1 2 3 4 5 6 1 2 7 1 2 3 4 5 6 7 1 2 3 4 5 6 1 2 7 1 2 3 4 5 6 7 1 2 3 4 5 6 1 2 7 1 2 3 4 5 6 7 1 2 3 4 5 6 1 2 7 1 2 3 4 5 6 7  
File 4 requests = 1 2 3 1 4 5 2 1 6 2 1 3 7 2 1 4 8 2 1 5 1 2 3 1 4 5 2 1 6 2 1 3 7 2 1 4 8 2 1 5 1 2 3 1 4 5 2 1 6 2 1 3 7 2 1 4 8 2 1 5  
File 5 requests = 1 2 1 3 1 2 4 1 2 3 5 1 2 4 6 1 2 5 7 1 1 2 1 3 1 2 4 1 2 3 5 1 2 4 6 1 2 5 7 1 1 2 1 3 1 2 4 1 2 3 5 1 2 4 6 1 2 5 7 1  

