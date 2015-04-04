all: matrix cache-test cache-write cache-l1-line

matrix: matrix.cpp
	g++ -O3 -msse3 -fstrict-aliasing matrix.cpp -o matrix

cache-test: cache-test.cpp
	g++ -O3 cache-test.cpp -o cache-test

cache-test-2: cache-test-2.cpp
	g++ cache-test-2.cpp -o cache-test-2

cache-write: cache-write.cpp
	g++ -O3 cache-write.cpp -o cache-write

cache-l1-line: cache-l1-line.cpp
	g++ -O3 cache-l1-line.cpp -o cache-l1-line 


cache-line: cache-line.cpp
	g++ cache-line.cpp -o cache-line 