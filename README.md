CS3210 - Parallel Computing - Assignment 1
==========================================

1. Cache Profiling
------------------

### Files 

- `cache.cpp`: for cache levels & size (1 & 2)
- `cache-write.cpp`: for cache write policy (3)
- `cache-l1-line.cpp`: for L1 cache line size (4)

### Compilation & execution 

All files are compiled by `make {filename}` and executed like `./{filename}`, 
where `{filename}` is the filename without extension. For example

    make cache && ./cache

### Output

The output is a csv meant as input into a spreadsheet to plot a graph

An Example: 

	1, 0.52 
	4, 0.53 
	8, 0.52 
	16, 0.52 
	32, 0.53 
	...

Where in each row, the 1st value is the test size (KB), and the 2nd the time (s)


2. Matrix Multiplication Optimization
-------------------------------------

Only file is `matrix.cpp`. Compiled & run in a similar way as part 1. 

    make matrix && ./matrix

Output like

	SIMD Matrix multiplication took 0.36 seconds
	Unoptimized Matrix multiplication took 7.65 seconds
	SUCCESS: Both optimized and unoptimized gave same results

The input size defaults to `1024`, and can be changed by changing line 1 (or something like below)

    #define SIZE 1024


------------------------

For information on methodology of this "experiments" see [Google Doc][1]

[1]: https://docs.google.com/document/d/1LtDiZVuN0qqxFUWs6naD94Hzn1Q2qaqRdlEluAuAlpQ/edit#heading=h.c0boq1pg8xsy