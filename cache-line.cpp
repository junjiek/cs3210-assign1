#include <stdio.h> 
#include <time.h>
#include <cstdlib>

#define KB 1024         // 1 KB = 1024 bytes
#define MB 1024 * KB    // 1 MB = 1024 KB
#define MAX_STRIDE 512 // in bytes, should be multiple of 4 (sizeof(int))
#define REPS 1000000    // times to access/modify memory
#define TIMES 5         // times to repeat experiment to get "average"

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
        // 多次读取数据
        totalTime = 0;
        for (int j = 0; j < TIMES; j++) {
            start = clock();
            for (unsigned int k = 0; k < REPS/3; k++) {
                index = array[index];
                index = array[index];
                index = array[index];
            }
            end = clock();
            totalTime += ((float)(end - start))/1000;
        }
        // 跳变处即为new level cache
        printf("%d, %1.2f \n", (sizes[i] / (1 * KB)), totalTime / TIMES);
        // printf("%1.2f \n", totalTime / TIMES);
        // cleanup
        delete[] array;
    }

}
