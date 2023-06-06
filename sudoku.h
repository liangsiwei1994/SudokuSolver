#ifndef SUDOKU_H
#define SUDOKU_H

/* pre-loaded functions */
void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* user-defined functions */

/* declaration of 'is_complete' function for question 1. */
bool is_complete(char board[9][9]);

/* declaration of 'make_move' function for question 2. */
bool make_move(const char* position, char digit, char board[9][9]);
/* declaration of 'check_value', helper function of 'make_move' */
bool check_value(char value);
/* declaration of 'check_position', helper function of 'make_move' */
bool check_position(int r, int c);
/* declaration of 'check_row_column', helper function of 'make_move' */
bool check_row_column(int r, int c, char digit, char board[9][9]);
/* declaration of 'check_subboard', helper function of 'make_move' */
bool check_subboard(int r, int c, char digit, char board[9][9]);

/* declaration of 'save_board' function for question 3 */
bool save_board(const char* filename,char board[9][9]);

/* declaration of 'solve_board' function for question 4 */
bool solve_board(char board[9][9]);

/* declaration of 'compare_board' function for question 5 */
void compare_board(const char* filename);
/* declaration of 'solve_board_with_count', helper function of 'compare_board' */
bool solve_board_with_count(char board[9][9], int &count);
/* declaration of 'permutation_count', helper function of 'compare_board' */
void permutation_count(char board[9][9], long double &permutation);

#endif