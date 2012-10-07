#include <stdio.h> 
#include <time.h>

#define KB 1024
#define MB 1024 * KB
#define SIZE 4 * MB
#define REPS 256 * MB // times to access/modify memory
#define MAX_STRIDE 512 // in bytes, should be multiple of 4 (sizeof(int))
#define TIMES 6 // times to run to get average

long long wall_clock_time();
 
int main() {
	long long start, end;
	int lengthMod;
	float totalTime;
	int tmp = 0;

	int *data = new int[SIZE/sizeof(int)]; 
	lengthMod = SIZE/sizeof(int) - 1;

	// repeatedly access/modify data, varying the STRIDE
	for (int i = 4; i <= MAX_STRIDE/sizeof(int); i*=2)  {
		totalTime = 0;
		for (int j = 0; j < TIMES; j++) {
			start = wall_clock_time();
			for (unsigned int k = 0; k < REPS; k++) {
				tmp += data[(k * i) & lengthMod];
			}
			end = wall_clock_time();
			totalTime += ((float)(end - start))/1000000000;
		}
		printf("%d, %1.2f \n", i * sizeof(int), totalTime/TIMES);
	}

	FILE *debug = fopen("/dev/null", "w");
	fprintf(stdout, "%d", tmp);

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