all: matrix cache-test cache-write cache-l1-line matrix_mul

matrix: matrix.cpp
	g++ -O3 -msse3 -fstrict-aliasing matrix.cpp -o matrix

cache-test: cache-test.cpp
	g++ -O3 cache-test.cpp -o cache-test


cache-write: cache-write.cpp
	g++ -O3 cache-write.cpp -o cache-write

cache-l1-line: cache-l1-line.cpp
	g++ -O3 cache-l1-line.cpp -o cache-l1-line 


cache-line: cache-line.cpp
	g++ cache-line.cpp -o cache-line 

size: size.cpp
	g++ size.cpp -o size

associality: associality.cpp
	g++ associality.cpp -o associality

matrix_mul: matrix_mul.cpp
	g++ -O2 matrix_mul.cpp -o matrix_mul 