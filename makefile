all: matrix cache cache-write

matrix: matrix.cpp
	g++ -O3 -msse3 -fstrict-aliasing matrix.cpp -o matrix -lrt

cache: cache.cpp
	g++ -O3 cache.cpp -o cache -lrt

cache-write: cache-write.cpp
	g++ -O3 cache-write.cpp -o cache-write -lrt

cache-l1-line: cache-l1-line.cpp
	g++ -O3 cache-l1-line.cpp -o cache-l1-line -lrt