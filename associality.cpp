#include <stdio.h> 
#include <time.h>
#include <cstdlib>

#define KB 1024       // 1 KB = 1024 bytes
#define MB 1024 * KB  // 1 MB = 1024 KB
#define L1CACHE 32 * KB   // L1 Cache size = 32KB
#define L2CACHE 256 * KB  // L2 Cache size = 256KB
#define L3CACHE 3 * MB    // L3 Cache size = 3MB
#define REPS 10000000  // times to access/modify memory
#define TIMES 5       // times to repeat experiment to get "average"

int main() {
    long long start, end;
    int lengthMod;
    float totalTime;
    int size = 2*L1CACHE/sizeof(int); 
    int* array = new int[size];
    for (int n = 2; n < 8; n++) {
        // 将数组分为2^n块，只访问奇数块
        int block_size = size/(1 << n);
        // 初始化
        int blocks = (1 << n);
        for (int i = 1; i < blocks; i+=2) {
            for (int j = block_size*i; j < block_size*(i+1); j ++) {
                int k = (rand()%(blocks/2)) * 2 + 1;
                array[j] = (block_size*k + (rand()%block_size)) % size;
            }
        }
        // 多次读取数据
        totalTime = 0;
        int index = array[block_size + (rand()%block_size)];
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
        // printf("%d, %1.2f \n", (sizes[i] / (1 * KB)), totalTime / TIMES);
        printf("%d, %1.2f \n", 1 << (n-2), totalTime / TIMES);
                
    }
    delete[] array;
}
