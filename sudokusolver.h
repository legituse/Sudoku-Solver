#ifndef sudokusolver_HEADER
#define sudokusolver_HEADER


#include <vector>

bool rowandcolvalchecker(std::vector<std::vector<char>>& board, int x, int y, char val); // checks if value given to the function is valid at the specific row and column of the 2d vector of the board
bool squarevalcheck(std::vector<std::vector<char>> & board, int x, int y, char val);  // checks if value given to the function is valid at the specific x and y in its 3x3 square of the 2d vector of the board
bool checkval(std::vector<std::vector<char>> & board, int x, int y, char val); // combines the func of row/col/square check into one main function
bool solving(std::vector<std::vector<char>> & solution, int x, int y); // a recursive backtracking algorithm to find a solution to the sudoku table

#endif