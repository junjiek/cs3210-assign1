#include <stdio.h> 
#include <time.h>

#define KB 1024
#define MB 1024 * KB
#define SIZE 32 * KB
#define REPS 512 * MB // times to access/modify memory
#define MAX_STRIDE 512 // in bytes, should be multiple of 4 (sizeof(int))

long long wall_clock_time();
 
int main() {
	long long start, end;
	int lengthMod;
	float timeTaken;

	int *data = new int[SIZE/sizeof(int)]; 
	lengthMod = SIZE/sizeof(int) - 1;

	// repeatedly access/modify data, varying the STRIDE
	for (int s = 4; s <= MAX_STRIDE/sizeof(int); s*=2) {
		start = wall_clock_time();
		for (unsigned int k = 0; k < REPS; k++) {
			for (unsigned int l = 0; l < REPS; l++) {
				data[(l * s) & lengthMod]++;
			}	
		}
		end = wall_clock_time();
		timeTaken = ((float)(end - start))/1000000000;
		printf("%d, %1.2f \n", s * sizeof(int), timeTaken);
	}

	// cleanup
	delete[] data;
}

/*******************************************************
 * Helpers
 ******************************************************/
long long wall_clock_time() {
	#ifdef __linux__
		struct timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);
		return (long long)(tp.tv_nsec + (long long)tp.tv_sec * 1000000000ll);
	#else 
	#warning "Your timer resolution may be too low. Compile on linux"
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (long long)(tv.tv_usec * 1000 + (long long)tv.tv_sec * 1000000000ll);
	#endif
}