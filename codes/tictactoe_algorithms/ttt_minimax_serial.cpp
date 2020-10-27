#include<bits/stdc++.h>
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
    int temp;
    
    // Checking for Rows for X or O victory. 
    for (int row = 0; row<3; row++) 
    { 
        if (b[row][0]==b[row][1] && 
            b[row][1]==b[row][2]) 
        { 
            if (b[row][0]==player) 
                temp=10; 
            else if (b[row][0]==opponent) 
                temp= -10; 
        } 
    } 
  
    // Checking for Columns for X or O victory. 
    for (int col = 0; col<3; col++) 
    { 
        if (b[0][col]==b[1][col] && 
            b[1][col]==b[2][col]) 
        { 
            if (b[0][col]==player) 
                temp=10; 
  
            else if (b[0][col]==opponent) 
                temp= -10; 
        } 
    } 
  
    // Checking for Diagonals for X or O victory. 
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]==player) 
            temp=10; 
        else if (b[0][0]==opponent) 
            temp=-10; 
    } 
  
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]==player) 
            temp=10; 
        else if (b[0][2]==opponent) 
            temp=-10; 
    } 
  
    // Else if none of them have won then return 0 

    return temp; 
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
  
  
    if (isMax) 
    { 
        int best = -1000; 
  
        // Traverse all cells 
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='_') 
                { 
                    // Make the move 
                    board[i][j] = player; 
  
                    
                    best = max( best, 
                        minimax(board, depth+1, !isMax) ); 
  
                    
                    board[i][j] = '_'; 
                } 
            } 
        } 
        return best; 
    } 
  
 
    else
    { 
        int best = 1000; 
  
        // Traverse all cells 
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='_') 
                { 
                    // Make the move 
                    board[i][j] = opponent; 
  
                    // Call minimax recursively and choose 
                    // the minimum value 
                    best = min(best, 
                           minimax(board, depth+1, !isMax)); 
  
                    // Undo the move 
                    board[i][j] = '_'; 
                } 
            } 
        } 
        return best; 
    } 
} 
  
// This will return the best possible move for the player 
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
  
// Driver code 
int main() 
{ 
    
    
    char board[3][3] = 
    { 
        { 'x', 'o', '_' }, 
        { 'x', 'o', 'x' }, 
        { 'o', '_', '_' } 
    }; 
   
    clock_t start = clock();
    cout<<"\nThe current stage of the game:"<<endl;
    for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
		cout<<" "<<board[i][j]<<" ";
	}
	cout<<endl;
    }
    cout<<"\n";
    for(int i=0;i<1000;i++){
	for(int j=0;j<1000;j++){
		int t=0;
		t++;
	}
    }
    Move bestMove = findBestMove(board); 
  
    printf("The Optimal Move is :\n"); 
    printf("ROW: %d COL: %d\n\n", bestMove.row+1, 
                                  bestMove.col+1 ); 
    
    clock_t end = clock();
    double timespent = ((double)(end - start) / CLOCKS_PER_SEC);
   
    
    cout<<"execution time for serial code="<<timespent<<endl;
    return 0; 
}
