#include <bits/stdc++.h>
#include<omp.h> 
using namespace std;

long long int ZobrisTable[3][3][2];

void init_table()
{
	int i,k,j;
	#pragma omp parallel for
	for(i=0;i<3;i++){
		#pragma omp parallel for
		for(j=0;j<3;j++){
			#pragma omp parallel for
			for(k=0;k<2;k++)
			{
				ZobrisTable[i][j][k]=rand();
				cout<<ZobrisTable[i][j][k]<<" ";
			}
		}
	}
}

int indexof(char player)
{
	if(player=='x')
		return 1;
	else if(player=='o')
		return 2;
	else
		return -1;
}

long long int computeHash(char board[3][3])
{
	long long int h=0;
	#pragma omp parallel for
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]!='_'){
				int player=indexof(board[i][j]);
				h^=ZobrisTable[i][j][player];
			}
		}
	}
	return h;
}

int main()
{
	char board[3][3] = 
	{ 
        	{ 'x', 'o', '_' }, 
        	{ 'x', 'o', 'x' }, 
        	{ 'o', '_', '_' } 
	}; 
	
	clock_t start = clock();
	cout<<"\nInitial values of Zobris Table:";
	init_table();
	cout<<"\n";
	long long int hashval=computeHash(board);
	clock_t end = clock();
	double timespent = ((double)(end - start) / CLOCKS_PER_SEC);
	cout<<"\nhash value="<<hashval<<endl;
	cout<<"execution time="<<timespent<<endl;
	return 0;
}
