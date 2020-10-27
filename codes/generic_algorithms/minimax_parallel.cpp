#include<bits/stdc++.h>
#include<omp.h> 
#include<time.h>
using namespace std; 

long int minimax(long int depth,long int nodeIndex, bool isMax, 
            long int scores[],long int h) 
{ 

    if (depth == h) 
        return scores[nodeIndex]; 
  
    long int t1, t2, res;
    if (isMax){
	    #pragma omp parallel
	    {
	       #pragma omp single
	       {
		   #pragma omp task shared(t1)
		   {
			t1=minimax(depth+1, nodeIndex*2, false, scores, h);
		   }

		   #pragma omp task shared(t2)
		   {
			t2=minimax(depth+1, nodeIndex*2 + 1, false, scores, h);
		   }
		   
		   #pragma omp taskwait
		   {
			res=max(t1,t2);
		   }
		   
		   
	       }
	  
	    }
	    return res; 
    }
    else{
	#pragma omp parallel
	{
		#pragma omp single
		{
			#pragma omp task shared(t1)
			{
				t1=minimax(depth+1, nodeIndex*2, true, scores, h);
			}
			
			#pragma omp task shared(t2)
			{
				t2=minimax(depth+1, nodeIndex*2 + 1, true, scores, h);
			}
			#pragma omp taskwait
		   	{
				res=min(t1,t2);
		   	}
		}
	}
	return res;
 }
        
} 
  

long int log2(long int n) 
{ 
  return (n==1)? 0 : 1 + log2(n/2); 
} 
  

int main() 
{ 
    
    long int scores[1000],i;
    #pragma omp parallel for
    for(i=0;i<1000;i++){
	scores[i]=(rand()%100)+1;
    } 
    long int n = sizeof(scores)/sizeof(scores[0]); 
    long int h = log2(n); 
    clock_t start = clock();
    long int res = minimax(0, 0, true, scores, h); 
    clock_t end = clock();
    double timespent = ((double)(end - start) / CLOCKS_PER_SEC);
    cout << "The optimal value is : " << res << endl;
    cout<<"execution time="<<timespent<<endl; 
    return 0; 
}
