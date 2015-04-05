#include <stdio.h> 
#include <sys/time.h>

#define KB 1024 // 1 KB = 1024 bytes
#define MB 1024 * KB // 1 MB = 1024 KB
#define SIZE 12 * MB // size of data array
#define REPS 256 * MB // number time times to write


int main() {
    long long start, end;

    int sizes[] = {
        1 * KB, 4 * KB, 8 * KB, 16 * KB, 32 * KB, 64 * KB, 128 * KB, 256 * KB, 
        512 * KB, 1 * MB, 2 * MB, 3 * MB, 4 * MB, 6 * MB, 8 * MB, 10 * MB, 12 * MB
    };
    for (int i = 0; i < sizeof(sizes)/sizeof(int); i++) {
        int size = sizes[i]/sizeof(int);
        int *data = new int[size];
        int *data2 = new int[size];

        int lengthMod = size-1;
        start = clock();
        int index;
        for (int j = 0; j < REPS; j++) 
            index = data[(j * 16) & lengthMod];
        end = clock();
        printf("%d: ", (sizes[i] / (1 * KB)));
        printf("%.2lf, ", (end-start)/1000.0);
        // write to data
        for (int j = 0; j < REPS; j++) 
            data2[(j * 16) & lengthMod] = j;
        start = clock();
        for (int j = 0; j < REPS; j++) 
            index = data2[(j * 16) & lengthMod];
        end = clock();
        printf("%.2lf\n", (end-start)/1000.0);

        delete[] data;
        delete[] data2;
    }
}