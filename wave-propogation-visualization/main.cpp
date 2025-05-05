#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Initializes Qt
    MainWindow w;               // creates the main window
    w.show();                   // displays the window
    return a.exec();            // starts the event loop
}
