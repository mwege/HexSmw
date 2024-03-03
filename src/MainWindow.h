#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_



#include <QMainWindow>


class HexViewWidget;
class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
    MainWindow();
    void createActions();
    void createMenus();

    private:
    HexViewWidget* _centralWidget;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QAction *openAct;
    QAction *displayAsmAct;
    QAction *displayHexAct;

private slots:
    void openFile();
    void displayAsm();
    void displayHex();

    protected:
     bool eventFilter(QObject *obj, QEvent *event);
};

#endif