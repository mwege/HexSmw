#ifndef _ASMEDITORWIDGET_H_
#define _ASMEDITORWIDGET_H_

#include <QWidget>

#include "capstone/capstone.h"

class AsmEditorWidget : public QWidget{
public:
    explicit AsmEditorWidget(QByteArray& fileContent);
    
    void setOffset(uint64_t offsetValue);
    void setFileContent(QByteArray& fileContent);

private:
    uint64_t _offset;
    QByteArray& _fileContent;
    QPointF _lastClick;

    cs_arch _capstoneArchType;
    cs_mode _capstoneArchMode;


protected:
    void paintEvent(QPaintEvent*) override;
    void mouseReleaseEvent(QMouseEvent *) override;

public slots:
    void onArchitectureChange(QString architectureIdentifierString);
};


#endif