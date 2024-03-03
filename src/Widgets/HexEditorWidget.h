#ifndef _HEXEDITORWIDGET_H_
#define _HEXEDITORWIDGET_H_

#include <QWidget>


class HexEditorWidget : public QWidget{
public:
    explicit HexEditorWidget(QByteArray& fileContent);
    QString generateHexLine(int offset);
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