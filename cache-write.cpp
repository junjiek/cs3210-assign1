#include <stdio.h> 
#include <sys/time.h>

#define KB 1024 // 1 KB = 1024 bytes
#define MB 1024 * KB // 1 MB = 1024 KB
#define SIZE 16 * MB // size of data array
#define REPS 256 * MB // number time times to write

long long wall_clock_time();

int main() {
	
	int sizes[] = { 
		8 * KB, 16 * KB, 32 * KB, 64 * KB, 128 * KB, 256 * KB, 512 * KB,
		1 * MB, 2 * MB, 3 * MB, 4 * MB, 6 * MB, 8 * MB, 10 * MB, 12 * MB
	};
	int lengthMod;
	int *data = new int[SIZE/sizeof(int)];
	int *dummy = new int[SIZE/sizeof(int)];
	for (unsigned int i = 0; i < SIZE/sizeof(int); i++) 
		dummy[i] = i;
	int tmp;
	long long start, end;
	float timeTaken;

	// measure time to write different sizes of data
	for (int i = 0; i < sizeof(sizes)/sizeof(int); i++) {
		lengthMod = sizes[i]/sizeof(int) - 1;

		start = wall_clock_time();

		// write to data
		for (int j = 0; j < REPS; j++) 
			data[(j * 16) & lengthMod] = j;

		// read from other data source to force any write back cache to flush
		for (int j = 0; j < REPS; j++)
		 	tmp += dummy[(j * 16) & lengthMod];

		end = wall_clock_time();
		timeTaken = ((float)(end - start))/1000000000;
		fprintf(stderr, "%d, %1.2f \n", sizes[i]/1024, ((float)(end - start))/1000000000);
	}

	FILE *debug = fopen("1.txt", "w");
	fprintf(debug, "%d", tmp);

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