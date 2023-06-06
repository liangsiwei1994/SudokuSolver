#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}



/* functions from here are user-defined functions for submission */



/* Function checks if board is completed and only filled with characters '1' to '9'
 * @param board: Sudoku board to be passed into the function for checking 
 * @return True: if the sudoku board only contains a character between '1' to '9'. False: if any of the position has a character outside of this range. */
bool is_complete(char board[9][9]) {
	/* to loop each row */
        for (int r=0; r<9; r++) {
		/* to loop each column */
                for (int c=0; c<9; c++){
                        if (!check_value(board[r][c]))
                                return false;
                }
        }
        return true;
}
/* end of function*/



/* Function that checks and attempts to place a digit onto the sudoku board at the requested position */
/* @param position: 2 characters string that represents the requested position to place the digit.
 * @param digit: Single (character) digit between '1' to '9' the function attempts to place on the requested position.
 * @param board: The board which the (character) digit is attempted to be placed on.
 * @return True: if the digit is valid for the requested position. False: if the digit is not valid due to 1) the digit appears in the row, column or subboard, 2) the position is filled, 3) the position is not a valid location within the board. 4) the digit to be placed is not between '1' to '9'. When False, board will remain unchanged. */
bool make_move(const char* position, char digit, char board[9][9]) {
        
	int r, c;

        r = position[0] - 'A';
        c = position[1] - '1';

        if(!check_value(digit))
                return false;

        if(check_value(board[r][c]))
                return false;

        if(!check_position(r, c))
                return false;

        if(!check_row_column(r, c, digit, board))
                return false;

        if(!check_subboard(r, c, digit, board))
                return false;

        else {
          board[r][c] = digit;
          return true;
        }
}
/* end of function */

/* Helper function has two purposes: 1) Check if the current position of the sudoku board is filled 2) Check if the digit to be placed on a position is within '1' to '9' */
/* @param value: Purpose 1) (character) digit at particular position, purpose 2) (character) digit to be placed on a particular position
 * @return True: if the digit is between '1' to '9'. False: if the digit is outside of the range. */
bool check_value(char value) {

        if (value >= '1' && value <= '9')
                return true;

        return false;
}
/* end of function */

/* Helper function that checks if the position is a valid location on the 9x9 board */
/* @param r: Row number to be checked if its valid.
 * @param c: Column number to be checked if its valid.
 * @return True: if the row or column number is within 1 to 9. False: if the row or column number falls outside of 1 to 9. */
bool check_position(int r, int c) {

        if ((r < 0 || r > 8) || (c < 0 || c > 8))
                return false;

        return true;
}
/* end of function*/

/* Helper function that checks if the digit to be placed on the board has appeared in the column or row it is requested to be placed at */
/* @param r: Row value of the position to be checked against.
 * @param c: Column value of the position to be checked against.
 * @param digit: Digit to be checked against.
 * @param board: Board that the digit is checked against.
 * @return True: if the digit is valid for the row and columnn. False: if the digit exists in the row and column it was checked against. Board will remain unchanged if the check is False. */
bool check_row_column(int r, int c, char digit, char board[9][9]) {

        /* iterate through each column in row r to check for duplicates */
        for (int i=0; i<9; i++){
		/* skip if it's the requested column */
                if(i == c)
                        continue;

                if (board[r][i] == digit)
                        return false;

                /* iterate through each row in column c to check for duplicates */
                for (int j=0; j<9; j++){
			/* skip if it's the requested row */
                        if (j == r)
                                continue;

                        if (board[j][c] == digit)
                                return false;
                }
        }
        return true;
}
/* end of function */

/* Helper function that check if the digit is valid within the sub-board */
/* @param r: Row value of the position to be checked against.
 * @param c: Column value of the position to be checked against.
 * @param digit: Digit to be checked against.
 * @param board: Existing board where the digit will be checked against.
 * @return True: if the digit is valid for the position's sub-board. False: if the digit exists in the sub-board it was checked against. Board will remain unchanged if the check is False. */
bool check_subboard(int r, int c, char digit, char board[9][9]) {

        /* divide by 3 to get sub-board's position without considering the positions on the sub-boards */
        int R = r/3;
        int C = c/3;

	/* 2 for-loops to move across the subboard for the check, starting from the top left position within the subboard*/
        for (int i = R*3; i < R*3+3; i++) {
                for (int j = C*3; j < C*3+3; j++) {
			/* skip if it's the requested position */
                        if ((i == r) && (j == c))
                                continue;

                        if (board[i][j] == digit)
                                return false;
                }
        }
        return true;
}
/* end of function */



/* Function that saves and outputs two_dimensional character array board as a .dat file */
/* @param filename: Name of the file that contains the board.
 * @param board: Board to be output as a .dat file.
 * @return True: if board output as a .dat file succesfully. False: if it outputs unsuccessfully. */
bool save_board(const char* filename,char board[9][9]) {
        
	ofstream out_stream;
        
        out_stream.open(filename);
        
	if (out_stream.fail())
                return false;
        
	else {
                for (int i=0; i<9; i++){
                        for (int j=0; j<9; j++) {
                                out_stream << board[i][j];
                        }
			out_stream << endl;
                }
        }

	out_stream.close();
        
	return true;
}
/* end of function*/



