#include "Mainwindow.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    //creating the QApp
    Mainwindow window;
    // creating the main window
    window.resize(600, 400);
    window.setWindowTitle("Sudoku Solver");
    window.show();

    return app.exec();
}