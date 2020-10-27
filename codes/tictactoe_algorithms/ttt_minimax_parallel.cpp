#include<bits/stdc++.h> 
#include<omp.h>
#include<time.h>
using namespace std; 
struct Move 
{ 
    int row, col; 
}; 
  
char player = 'x', opponent = 'o'; 
 
bool isMovesLeft(char board[3][3]) 
{ 
    
    for (int i = 0; i<3; i++) 
        for (int j = 0; j<3; j++) 
            if (board[i][j]=='_') 
                return true; 
    return false; 
} 
  

int evaluate(char b[3][3]) 
{ 
     
    int temp=0;
#pragma omp parallel shared(temp)
{
    #pragma omp single nowait
    {	    
	    #pragma omp task
	    {
		    
		    for (int row = 0; row<3; row++) 
		    { 
			if (b[row][0]==b[row][1] && 
			    b[row][1]==b[row][2]) 
			{ 
			    if (b[row][0]==player) 
				temp=10; 
			    else if (b[row][0]==opponent) 
				temp=-10;
			} 
		    } 
	  
            }

	    #pragma omp task
	    {
		    
		    for (int col = 0; col<3; col++) 
		    { 
			if (b[0][col]==b[1][col] && 
			    b[1][col]==b[2][col]) 
			{ 
			    if (b[0][col]==player) 
				temp=10; 
		  
			    else if (b[0][col]==opponent) 
				temp=-10; 
			} 
		    } 
	    }

	
	    
	    #pragma omp task
	    {
		    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
		    { 
			if (b[0][0]==player) 
			    temp=10; 
			else if (b[0][0]==opponent) 
			    temp=-10; 
		    } 
       	    
	     }	    
	     
	     #pragma omp task
	     {    	  
		    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
		    { 
			if (b[0][2]==player) 
			    temp=10; 
			else if (b[0][2]==opponent) 
			    temp=-10; 
		    }
	     }
	}
       	  
}
    return temp;
} 
  
// maximiser move
int minimax(char board[3][3], int depth, bool isMax) 
{ 
    int score = evaluate(board); 
  
   
    if (score == 10) 
        return score; 
  
    
    if (score == -10) 
        return score; 
  
    
    if (isMovesLeft(board)==false) 
        return 0; 
    int best;
    #pragma omp parallel if(isMax)
    if (isMax) 
    { 
        best = -1000; 
  
        #pragma omp parallel for
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                #pragma omp parallel if(board[i][j]=='_')
                if (board[i][j]=='_') 
                { 
                    
                    board[i][j] = player; 
  
                    
                    best = max( best, 
                        minimax(board, depth+1, !isMax) ); 
  
                    // Undo the move 
                    board[i][j] = '_'; 
                } 
            } 
        } 
        //return best; 
    } 
  
    // If this minimizer's move 
    else
    { 
        best = 1000; 
  
        // Traverse all cells 
        #pragma omp parallel for
        for (int i = 0; i<3; i++) 
        {   
            for (int j = 0; j<3; j++) 
            { 
                
                if (board[i][j]=='_') 
                { 
                    
                    board[i][j] = opponent; 
  
                    
                    best = min(best, 
                           minimax(board, depth+1, !isMax)); 
  
                    // Undo the move 
                    board[i][j] = '_'; 
                } 
            } 
        } 
        //return best; 
    } 
    return best;
} 
  
// This will return the best possible move for the player 
Move findBestMove(char board[3][3]) 
{ 
    int bestVal = -1000; 
    Move bestMove; 
    bestMove.row = -1; 
    bestMove.col = -1; 
  
    int i,j;
    #pragma omp parallel for private(i,j)
    for (i = 0; i<3; i++) 
    { 
        for (j = 0; j<3; j++) 
        { 
            #pragma omp parallel if(board[i][j]=='_')  
            if (board[i][j]=='_') 
            { 
                
                board[i][j] = player; 
  
                
                int moveVal = minimax(board, 0, false); 
  
                 
                board[i][j] = '_'; 
  
                
                if (moveVal > bestVal) 
                { 
                    bestMove.row = i; 
                    bestMove.col = j; 
                    bestVal = moveVal; 
                } 
            } 
        } 
    } 
  
    printf("The value of the best Move is : %d\n\n", 
            bestVal); 
  
    return bestMove; 
} 
  

int main() 
{ 
    
    
    char board[3][3] = 
    { 
        { 'x', 'x', '_' }, 
        { '_', 'o', '_' }, 
        { 'o', '_', '_' } 
    }; 
    cout<<"\nThe current stage of the game:"<<endl;
    for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
		cout<<" "<<board[i][j]<<" ";
	}
	cout<<endl;
    }
    cout<<"\n";
    clock_t start = clock();
    Move bestMove = findBestMove(board); 
    
    
    clock_t end = clock();
    double timespent = ((double)(end - start) / CLOCKS_PER_SEC);
    
    printf("The Optimal Move is :\n"); 
    printf("ROW: %d COL: %d\n\n", bestMove.row+1, 
                                  bestMove.col+1 ); 
    
    cout<<"execution time for parallel algorithm="<<timespent<<endl;
    return 0; 
}
