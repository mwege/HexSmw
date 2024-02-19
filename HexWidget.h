#ifndef _HEXWIDGET_H_
#define _HEXWIDGET_H_

#include <QWidget>
#include <QTextEdit>

#include <memory>

class QFile;

class HexWidget : public QWidget{
public:
    enum ViewMode { DisplayAsm, DisplayHex};

    explicit HexWidget(QWidget* parent);
    virtual void setFile(QString pathToFile);
    virtual void setMode(ViewMode mode);

    void decreaseOffsetByOne();
    void increaseOffsetByOne();
    void increaseOffsetByLine();
    void decreaseOffsetByLine();
    
private:
    QString _currentPathToFile;
    QByteArray _currentFileContent;
    
    std::unique_ptr<QFile> _currentFile;

private:
    QString generateHexLine(int offset);

    QPointF lastClick;
    ViewMode mode;
    uint64_t offset;

    void paintHexView(QPaintEvent* ev);
    void paintAsmView(QPaintEvent* ev);

protected:
    void paintEvent(QPaintEvent*) override;
    void mouseReleaseEvent(QMouseEvent *) override;

};
#endif