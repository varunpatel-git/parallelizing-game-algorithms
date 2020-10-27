// ZOBRIST COMBINED WITH MINIMAX

#include <iostream>   
using namespace std;
#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
using namespace std;

long ZobristTable[3][3][2];

long randomno()
{
	long temp= rand();
	long n= temp*rand()*rand();
	n=n*rand()*n*n;
	n=n*rand()*999999;
	return n%100000;
}

int indexof(char ch){
	if(ch=='x' || ch=='X'){
		return 0;
	}
	if(ch=='o' || ch=='O'){
		return 1;
	}
	else{
		return -1; 
	}
}

void initTable() 
{
    #pragma omp parallel num_threads(1)
    {
    for (int i = 0; i<3; i++) 
      for (int j = 0; j<3; j++) 
        for (int k = 0; k<2; k++) 
          ZobristTable[i][j][k] = randomno();
    }
    
} 

long computeHash(char board[3][3]) 
{ 
    long h = 0; 
    #pragma omp parallel num_threads(1)
    {
    
    for (int i = 0; i<3; i++) 
    { 
        for (int j = 0; j<3; j++) 
        { 
            if (board[i][j]!='-') 
            { 
                int piece = indexof(board[i][j]); 
                h ^= ZobristTable[i][j][piece]; 
            } 
        } 
    }
    } 
    return h; 
} 



// Minimax Functions
struct Move 
{ 
    int row, col; 
};

char player = 'x', opponent = 'o'; 
bool isMovesLeft(char board[3][3]);
int evaluate(char b[3][3]);
int minimax(char board[3][3], int depth, bool isMax); 
Move findBestMove(char board[3][3]);


int win_lose(char b[3][3]){
	
	for (int row = 0; row<3; row++) 
    	{ 
        	if (b[row][0]==b[row][1] && 
            	b[row][1]==b[row][2]) 
        	{ 
            	if (b[row][0]=='x') 
                	return 1; 
            	else if (b[row][0]=='o') 
                	return -1; 
        	} 
    	
    }
    
    	

    for (int col = 0; col<3; col++) 
    	{ 
        if (b[0][col]==b[1][col] && 
            b[1][col]==b[2][col]) 
        { 
            if (b[0][col]=='x') 
                return 1; 
  
            else if (b[0][col]=='o') 
                return -1; 
        } 
    
    }
    
  
    // Checking for Diagonals for X or O victory. 
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]=='x') 
            return 1; 
        else if (b[0][0]=='o') 
            return -10; 
    } 
  
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]=='x') 
            return 1; 
        else if (b[0][2]=='o') 
            return -1; 
    }
    
    return 2;
}
 
int main()
{
	
	clock_t start1 = clock();
	initTable(); 
	long hash[1000], temp; int idx=0;
	char board[3][3] = 
    	{	 
        	{ '-', '-', '-' }, 
        	{ '-', '-', '-' }, 
        	{ '-', '-', '-' } 
    	}; 
    
    	int result;
    	    	
	    	while(isMovesLeft(board)){
	    	
	    		
	    		
	    		
	    		Move bestMove = findBestMove(board);
	    		board[bestMove.row][bestMove.col]='x';
	    		
	    		temp= computeHash(board);
	    		hash[idx]=temp;
	    		idx++;
	    		
	    		for(int i=0;i<3;i++){
	    			for(int j=0;j<3;j++){
	    				cout<<board[i][j]<<"	";
	    			}cout<<endl;
	    		}
	    		cout<<"----------------\n";
	    		result=win_lose(board);
	    		if(result==1 || result==-1){
	    			break;
	    		}
	    		
	    		int x,y;
	    		
	    		cout<<"\nEnter opp move:";
	    		cin>>x>>y;
	    		board[x][y]='o';
	    		
	    		temp= computeHash(board);
	    		hash[idx]=temp;
	    		idx++;
	    		
	    		for(int i=0;i<3;i++){
	    			for(int j=0;j<3;j++){
	    				cout<<board[i][j]<<"	";
	    			}cout<<endl;
	    		}
	    		cout<<"----------------\n";
	    		result=win_lose(board);
	    		if(result==1 || result==-1){
	    			break;
	    		}
	    	}
	    	clock_t end1 = clock();
			double timespent1 = ((double)(end1 - start1) / CLOCKS_PER_SEC);
	    	
	    	
	    	if(result==1){
	    		cout<<"YOU WON\n\n";
	    	}
	    	else{
	    		cout<<"Opponent Won\n\n";
	    	}
	    	float p=pow(10, -4);
    	char board2[3][3] = 
    	{	 
        	{ '-', '-', '-' }, 
        	{ '-', '-', '-' }, 
        	{ '-', '-', '-' } 
    	}; 
    	
	int pred=2;
	clock_t start2 = clock();
	while(isMovesLeft(board2)){
	    		//result=evaluate(board);
	    		if(pred==1 || pred==-1){
	    			break;
	    		}
	    		
	    		Move bestMove = findBestMove(board2);
	    		board2[bestMove.row][bestMove.col]='x';
	    		
	    		temp= computeHash(board2);
	    		
	    		if(temp==hash[4] || temp==hash[5] || temp==hash[2]){
	    			pred=result;
	    			break;
	    		}
	    		
	    		#pragma omp parallel num_threads(1)
    			{
	    		for(int i=0;i<3;i++){
	    			for(int j=0;j<3;j++){
	    				cout<<board2[i][j]<<"	";
	    			}cout<<endl;
	    		}
	    		}
	    		cout<<"----------------\n";
	    		
	    		
	    		
	    		int x,y;
	    		
	    		cout<<"\nEnter opp move:";
	    		cin>>x>>y;
	    		board2[x][y]='o';
	    		
	    		if(temp==hash[4] || temp==hash[5] || temp==hash[2]){
	    			pred=result;
	    			break;
	    		}
	    		#pragma omp parallel num_threads(1)
	    		{
	    		for(int i=0;i<3;i++){
	    			for(int j=0;j<3;j++){
	    				cout<<board2[i][j]<<"	";
	    			}cout<<endl;
	    		}
	    		}
	    		cout<<"----------------\n";
	    		
	    		
	    		
	    	}
	    	clock_t end2 = clock();
			double timespent2 = ((double)(end2 - start2) / CLOCKS_PER_SEC);
	    	
	    	double t3 = timespent1*p + timespent2*p;
	    	
	    	if(result==-1){
	    		cout<<"You will lose"<<endl;
	    	}
	    	else if(result == 2){
	    		cout<<"High chance of draw"<<endl;
	    	}
	    	
	    	else{
	    		cout<<"You may win\n";
	    	}
    		printf("Time:- %f\n", t3);
	return 0;
	
}







