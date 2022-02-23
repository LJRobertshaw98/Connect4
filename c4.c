#include <stdio.h>
#include <unistd.h>

#define NROWS 6
#define NCOLS 7
#define CONNECT 4

void drop_piece(int board[NROWS][NCOLS], int row, int col, int piece){
    board[row][col] = piece;
}

int is_valid_location(int board[NROWS][NCOLS], int col){
    /* Checks if the column chosen by the player is a valid location */
    if(board[NROWS-1][col] == 0){  // Evaluates to false for col != 2 or 3
        return 0;
    } else{
        return 1;
    }
}

int get_next_open_row(int board[NROWS][NCOLS], int col){
    /* This function checks the lowest row which is zero, ie drops a piece and it will land on the lowest row that is free */
    for(int row = 0; row < NROWS; row++){
        if(board[row][col] == 0){
            return row;
        }
    }
}

void draw_board(int board[NROWS][NCOLS]){
    // Display 2D array using for loop
//    printf("The Array elements are:\n");
    for(int row=NROWS; row>0; row--) {
        // inner loop for column
        for(int col=0; col<NCOLS; col++) {
            printf("%d ", board[row-1][col]);
        }
        printf("\n"); // new line
    }
}

int winning_move(int board[NROWS][NCOLS], int piece, int col, int row){

    // Check horizontals
    for(int c = 0; c < NCOLS-3; c++){
        for(int r = 0; r < NROWS; r++){
            if(board[r][c] == piece && board[r][c+1] == piece && board[r][c+2] == piece && board[r][c+3] == piece){
                return 1;
            }
        }
    }

    // Check verticals
    for(int c = 0; c < NCOLS; c++){
        for(int r = 0; r < NROWS-3; r++){
            if(board[r][c] == piece && board[r+1][c] == piece && board[r+2][c] == piece && board[r+3][c] == piece){
                return 1;
            }
        }
    }

    // Check positive diagonal
    for(int c = 0; c < NCOLS-3; c++){
        for(int r = 0; r < NROWS-3; r++){
            if(board[r][c] == piece && board[r+1][c+1] == piece && board[r+2][c+2] == piece && board[r+3][c+3] == piece){
                return 1;
            }
        }
    }

    // Check negative diagonal
    for(int c = 0; c < NCOLS-3; c++){
        for(int r = 3; r < NROWS; r++){
            if(board[r][c] == piece && board[r-1][c+1] == piece && board[r-2][c+2] == piece && board[r-3][c+3] == piece){
                return 1;
            }
        }
    }

    return 0;
}

int main(){
    
    int board[NROWS][NCOLS] = {0};  // Initialise the board as array of 0s
    int game_over = 0;  // 0 represents game not over, 1 is game over
    int turn = 0;  // even represents player 1, odd represents player 2
    int col;  // initialise variable to store column selected by player
    int row;  // Initialise row which will store next open row each time player chooses a column
    int piece;

    while(game_over == 0){

        piece = (turn % 2) + 1;
        draw_board(board);
    
        // Ask for player input
        if(piece == 1){
            printf("Player %d make your move (0-6)\n", piece);
            scanf("%d", &col);
            
            if(is_valid_location(board, col) == 0){
                row = get_next_open_row(board, col);
                drop_piece(board, row, col, piece);
            } else if(is_valid_location(board, col) == 1){
                printf("Player %d: location not valid! \n", piece);
            }

            game_over = winning_move(board, piece, col, row);
            if(game_over == 1){
                draw_board(board);
                printf("Player %d wins!\n", piece);
                sleep(3);
            }

        } else if(piece == 2){
            printf("Player %d make your move (0-6)\n", piece);
            scanf("%d", &col);
            
            if(is_valid_location(board, col) == 0){
                row = get_next_open_row(board, col);
                drop_piece(board, row, col, piece);
            } else if (is_valid_location(board, col) == 1) {
                printf("Player %d: location not valid!\n", piece);
            }
            
            game_over = winning_move(board, piece, col, row);
            if(game_over == 1){
                draw_board(board);
                printf("Player %d wins!\n", piece);
                sleep(3);
            }
        }

        turn += 1;
    }

    return 0;
}
