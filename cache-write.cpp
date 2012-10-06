#include <stdio.h> 
#include <time.h>

#define KB 1024
#define MB 1024 * KB
#define SIZE 16 * MB
#define WRITES_BASE 32 * MB // the base line, should be a small number compared to WRITES
#define WRITES 32 * WRITES_BASE // times to write repeatedly 


long long wall_clock_time();

int main() {
	long long start, end;
	int lengthMod;
	float timeBaseLoop, timeManyLoop, timeBase, timeMany;
	int caches[] = { 16 * KB, 128 * KB, 2 * MB }; // less than size of each cache to ensure it fits 
	int tmp;
	// initialize large data
	int *data = new int[SIZE/sizeof(int)];
	int *dummy = new int[SIZE/sizeof(int)];
	for (int i = 0; i < SIZE/sizeof(int); i++)
		dummy[i] = i;

	// record time for a loop of size `WRITES_BASE`
	start = wall_clock_time();
	for (unsigned int i = 0; i < WRITES_BASE; i++) {}
	end = wall_clock_time();
	timeBaseLoop = ((float)(end - start))/1000000000;

	// record time for a loop of size `WRITES`
	start = wall_clock_time();
	for (unsigned int i = 0; i < WRITES; i++) {}
	end = wall_clock_time();
	timeManyLoop = ((float)(end - start))/1000000000;

	// for each cache level
	for (int i = 0; i < sizeof(caches)/sizeof(int); i++) {
		lengthMod = caches[i]/sizeof(int) - 1;

		// record time to access once and write `WRITES_BASE` time 
		start = wall_clock_time();
		for (unsigned int j = 0; j < WRITES_BASE; j++) 
			data[(j * 16) & lengthMod] = i + j;
		end = wall_clock_time();

		// force cache flush
		tmp = 0;
		for (unsigned int j = 0; j < WRITES; j++)
			tmp += dummy[j & (SIZE/sizeof(int)-1)];

		timeBase = ((float)(end - start))/1000000000;
		//timeBase -= timeBaseLoop; // minus off time for loop

		// record time to access once and write `WRITES` times
		start = wall_clock_time();
		for (unsigned int j = 0; j < WRITES; j++) 
			data[(j * 16) & lengthMod] = i + j;

		// force cache flush
		tmp = 0;
		for (unsigned int j = 0; j < WRITES; j++)
			tmp += dummy[j & (SIZE/sizeof(int)-1)];

		end = wall_clock_time();
		timeMany = ((float)(end - start))/1000000000;
		//timeMany -= timeManyLoop; // minus off time for loop


		// if average to write `WRITES_BASE` time vs `WRITES` times is about the same 
		// (minus time to execute loop of same size), it should be a write back
		printf("%d, %1.2f, %.2f (%.2f) \n", caches[i]/1024, timeBase, timeMany, (timeMany/timeBase)/(WRITES/WRITES_BASE));
	}

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