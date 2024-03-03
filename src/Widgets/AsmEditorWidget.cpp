#include "AsmEditorWidget.h"
#include <QMouseEvent>
#include <QPainter>

#include "capstone/capstone.h"

AsmEditorWidget::AsmEditorWidget(QByteArray& fileContent)  : _fileContent(fileContent), _offset(0){
    
}

void AsmEditorWidget::setOffset(uint64_t offsetValue){
    _offset = offsetValue;
    update();
}

void AsmEditorWidget::setFileContent(QByteArray& fileContent){
    _fileContent = fileContent;
    update();
}


void AsmEditorWidget::paintEvent(QPaintEvent* ev){
  QPainter painter(this);

    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(QGradient(QGradient::AfricanField)));
    const char* _currentFileAsCharArray = _fileContent.constData();

    csh handle;
    cs_insn *isn;
    cs_err err = cs_open(CS_ARCH_X86, CS_MODE_16, &handle);
    int count = 0;
    int file_size = _fileContent.size();
    int lastBytes = file_size - _offset;
    count = cs_disasm(handle, ((const uint8_t *) _currentFileAsCharArray) + _offset, file_size - _offset , 0x0000 + _offset, 300, &isn);
    qDebug() << count;
    QFont font("Courier", 12);
    QFontMetrics fm(font);
    painter.setFont(font);
    int start = fm.height();

    if (count > 0) {
        
        for (int i = 0; i < count; i++) {
            QString line;
            //line.append(QString(isn[i].address));
            
            line.append(QString("%1").arg(isn[i].address,8,16, QChar('0')));
            line.append("  ");
            for (int j = 0; j < isn[i].size; j++) {
                line.append(QString("%1").arg(isn[i].bytes[j],2,16, QChar('0')));

            }
            line.append("  ");

            line.append(QString(isn[i].mnemonic));
            line.append(" ");
            line.append(QString(isn[i].op_str));
            line.append("  ");
            // append(line);
            painter.drawText(10, start, line);
            start += fm.height();
        }
    }
    cs_free(isn, count);
}

void AsmEditorWidget::mouseReleaseEvent(QMouseEvent *ev) {
    QPointF pos = ev->position();
    _lastClick = pos;
    update();
}
