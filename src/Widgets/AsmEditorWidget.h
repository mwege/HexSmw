#ifndef _ASMEDITORWIDGET_H_
#define _ASMEDITORWIDGET_H_

#include <QWidget>


class AsmEditorWidget : public QWidget{
public:
    explicit AsmEditorWidget(QByteArray& fileContent);
    
    void setOffset(uint64_t offsetValue);
    void setFileContent(QByteArray& fileContent);

private:
    uint64_t _offset;
    QByteArray& _fileContent;
    QPointF _lastClick;

protected:
    void paintEvent(QPaintEvent*) override;
    void mouseReleaseEvent(QMouseEvent *) override;
};


#endif