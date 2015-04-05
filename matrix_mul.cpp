#include <iostream>   
#include <vector>
#include <time.h>
using namespace std;   

void transpose_matrix(int b[][1000]) {
	for (int i = 0 ; i < 1000 ; i++) {
		for (int j = 0; j < 1000; j++) {
			int tmp = b[i][j];
			b[i][j] = b[j][i];
			b[j][i] = tmp;
		}
	}
	return;
}


int main()
{
	clock_t start, finish;
	clock_t start1, finish1;

	int i,j,k;
	//初始化两个1000*1000的矩阵
	int (*a)[1000],(*b)[1000];
	a = new int[1000][1000];
	b = new int[1000][1000];
    
	
	for(i = 0; i < 1000; i++)
	{
		for(j = 0; j < 1000; j++)
		{
			a[i][j] = i % (j+1);
			b[i][j] = i / (j+1);
		}
	}
	//存放A*B的结果
	int (*c)[1000],(*d)[1000];
	c = new int[1000][1000];
	d = new int[1000][1000];

	//初始化为0
	memset(c,0, 1000*1000*sizeof(int));
	memset(d,0, 1000*1000*sizeof(int));

	start = clock();	
	for(i = 0; i < 1000; i++)
	{
		for(j = 0; j < 1000; j++)
		{
			for (k = 0; k < 1000; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}

		}
	}
	finish = clock();

	start1 = clock();

	//可以修改的部分  开始
	//======================================================

	int N = 1000;
	int B = 62;
	for ( int jj = 0; jj < N; jj = jj+B) {
		for ( int kk = 0; kk < N; kk = kk+B) {
			for ( int i = 0; i < N; i++) {
				for ( int j = jj; j < min(jj+B, N); j++) { 
					int r = 0; 
					for ( k = kk; k < min(kk+B, N); k++) {
						r = r + a[ i ][ k ] * b[ k ][ j ]; 
					}
					d[ i ][ j ] = d[ i ][ j ] + r;
				} 
			}
		}
	}
	// 可以修改的部分   结束
	// ======================================================
	finish1 = clock();

	//对比两次的结果
	for(i = 0; i < 1000; i++)
	{
		for(j = 0; j < 1000; j++)
		{
			if (c[i][j] != d[i][j])
			{
				cout<< i << ", " << j << " : you have got an error in algorithm modification!"<<endl;
				exit(1);
			}

		}
	}



	cout<<"time spent for original method : "<<finish - start<<" ms"<<endl;
	cout<<"time spent for new method : "<<finish1 - start1<<" ms"<<endl;
	return 0;
}