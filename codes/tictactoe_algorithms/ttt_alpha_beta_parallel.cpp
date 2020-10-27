#include<bits/stdc++.h> 
using namespace std; 
const int MAX=1000;
const int MIN=-1000;
  
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
    #pragma omp parallel
{
    #pragma omp for nowait
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
  
    #pragma omp for nowait 
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
  

    #pragma omp if nowait
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]==player) 
            temp=10; 
        else if (b[0][0]==opponent) 
            temp=-10; 
    } 
  
    #pragma omp if nowait
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]==player) 
            temp=10; 
        else if (b[0][2]==opponent) 
            temp=-10; 
    } 
  
}   
    return temp; 
} 
  

int minimax(char board[3][3], int depth, bool isMax,int alpha, int beta) 
{ 
    int score = evaluate(board); 
  
    
    if (score == 10) 
        return score; 
  
    
    if (score == -10) 
        return score; 
  
    
    if (isMovesLeft(board)==false) 
        return 0; 
  
    // If this maximizer's move 

    int val;
    #pragma omp parallel if(isMax)
{
    if (isMax) 
    { 
        int best = -1000; 
  
        #pragma omp parallel for
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='_') 
                { 
                    // Make the move 
                    board[i][j] = player; 
  
                    // Call minimax recursively and choose 
                    // the maximum value 
                    best = max( best, 
                        minimax(board, depth+1, !isMax,alpha, beta) ); 
					alpha=max(alpha,best);
					if (beta <= alpha) 
                	break;	  
                    // Undo the move 
                    board[i][j] = '_'; 
                } 
            } 
        }

        val=best;
    } 
  
    //this minimizer's move 
    else
    { 
        int best = 1000; 
  
  	#pragma omp parallel for      
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='_') 
                { 
                    // Make the move 
                    board[i][j] = opponent; 
		    int c1;
		    #pragma omp parallel
		    {
			#pragma omp single
			{
				#pragma omp task shared(c1)
				{
					c1=minimax(board, depth+1, !isMax,alpha,beta);
				}
				#pragma omp task shared(best)
				{
					best=min(best,c1);
					
  					
				}
				#pragma omp taskwait
				{
					beta=min(beta,best);
				}
			}
		    }
		    if (beta <= alpha) 
                	break;
                    /*best = min(best, 
                           minimax(board, depth+1, !isMax,alpha,beta)); 
  					beta=min(beta,best);
  					if (beta <= alpha) 
                		break;*/
                    // Undo the move 
                    board[i][j] = '_'; 
                } 
            } 
        } 
        val=best;
    } 
}
    return val;
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
            if (board[i][j]=='_') 
            { 
                 
                board[i][j] = player; 
  
                 
                int moveVal = minimax(board, 0, false,MIN,MAX); 
  
               
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
    printf("The Optimal Move is :\n"); 
    printf("ROW: %d COL: %d\n\n", bestMove.row+1, 
                                  bestMove.col+1 );
    double timespent = ((double)(end - start) / CLOCKS_PER_SEC); 
    cout<<"execution time="<<timespent<<endl; 
    return 0; 
}
