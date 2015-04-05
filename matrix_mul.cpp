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
	//��ʼ������1000*1000�ľ���
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
	//���A*B�Ľ��
	int (*c)[1000],(*d)[1000];
	c = new int[1000][1000];
	d = new int[1000][1000];

	//��ʼ��Ϊ0
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

	//�����޸ĵĲ���  ��ʼ
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
	// �����޸ĵĲ���   ����
	// ======================================================
	finish1 = clock();

	//�Ա����εĽ��
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