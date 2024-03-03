#include "HexEditorWidget.h"
#include <QMouseEvent>
#include <QPainter>

HexEditorWidget::HexEditorWidget(QByteArray& fileContent)  : _fileContent(fileContent), _offset(0){
    
}

QString HexEditorWidget::generateHexLine(int offset){
    QString hexValueRegion = "";
    QString asciiRegion = "";

    for (int i = offset; i < offset + 32 && i < _fileContent.size(); i++) {
        int b = _fileContent[i];

        asciiRegion += isprint(b)?QChar(b):'.';
        QString h = QString("%1 ").arg(b, 2, 16, QChar('0')).toUpper();
        hexValueRegion += h;
        
    }
    QString address = QString("0x%1 ").arg(offset,8,16, QChar('0')).toUpper();

    return address + hexValueRegion + "    " + asciiRegion;
}

void HexEditorWidget::setOffset(uint64_t offsetValue){
    _offset = offsetValue;
    update();
}

void HexEditorWidget::setFileContent(QByteArray& fileContent){
    _fileContent = fileContent;
    update();
}


void HexEditorWidget::paintEvent(QPaintEvent* ev){
   QPainter painter(this);

    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(QGradient(QGradient::AfricanField)));
    
    int width = size().width() - 3;
    int height = size().height() - 5;
    painter.fillRect(0, 0, width, height, QColor(220,220,220));

    QFont font("Courier New", 12);
    QFontMetrics fm(font);
    painter.setFont(font);
    int start = fm.height();

    int hexline = 0 + _offset;
    while (start + fm.height() < height ) {
        painter.drawText(10, start, generateHexLine(hexline));
        hexline += 16;
        start += fm.height();
    }

    painter.fillRect((int)_lastClick.x(), (int)_lastClick.y(), 10, 10, QColor(255, 0, 0));
    
    //painter.drawText(10, 10, "Machine " + QString::number(0));
    qDebug() << "paintEvent" << width << " , " << height;
}

void HexEditorWidget::mouseReleaseEvent(QMouseEvent *ev) {
    QPointF pos = ev->position();
    _lastClick = pos;
    update();
}
