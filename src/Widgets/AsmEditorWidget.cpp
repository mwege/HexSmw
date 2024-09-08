#include "AsmEditorWidget.h"
#include <QMouseEvent>
#include <QPainter>


AsmEditorWidget::AsmEditorWidget(QByteArray& fileContent)  : _fileContent(fileContent), _offset(0){
    _capstoneArchType = CS_ARCH_X86;
    _capstoneArchMode = CS_MODE_16;
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
    cs_err err = cs_open(_capstoneArchType, _capstoneArchMode, &handle);
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

void AsmEditorWidget::onArchitectureChange(QString architectureIdentString){

    qDebug() << "AsmEditorWidget::onArchitectureChange";
    QMap<QString, QPair<cs_arch, cs_mode> > archMapStringToTypeModeTuple;
    archMapStringToTypeModeTuple["x86 (16 bit)"] = QPair<cs_arch, cs_mode>(CS_ARCH_X86, CS_MODE_16);
    archMapStringToTypeModeTuple["x86 (32 bit)"] = QPair<cs_arch, cs_mode>(CS_ARCH_X86, CS_MODE_32);
    archMapStringToTypeModeTuple["x86 (64 bit)"] = QPair<cs_arch, cs_mode>(CS_ARCH_X86, CS_MODE_64);

    if (archMapStringToTypeModeTuple.contains(architectureIdentString)){
        QPair<cs_arch, cs_mode> archTuple = archMapStringToTypeModeTuple.value(architectureIdentString);
        _capstoneArchType = archTuple.first;
        _capstoneArchMode = archTuple.second;
        qDebug() << "Set " << architectureIdentString;
    } else {
        qDebug() << "invalid arch";
    }
    update();
}