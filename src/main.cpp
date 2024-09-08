#include <QApplication>


#include <iostream>

#include "MainWindow.h"



int main(int argc, char** argv){
    QApplication app(argc, argv);
    
    MainWindow mainWin;
    mainWin.show();
    return QApplication::exec();
}
