#include <stdio.h> 
#include <time.h>
#include <cstdlib>

#define KB 1024         // 1 KB = 1024 bytes
#define MB 1024 * KB    // 1 MB = 1024 KB
#define SIZE 8 * MB     // Size of the data array
#define MAX_STRIDE 512  // in bytes, should be multiple of 4 (sizeof(int))
#define REPS 1000000    // times to access/modify memory
#define TIMES 5         // times to repeat experiment to get "average"

int main() {
    long long start, end;
    int lengthMod;
    float totalTime;

    int* array = new int[SIZE/sizeof(int)];
    for (int stride = 1; stride <= MAX_STRIDE/sizeof(int); stride*=2){
        // 初始化
        for (int i = 0; i < SIZE/sizeof(int); i++) {
            array[i] = i;
        }
        for (int i = SIZE/sizeof(int) - 1; i >= 0; i--) {
            if (i < stride) continue;
            int j = rand()%(i/stride) * stride + i%stride;
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
        int index = array[rand() % SIZE/sizeof(int)];
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
        printf("%d, %1.2f \n", (int)(stride * sizeof(int)), totalTime / TIMES);
        // printf("%1.2f \n", totalTime / TIMES);
        // cleanup
    }
    delete[] array;
        

}
