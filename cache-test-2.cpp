#include <stdio.h> 
#include <sys/time.h>
#include <cstdlib>

#define KB 1024         // 1 KB = 1024 bytes
#define MB 1024 * KB    // 1 MB = 1024 KB
#define STRIDE 64       // 64 bytes
#define REPS 1024 * MB  // times to access/modify memory (MB/KB just used as millions/thousands multiplier)
#define TIMES 6         // times to repeat experiment to get "average"
long long wall_clock_time();

int main() {
    long long start, end;
    int lengthMod;
    float totalTime;
    // 可能的Cache大小
    int sizes[] = {
        1 * KB, 4 * KB, 8 * KB, 16 * KB, 32 * KB, 64 * KB, 128 * KB, 256 * KB, 
        512 * KB, 1 * MB, 2 * MB, 3 * MB, 4 * MB, 6 * MB, 8 * MB, 10 * MB, 12 * MB
    };
   
    // 测试每个可能的的Cache大小
    for (int i = 0; i < sizeof(sizes)/sizeof(int); i++) {
        int size = sizes[i]/sizeof(int);
        // 初始化
        int* array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = i;
        }
        for (int i = size - 1; i >= 0; i--) {
            if (i < STRIDE) continue;
            int j = rand()%(i/STRIDE) * STRIDE + i%STRIDE;
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
        int index = array[rand() % size];
        // repeatedly read data
        totalTime = 0;
        for (int j = 0; j < TIMES; j++) {
            start = wall_clock_time();
            for (unsigned int k = 0; k < REPS/3; k++) {
                index = array[index];
                index = array[index];
                index = array[index];
            }
            end = wall_clock_time();
            totalTime += ((float)(end - start))/1000000000;
        }
        // where theres a spike in time --> new level of cache
        printf("%d, %1.2f \n", (sizes[i] / (1 * KB)), totalTime / TIMES);
        // cleanup
        delete[] array;
    }

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
    // #warning "Your timer resolution may be too low. Compile on linux"
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return (long long)(tv.tv_usec * 1000 + (long long)tv.tv_sec * 1000000000ll);
    #endif
}
