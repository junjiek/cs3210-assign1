all: matrix cache

matrix: matrix.cpp
	g++ -O3 -msse3 -fstrict-aliasing matrix.cpp -o matrix -lrt

cache: cache.cpp
	g++ -O3 cache.cpp -o cache -lrt

cache-write: cache-write.cpp
	g++ -O3 cache-write.cpp -o cache-write -lrt