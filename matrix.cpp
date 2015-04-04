#define SIZE 1024

#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <x86intrin.h>
#include <sys/time.h>

using namespace std;

long long wall_clock_time();
void zero_matrix(float *m);
void transpose_matrix(float *m);
void matrix_multiply(float *m1, float *m2, float *result);
void print_matrix(float *m);
void random_matrix(float *m);

void zero_matrix(float *m) {
	for (int i = 0; i < SIZE; i++) 
		for (int j = 0; j < SIZE; j++) 
			m[i * SIZE + j] = 0;
}

void transpose_matrix(float *m) {
	for (int i = 0; i < SIZE; i++) 
		for (int j = i + 1; j < SIZE; j++) 
			swap(m[i * SIZE + j], m[j * SIZE + i]);
}

void matrix_multiply_unoptimized(float *m1, float *m2, float *result) {
	long long start, end;

	start = wall_clock_time();
	for (int i = 0; i < SIZE; i++) 
		for (int j = 0; j < SIZE; j++) 
			for (int k = 0; k < SIZE; k++) 
				result[i * SIZE + j] += m1[i * SIZE + k] * m2[k * SIZE + j];
	end = wall_clock_time();
	fprintf(stderr, "Unoptimized Matrix multiplication took %1.2f seconds\n", ((float)(end - start))/1000000000);
}

void matrix_multiply_optimized(float *m1, float *m2, float *result) {
	long long start, end;

	start = wall_clock_time();
	transpose_matrix(m2);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			float tmp = 0;
			for (int k = 0; k < SIZE; k++) 
				tmp += m1[i * SIZE + k] * m2[j * SIZE + k];
			result[i * SIZE + j] = tmp;
		}
	}
	end = wall_clock_time();
	fprintf(stderr, "Optimized Matrix multiplication took %1.2f seconds\n", ((float)(end - start))/1000000000);

	// reverse the transposition
	transpose_matrix(m2);
}

void matrix_multiply_simd(float *m1, float *m2, float *result) {
	long long start, end;
	__m128 v1, v2, vMul, vRes;

	start = wall_clock_time();
	transpose_matrix(m2);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			vRes = _mm_setzero_ps();
			for (int k = 0; k < SIZE; k+=4) {
				v1 = _mm_load_ps(&m1[i * SIZE + k]);
				v2 = _mm_load_ps(&m2[j * SIZE + k]);
				vMul = _mm_mul_ps(v1, v2);

				vRes = _mm_add_ps(vRes, vMul);
			}
			vRes = _mm_hadd_ps(vRes, vRes);
			vRes = _mm_hadd_ps(vRes, vRes);
			_mm_store_ss(&result[i * SIZE + j], vRes);
		}
	}
	end = wall_clock_time();
	fprintf(stderr, "SIMD Matrix multiplication took %1.2f seconds\n", ((float)(end - start))/1000000000);

	// reverse the transposition
	transpose_matrix(m2);
}

void print_matrix(float *m) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << m[i * SIZE + j] << " ";
		} 
		cout << endl;
	}
}

void random_matrix(float *m) {
	for (int i = 0; i < SIZE; i++) 
		for (int j = 0; j < SIZE; j++) 
			m[i * SIZE + j] = rand() % 10;
}

int main() {
	// init matrixes
	float *m1 __attribute__((aligned(16))) = new float[SIZE * SIZE];
	float *m2 __attribute__((aligned(16))) = new float[SIZE * SIZE];
	float *result_unoptimized __attribute__((aligned(16))) = new float[SIZE * SIZE];
	float *result_optimized __attribute__((aligned(16))) = new float[SIZE * SIZE];
	random_matrix(m1);
	random_matrix(m2);
	zero_matrix(result_unoptimized);
	zero_matrix(result_optimized);

	// do matrix multiply
	matrix_multiply_simd(m1, m2, result_optimized);
	matrix_multiply_unoptimized(m1, m2, result_unoptimized);

	// print result
	int wrong = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (result_optimized[i * SIZE + j] != result_unoptimized[i * SIZE + j]) {
				wrong++;
			}
		}
	}
	if (wrong == 0) {
		cout << "SUCCESS: Both optimized and unoptimized gave same results" << endl;
	} else {
		cout << "FAIL: Optimized and unoptimized gave different results" << endl;
	}

	return 0;
}




/********************************************
 * Helpers
 *******************************************/
long long wall_clock_time() {
	#ifdef __linux__
		struct timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);
		return (long long)(tp.tv_nsec + (long long)tp.tv_sec * 1000000000ll);
	#else
		#warning "Your timer resoultion might be too low. Compile on Linux and link with librt"
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (long long)(tv.tv_usec * 1000 + (long long)tv.tv_sec * 1000000000ll);
	#endif
}