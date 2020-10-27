#include<bits/stdc++.h> 
#include<time.h>
using namespace std; 
long int minimax(long int depth,long int nodeIndex, bool isMax, 
            long int scores[],long int h) 
{ 
    
    if (depth == h) 
        return scores[nodeIndex]; 
  
    
    if (isMax) 
       return max(minimax(depth+1, nodeIndex*2, false, scores, h), 
            minimax(depth+1, nodeIndex*2 + 1, false, scores, h)); 
  
    
    else
        return min(minimax(depth+1, nodeIndex*2, true, scores, h), 
            minimax(depth+1, nodeIndex*2 + 1, true, scores, h)); 
} 
  

long int log2(long int n) 
{ 
  return (n==1)? 0 : 1 + log2(n/2); 
} 
  

int main() 
{ 
    
    long int scores[1000],i;
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