/* Function that solves sudoku board */
/* @param board: Board to be solved.
 * @return True: if the board can be solved. False: if the board cannot be solved and board remains unchanged. */
bool solve_board(char board[9][9]) {

	char position[2];
        
	/* stop the recursion once the board is filled with valid numbers */
        if (is_complete(board))
                return true;
                
        for (int r=0; r<9; r++) {
                for (int c=0; c<9; c++) {

			position[0] = 'A'+r;
			position[1] = '1'+c;

                        if(!check_value(board[r][c])) {
                                for(int value='1'+0; value < '1'+9; value++) {
				        if (make_move(position, value, board)) {
                                                board[r][c]=value;       	
					        /* Carry out recursion to move on to the next position and attempts to solve the next position */
					        if (solve_board(board))
						        return true;
					        /* backtracks and replace the position with the empty position value if the latest position has no valid number while the board remains unsolved. */
					        board[r][c]='.';
				}
			} 
                        return false;
			}
		}
	}
        return false;
}
/* end of function */



/* Functions below are for question 5 (not for marking) */

/* Function that provide the values used for comparison. It calculates the number of times the solve_board function is called and the maximum number of permutations by multiplying the number of valid numbers in each empty cell all together (using a helper function). */
/* @params filename: .dat file that contains the board to be solved and checked. 
 * @return: void. It will display the solved board, number of permutations, number of possible solutions in each empty cell and number of time the solve_board function is called */
void compare_board(const char* filename) {
	char board[9][9];
	int count = 0;
	long double permutation = 1;

	load_board(filename, board);
	if (solve_board_with_count(board, count)) {
		cout << "The " << filename << " board has a solution:\n";
		display_board(board);
		cout << "Recursion Count: " << count << endl;
		load_board(filename, board);
		permutation_count(board, permutation);
		cout << filename << " solution count for each cell: " << endl;
		display_board(board);
		cout << "Permutation count for " << filename << ": " << permutation << "\n";
	} 
	else {
		cout << "A solution cannot be found.\n";
	}
	cout << '\n';
}
/* end of function */

/* Helper function that solves the board and counts the number of the times the function is called (recursion count) */
/* @param board: Board to be solved.
 * @param count: reference to the 'count' integer passed from the calling function 'compare_board', which is a counter for the number of time the function was called
 * @return True: if the board can be solved. False: if the board cannot be solved and board remains unchanged. */
bool solve_board_with_count(char board[9][9], int &count) {

        char position[2];

        /* counter that increases by 1 everytime the function is called */
        count++;

        /* ending condition to stop the recursion from going depper when the board is filled */
        if (is_complete(board))
                return true;

        /* attempt to solve the board */
        for (int r=0; r<9; r++) {
                for (int c=0; c<9; c++) {

                        position[0] = 'A'+r;
			position[1] = '1'+c;

                        /* check if the position is filled before attempting to solve with a number, move on to the next position if the position is filled. */
                        if (!check_value(board[r][c])) {
                                /* attempts to try every character from '1' to '9' to check if the digit can be placed at the position. */
                                for(int value='1'+0; value <= '1'+8; value++){
                                        /* check if the digit is valid to be placed at the position of the current loop */
                                        if (make_move(position, value, board)){
                                                board[r][c]=value;
                                                /* Carry out recursion to move on to the next position and attempts to solve the next position */
                                                if (solve_board_with_count(board, count))
                                                        return true;
                                                /* backtracks and replace the position with the empty position value if the latest position has no valid number while the board remains unsolved. */
                                                board[r][c]='.';
                                        }
                                } 
                                return false;
                        }
                }
        }
        return false;
}
/* end of function */

/* Helper function that counts the number of possible solution in each of the empty cell and the total number of possible ways to fill up the empty cells with valid numbers (be it wrong or correct). */
/* @param board: Board to be checked.
 * @param permutation: reference to the 'permutation' long double from the calling function 'compare_board', which will give the number of possible ways to fill up the empty cells with valid numbers.
 * @return: void. It will fill up the empty cells with the number of valid numbers for each empty cell and remove the given numbers in the pre-filled cell . It will also update the 'permutation' referenced. */
void permutation_count(char board[9][9], long double &permutation) {

        char board_copy[9][9];

        /* Store the board with pre-filled positions in a copy for reference */
        for (int r=0; r<9; r++) {
                for (int c=0; c<9; c++) {
                        board_copy[r][c] = board[r][c];
                }
        }

        /* attempt to solve the board */
        for (int r=0; r<9; r++) {
                for (int c=0; c<9; c++) {
                        /* check if the position is filled before attempting to solve with a number, move on to the next position if the position is filled. */
                        if (!check_value(board_copy[r][c])) {
                                /* initiates a counter everytime the function reaches a new position */
                                int possible_ans_count=0;
                                /* attempts to try every character from '1' to '9' to check if the digit can be placed at the position. */
                                for(int value='1'+0; value < '1'+9; value++) {
                                        /* check if the digit is valid to be placed at the position of the current loop */
                                        if (check_row_column(r, c, value, board_copy) && check_subboard(r, c, value, board_copy)){
                                                possible_ans_count++;
                                        }
                                        board[r][c] = possible_ans_count + '0';
                                }
                                if (possible_ans_count != 0)
                                permutation *= possible_ans_count;
                        }
                        else
                                board[r][c] = '.';
                }
        }

}
/* end of function */