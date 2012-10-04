all: matrix cache

matrix:
	g++ -O3 -msse3 -fstrict-aliasing matrix.cpp -o matrix -lrt

cache: 
	g++ -O3 cache.cpp -o cache -lrt
