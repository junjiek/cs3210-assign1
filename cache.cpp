#include <stdio.h> 
#include <time.h>

#define KB 1024
#define MB 1024 * KB
#define SIZE 12 * MB
#define REPS 512 * MB // times to access/modify memory
#define TIMES 3 // times to repeat experiment to get "average"

long long wall_clock_time();

int main() {
	long long start, end;
	int lengthMod;
	float totalTime;
	unsigned long long tmp = 0;
	// possible cache sizes to test for
	int sizes[] = {
		1 * KB, 4 * KB, 8 * KB, 16 * KB, 32 * KB, 64 * KB, 128 * KB, 256 * KB, 
        512 * KB, 1 * MB, 2 * MB, 3 * MB, 4 * MB, 6 * MB, 8 * MB, 10 * MB, 12 * MB
	};
	// init large data 
	int *data = new int[SIZE/sizeof(int)];
	for (int i = 0; i < SIZE/sizeof(int); i++)
		data[i] = i;
	// for each possible cache size to test for
	for (int i = 0; i < sizeof(sizes)/sizeof(int); i++) {
		lengthMod = sizes[i]/sizeof(int) - 1;
		
		// repeatedly access/modify data
		totalTime = 0;
		for (int j = 0; j < TIMES; j++) {
			start = wall_clock_time();
			for (unsigned int k = 0; k < REPS; k++) {
				tmp += (data[(k * 16) & lengthMod] & SIZE);
			}
			end = wall_clock_time();
			totalTime += ((float)(end - start))/1000000000;
		}
		printf("%d, %1.2f \n", (sizes[i] / (1 * KB)), totalTime / TIMES);
		
	}

	FILE *debug = fopen("/dev/null", "w");
	fprintf(debug, "%d", tmp);

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