#include "HexWidget.h"
#include "capstone/capstone.h"

#include <QFile>
#include <QPainter>
#include <QMouseEvent>
#include <QFontDatabase>

HexWidget::HexWidget(QWidget *parent) {
    setFile("/Users/mwege/x.txt");

    auto fonts = QFontDatabase();
    auto names = fonts.families();
    for (QString n : names) {
        qDebug() << n;
    }
}

void HexWidget::setFile(QString pathToFile) {
    _currentFile = std::make_unique<QFile>(pathToFile);
    _currentFile->open(QIODeviceBase::ReadOnly);
    _currentFileContent = _currentFile->readAll();
    offset = 0;

}

void HexWidget::setMode(ViewMode mode){
    switch(mode) {
        case ViewMode::DisplayAsm:
            this->mode = mode;
            break;
        default:
            [[fallthrough]];
        case ViewMode::DisplayHex:
            // todo setup hex view
            this->mode = mode;
            break;
    }
    update();
}

QString HexWidget::generateHexLine(int offset) {
    QString hexValueRegion = "";
    QString asciiRegion = "";

    //qDebug() <<  _currentFileContent;
    for (int i = offset; i < offset + 32 && i < _currentFileContent.size(); i++) {
        int b = _currentFileContent[i];

        asciiRegion += isprint(b)?QChar(b):'.';
        QString h = QString("%1 ").arg(b, 2, 16, QChar('0')).toUpper();
        hexValueRegion += h;
        
    }
    QString address = QString("0x%1 ").arg(offset,8,16, QChar('0')).toUpper();

    return address + hexValueRegion + "    " + asciiRegion;
}


void HexWidget::paintEvent(QPaintEvent* ev){
    if (mode == ViewMode::DisplayAsm) {
        paintAsmView(ev);
    } else {
        paintHexView(ev);
    }
}


void HexWidget::paintHexView(QPaintEvent* ev){
    QPainter painter(this);

    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(QGradient(QGradient::AfricanField)));
    
    painter.drawLine(QLine( 0, 0, 100, 100));
   // painter.setBackground(QBrush(QGradient(QGradient::AfricanField)));
    int width = size().width() - 3;
    int height = size().height() - 5;
    painter.fillRect(0, 0, width, height, QColor(220,220,220));

    QFont font("Courier New", 12);
    QFontMetrics fm(font);
    painter.setFont(font);
    int start = fm.height();

    int hexline = 0 + offset;
    while (start + fm.height() < height ) {
        painter.drawText(10, start, generateHexLine(hexline));
        hexline += 16;
        start += fm.height();
    }

    painter.fillRect((int)lastClick.x(), (int)lastClick.y(), 10, 10, QColor(255, 0, 0));
    
    //painter.drawText(10, 10, "Machine " + QString::number(0));
    qDebug() << "paintEvent" << width << " , " << height;
}

void HexWidget::paintAsmView(QPaintEvent* ev){
    QPainter painter(this);

    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(QGradient(QGradient::AfricanField)));
    
    painter.drawLine(QLine( 0, 0, 100, 100));


    const char* _currentFileAsCharArray = _currentFileContent.constData();

    csh handle;
    cs_insn *isn;
    ///cs_err err = cs_open(CS_ARCH_X86, CS_MODE_64, &handle);
    cs_err err = cs_open(CS_ARCH_X86, CS_MODE_16, &handle);
    int count = 0;
    int file_size = _currentFileContent.size();
    int lastBytes = file_size - offset;
    count = cs_disasm(handle, ((const uint8_t *) _currentFileAsCharArray) + offset, file_size - offset , 0x0000 + offset, 300, &isn);
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


void HexWidget::mouseReleaseEvent(QMouseEvent *ev) {
    QPointF pos = ev->position();
    lastClick = pos;
    update();
}

void HexWidget::decreaseOffsetByLine(){
    if ( (static_cast<int64_t>(offset) - 16) > 0) {
        offset -= 16;
    } else {
        offset = 0;
    }
    qDebug() << "-16" << offset;
    update();
}

void HexWidget::decreaseOffsetByOne(){
    if (offset > 0) {
        offset--;
    }
    qDebug() << "--" << offset;
    update();
}

void HexWidget::increaseOffsetByOne(){
    offset++;
    qDebug() << "++" << offset;
    update();
}

void HexWidget::increaseOffsetByLine(){
    offset += 16;
    qDebug() << "+16" << offset;
    update();
}