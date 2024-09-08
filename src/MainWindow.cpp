#include "MainWindow.h"

#include <QMenuBar>
#include <QFileDialog>
#include <QEvent>
#include <QKeyEvent>
#include <QWheelEvent>

#include "EditorStackWidget.h"
#include "ToolbarWidget.h"

MainWindow::MainWindow() : _centralWidget(new EditorStackWidget(this)) {
    setCentralWidget(_centralWidget);
    ToolbarWidget* toolbarMainWindow = createToolbar();

    connect(toolbarMainWindow, &ToolbarWidget::disassemblerArchitectureChanged, _centralWidget, &EditorStackWidget::onArchitectureChange);

    addToolBar(toolbarMainWindow);

    createActions();
    createMenus();

    installEventFilter(this);

}

ToolbarWidget* MainWindow::createToolbar() {
    ToolbarWidget* toolbar = new ToolbarWidget(this);
    openAct = new QAction(tr("&Open"), toolbar);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
    return toolbar;
}

void MainWindow::createActions() {
    openAct = new QAction(tr("&Open"), this);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
    
    displayAsmAct = new QAction(tr("Assembler"), this);
    connect(displayAsmAct, &QAction::triggered, this, &MainWindow::displayAsm);
    
    displayHexAct = new QAction(tr("Hex"), this);
    connect(displayHexAct, &QAction::triggered, this, &MainWindow::displayHex);
    

}

void MainWindow::createMenus() {
    
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(displayAsmAct);
    viewMenu->addAction(displayHexAct);

    
}


void MainWindow::openFile() {
    QFileDialog dialog(this);
    QStringList fileNames;
    if (dialog.exec())
     fileNames = dialog.selectedFiles();
     _centralWidget->setFile(fileNames[0]);

}


void MainWindow::displayAsm(){
    _centralWidget->setMode(EditorStackWidget::ViewMode::DisplayAsm);
}

void MainWindow::displayHex(){
     _centralWidget->setMode(EditorStackWidget::ViewMode::DisplayHex);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{   
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        switch(keyEvent->key()) {
            case Qt::Key_Left:
                _centralWidget->decreaseOffsetByOne();
                qDebug() << "left";
                break;
            case Qt::Key_Right:
                _centralWidget->increaseOffsetByOne();
                qDebug() << "right";
                break;
            case Qt::Key_Down:
                _centralWidget->increaseOffsetByLine();
                qDebug() << "down";
                break;
            case Qt::Key_Up:
                _centralWidget->decreaseOffsetByLine();
                qDebug() << "up";
                break;
            default:
            ;
        }
           qDebug() << "key " << keyEvent->key() << "from" << obj; 
    } else if (event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);
        
        
        QPoint numPixels = wheelEvent->pixelDelta();
        QPoint numDegrees = wheelEvent->angleDelta() / 8;

        if (!numPixels.isNull()) {
            bool negative = numPixels.y()<0;
            
            int numSteps = abs(numPixels.y())/ 10; // TODO FIX ME: USE FONT HEIGHT
            for (int i = 0; i < numSteps; i++) {
                if(!negative) {
                    _centralWidget->decreaseOffsetByLine();
                } else {
                    _centralWidget->increaseOffsetByLine();
                }
            }
        } else if (!numDegrees.isNull()) {
            
            QPoint numSteps = numDegrees / 15;
            bool negative = (numSteps.y()<0);
            for (int i = 0; i < numSteps.y(); i++) {
                if(!negative) {
                    _centralWidget->decreaseOffsetByLine();
                } else {
                    _centralWidget->increaseOffsetByLine();
                }
            }
                
        }

    event->accept();
        
            
    }
    return QObject::eventFilter(obj, event);
}