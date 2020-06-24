#ifndef Mainwindow_HEADER
#define Mainwindow_HEADER


#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QMouseEvent>
#include "sudokusolver.h"


class Mainwindow : public QMainWindow {

    Q_OBJECT

public:
    Mainwindow(QMainWindow* parent = 0);

private:

    QPushButton* solveButton; // button to solve sudoku
    QPushButton* clearButton; // button to clear the table
    QTableWidget* sudokuTable;    // table widget to hold the sudoku table
    QFrame* MainFrame; // the mainframe displayed
    QHBoxLayout* mainhbox; // horizontal layout
    QVBoxLayout* mainvbox;  // vertical layout for buttons
    std::vector<std::vector <char>> getCurrentBoard(); // returns the current board in a 2d vector of char
    void clearBoard(); // clears the board
    void checkIfboardValid(); // checks if the sudoku rules are followed before initiating solving
    void solveSudoku(); // solves sudoku using the current board
    void displaySolvedBoard(std::vector<std::vector <char>> solution); // displays the solution on the board
    void mousePressEvent(QMouseEvent* e); //mouse event to clear seletion of table

};

#endif