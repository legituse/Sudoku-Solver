#include "sudokusolver.h"


bool rowandcolvalchecker(std::vector<std::vector<char>>& board, int x, int y, char val) { // takes a char value and checks if placing it at the row and column of the x,y of the 2d vector is possible or not
    // returns true if it is possible , otherwise false
    for (int c = 0; c < board.size(); c++) {
        if (board.at(y).at(c) == val) { //checking x's
            return false;
        }
        if (board.at(c).at(x) == val) { //checking y's
            return false;
        }
    }
    return true;
}



bool squarevalcheck(std::vector<std::vector<char>>& board, int x, int y, char val) {// takes a char value and checks if placing it in the 3x3 square of the  x,y of the 2d vector is possible or not
    // returns true if it is possible , otherwise false
    int startcol = 3 * (y / 3);
    int startrow = 3 * (x / 3);

    for (int i = startcol; i < startcol + 3; i++) {
        for (int j = startrow; j < startrow + 3; j++) {
            if (board.at(i).at(j) == val) {
                return false;
            }
        }
    }

    return true;
}

bool checkval(std::vector<std::vector<char>>& board, int x, int y, char val) { // combines the function of checking for the rows, columns and square 3x3 at a given x,y with a value
    return rowandcolvalchecker(board, x, y, val) && squarevalcheck(board, x, y, val);
}


bool solving(std::vector<std::vector<char>>& solution, int x, int y) { // recursive backtracking algorithm to find a solution to the sudokutable
    // takes an empty/partially filled board with valid postions and an index x,y. where y is the row number and x is the column number
    for (std::vector<char> xd : solution) { // searches in the table to find an empty index aka '0' which indicates the sudoku table is not solved
        for (char d : xd) {
            if (d == '0') { // finds and empty index of '0'
                goto Break_Out; // breaks out of the nested for loops
            }
        }
    }
    return true; // returns true when no '0' index's in the 2d vector are found, implying the table is solved

Break_Out:

    if (x > 8) { // used to loop thru all the possible index's of the sudoku table in recursion. since each recursion calls adds one to X,  this allows y to increment to a new row when all values of a row have been checked
        y++;
        x = 0;
    }
    if (y > 8) { // when the row number exceeds 8 which is the last row, it means no solution has been found and returns false
        return false;
    }

    if (!(solution.at(y).at(x) == '0')) { // checks if the current row / column value isnt empty or isnt '0' and recurses the solving function again but incrementing the column number to find an index where it is empty.
        return (solving(solution, x + 1, y));
    }


    for (int i = 1; i < 10; i++) { // loops thru all the possible numbers in sudoku 1 to 9
        if (checkval(solution, x, y, '0' + i)) { // checks if the char value of '0' + i is placable at the given x,y of the index while following the rules
            solution.at(y).at(x) = '0' + i; // places the char value of at the x,y and replacing the previous empty value or '0'
            if (solving(solution, x, y)) {  // checks if placing that value at the given x,y returns a solved table if so, returns true
                return true;
            }
            else { // otherwise if placing that value doesnt lead to a solution, it makes the index empty again to try again with another value after one iteration of the forloop
                solution.at(y).at(x) = '0';
            }
        }
    }

    return false; //returns false if a solution is not reached after testing each value 1-9 in the forloop
    

}