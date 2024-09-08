#ifndef _HEXWIDGET_H_
#define _HEXWIDGET_H_

#include <QWidget>
#include <QTextEdit>
#include <QStackedWidget>

#include <memory>

// class QFile;
#include <QFile>
class HexEditorWidget;
class AsmEditorWidget;

class EditorStackWidget : public QStackedWidget{
    Q_OBJECT
public:
    enum ViewMode { DisplayAsm, DisplayHex};

    explicit EditorStackWidget(QWidget* parent);
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
    QPointF lastClick;
    ViewMode mode;
    uint64_t offset;

    HexEditorWidget* _hexEditorWidget;
    AsmEditorWidget* _asmEditorWidget;

public slots:
    void onArchitectureChange(QString);

signals:
    void architectureChange(QString);
};
#endif