bool isMovesLeft(char board[3][3]) 
{ 
    for (int i = 0; i<3; i++) 
        for (int j = 0; j<3; j++) 
            if (board[i][j]=='-') 
                return true; 
    return false; 
} 

int evaluate(char b[3][3]) 
{ 
    // Checking for Rows for X or O victory.

    for (int row = 0; row<3; row++) 
    { 
        if (b[row][0]==b[row][1] && 
            b[row][1]==b[row][2]) 
        { 
            if (b[row][0]==player) 
                return +10; 
            else if (b[row][0]==opponent) 
                return -10; 
        } 
    }
    
  
    // Checking for Columns for X or O victory. 

    for (int col = 0; col<3; col++) 
    { 
        if (b[0][col]==b[1][col] && 
            b[1][col]==b[2][col]) 
        { 
            if (b[0][col]==player) 
                return +10; 
  
            else if (b[0][col]==opponent) 
                return -10; 
        } 
    }
    
  
    // Checking for Diagonals for X or O victory. 
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]==player) 
            return +10; 
        else if (b[0][0]==opponent) 
            return -10; 
    } 
  
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]==player) 
            return +10; 
        else if (b[0][2]==opponent) 
            return -10; 
    } 
  
    // Else if none of them have won then return 0 
    return 0; 
} 


int minimax(char board[3][3], int depth, bool isMax) 
{ 
    int score = evaluate(board); 
  
   
    if (score == 10) 
        return score; 
  
    
    if (score == -10) 
        return score; 
  
    
    if (isMovesLeft(board)==false) 
        return 0; 
  
    // If this maximizer's move 
    if (isMax) 
    { 
        int best = -1000; 
  
        // Traverse all cells 
        #pragma omp parallel num_threads(1)
    	{
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='-') 
                { 
                    // Make the move 
                    board[i][j] = player; 
  
                    
                    best = max( best, 
                        minimax(board, depth+1, !isMax) ); 
  
                    // Undo the move 
                    board[i][j] = '-'; 
                } 
            } 
        }
        }
        return best; 
    } 
  
    // If this minimizer's move 
    else
    { 
        int best = 1000; 
  
        // Traverse all cells 
        #pragma omp parallel num_threads(1)
    	{
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='-') 
                { 
                    // Make the move 
                    board[i][j] = opponent; 
  
                     
                    best = min(best, 
                           minimax(board, depth+1, !isMax)); 
  
                    // Undo the move 
                    board[i][j] = '-'; 
                } 
            } 
        }
        }
        return best; 
    } 
} 


Move findBestMove(char board[3][3]) 
{ 
    int bestVal = -1000; 
    Move bestMove; 
    bestMove.row = -1; 
    bestMove.col = -1; 
  
     
    for (int i = 0; i<3; i++) 
    { 
        for (int j = 0; j<3; j++) 
        { 
            // Check if cell is empty 
            if (board[i][j]=='-') 
            { 
                // Make the move 
                board[i][j] = player; 
  
                
                int moveVal = minimax(board, 0, false); 
  
                // Undo the move 
                board[i][j] = '-'; 
  
                
                if (moveVal > bestVal) 
                { 
                    bestMove.row = i; 
                    bestMove.col = j; 
                    bestVal = moveVal; 
                } 
            } 
        } 
    } 
  
    //printf("The value of the best Move is : %d\n\n", 
    //        bestVal); 
  
    return bestMove; 
}
