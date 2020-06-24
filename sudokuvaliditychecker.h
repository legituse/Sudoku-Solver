#ifndef sudokuvaliditychecker_HEADER
#define sudokuvaliditychecker_HEADER

#include <vector>
#include <QMap>



bool checkValidityRows(std::vector<std::vector<char>> board) { // uses a QMap to check each row of the board to find duplicate numbers. If found duplicate returns false else it is true
	QMap <char, int> rows;
	for (int c = 0; c < 9; c++) {
		rows.clear();
		for (int i = 0; i < 9; i++) {
			if (board.at(c).at(i) != '0') {
				if (rows.contains(board.at(c).at(i))) {
					return false;
				}
				rows.insert(board.at(c).at(i), 1);
			}
		}
	}
	return true;
}

bool checkValidityCols(std::vector<std::vector<char>> board) { // uses a QMap to check each column of the board to find duplicate numbers.  If found duplicate returns false else it is true

	QMap <char, int> cols;
	for (int c = 0; c < 9; c++) {
		cols.clear();
		for (int i = 0; i < 9; i++) {
			if (board.at(i).at(c) != '0') {
				if (cols.contains(board.at(i).at(c))) {
					return false;
				}
				cols.insert(board.at(i).at(c), 1);
			}
		}
	}
	return true;
}

bool checkVailiditySquare(std::vector<std::vector<char>> board) { // uses a QMap to check each 3x3 of the sudoku table to find duplicate numbers.  If found duplicate returns false else it is true

	QMap <char, int> square;
	int startcol = 0;
	int startrow = -3;
	for (int c = 0; c < 9; c++) {
		if (startrow > 5) {
			startrow = -3;
			startcol += 3;
		}
		startrow += 3;

		square.clear();
		for (int i = startcol; i < startcol + 3; i++) {
			for (int j = startrow; j < startrow + 3; j++) {
				if (board.at(i).at(j) != '0') {
					if (square.contains(board.at(i).at(j))) {
						return false;
					}
					square.insert(board.at(i).at(j), 1);
				}
			}
		}

	}
	return true;

}



bool checkValidity(std::vector<std::vector<char>>& board) { // a central function which combines checking validity of the 3x3, rows and column of the board and returns true / false based on its validity
	return checkValidityCols(board) && checkValidityRows(board) && checkVailiditySquare(board);
}

#endif