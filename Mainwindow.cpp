#include "Mainwindow.h"
#include "customDelegate.h"
#include <QHeaderView>
#include <QAbstractItemView>
#include <QMessageBox>
#include "sudokuvaliditychecker.h"



Mainwindow::Mainwindow(QMainWindow* parent)
    : QMainWindow(parent) {

    MainFrame = new QFrame(this); 
    //initializing the main frame


    solveButton = new QPushButton("Solve",MainFrame);
    clearButton = new QPushButton("Clear Board", MainFrame);
   // initializing the buttons
    
    sudokuTable = new QTableWidget(MainFrame);
    
 
    sudokuTable->setColumnCount(9);
    sudokuTable->setRowCount(9);
    sudokuTable->setFixedWidth(497);
    sudokuTable->setFixedHeight(497);
    // initilizing the table and settings up the lengths/widths and rows/cols

    for (int c = 0; c < 9; c++) { // customizing the dimensions for each cell in sudokutable
        sudokuTable->setRowHeight(c, 55);
        sudokuTable->setColumnWidth(c, 55);
    }

    sudokuTable->horizontalHeader()->setVisible(false);
    sudokuTable->verticalHeader()->setVisible(false);
    
    sudokuTable->setItemDelegate(new customDelegate);
    // using a custome delegate and removing horizontal/vertical labels from the table

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            QTableWidgetItem* temp = new QTableWidgetItem("");
            temp->setFont((QFont("Arial", 25, QFont::Bold)));
            temp->setTextAlignment(Qt::AlignCenter);
            // filling each cell with an empty string of Qtablewidgetitem, effectively a qlineedit

            if (((j < 3 || j>5) && (i < 3)) || ((j < 3 || j>5) && (i > 5)) || ((j > 2 && j < 6) && (i < 6 && i>2))) {
                temp->setBackground(QBrush(Qt::yellow));
            }
            else {
                temp->setBackground(QBrush(Qt::darkGreen));
            } 
            //coloring every 3x3 in the table a different color

            sudokuTable->setItem(i, j, temp);
            // adding the item to the sudokutable
           
        }
    }



    mainhbox = new QHBoxLayout(MainFrame);
    mainvbox = new QVBoxLayout(MainFrame);
    mainhbox->addWidget(sudokuTable);
    mainhbox->addLayout(mainvbox);
    // adding the table and the button's vertical layout to the horizontal one



    mainvbox->addWidget(clearButton);
    mainvbox->addWidget(solveButton);
    // adding buttons on the vertical layout
   

    setCentralWidget(MainFrame);
    // setting the frame as a central wdiget


    connect(clearButton, &QPushButton::clicked, this, &Mainwindow::clearBoard);
    //connecting clear button to the clearboard func
    connect(solveButton, &QPushButton::clicked, this, &Mainwindow::checkIfboardValid);
    //connecting solve button to checkifboard is valid func when then triggeres solving of the board if it is valid
    

}


void Mainwindow::mousePressEvent(QMouseEvent* e){ //mouse event to clear the selection on the table,
    int x = e->pos().x();
    int y = e->pos().y();
    if (((x <= 8) || (x >= 505)) || ((y <= 8) || (y >= 505))) {
        sudokuTable->clearSelection();
    }
    // a cosmetic change which allows users to unselect the board when clicking outside of it
}

std::vector<std::vector<char>> Mainwindow::getCurrentBoard(){ // generates a 2d vector with '0's and replaces them with the numbers given on the board and returns that value

    std::vector<std::vector<char>> currentBoard = {
        {'0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0'}
    }; // creating an empty 2d vector for the board

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char temp = sudokuTable->item(i, j)->text().toStdString().c_str()[0];
            if (temp != '\0') {
                currentBoard.at(i).at(j) = temp;
            }
            
        }
    }
    // replacing all values from the sudokutable into the board

    return currentBoard;
}

void Mainwindow::clearBoard(){ //sets every cell of the table to an empty string to effectively clear the board 
    sudokuTable->clearSelection();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudokuTable->item(i, j)->setText("");
        }
    }
}


void Mainwindow::checkIfboardValid() { // checks if the board is valid to solve or not. Dispalys a Warning message if not Valid, otherwise solves the sudoku
    sudokuTable->clearSelection(); // clearing table selection for cosmetic purposes

    std::vector<std::vector<char>> checkBoard(getCurrentBoard()); // getting the current board
    if (!checkValidity(checkBoard)) {
        QMessageBox::information(
            this,
            tr("Sudoku Validator"),
            tr("The Current Sudoku Puzzle is not Valid."));

        return;
    }
    
    solveSudoku(); // solves sudoku when board is valid
    
}


void Mainwindow::solveSudoku(){ // Attemps to solve the board. If solved it displays the solved board onto the sudokutable otherwise displays an error saying the board in not solvable

    std::vector<std::vector<char>> solution(getCurrentBoard()); // getting the current board
    if (!solving(solution, 0, 0)) { // if solving failed
        QMessageBox::critical(
            this,
            tr("Sudoku Solver"),
            tr("The Current Sudoku Puzzle is not Solvable."));
        return;
    }

    displaySolvedBoard(solution);
    //displaying the solved board
    
}

void Mainwindow::displaySolvedBoard(std::vector<std::vector<char>> solvedboard){ // takes the solved board as a param and displays it onto the sudokutable
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudokuTable->item(i, j)->setText(QString(solvedboard.at(i).at(j)));
        }
    }

}

