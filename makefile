all: matrix cache cache-write cache-l1-line

matrix: matrix.cpp
	g++ -O3 -msse3 -fstrict-aliasing matrix.cpp -o matrix -lrt

cache-test: cache-test.cpp
	g++ -O3 cache-test.cpp -o cache-test

cache-write: cache-write.cpp
	g++ -O3 cache-write.cpp -o cache-write -lrt

cache-l1-line: cache-l1-line.cpp
	g++ -O3 cache-l1-line.cpp -o cache-l1-line -lrt