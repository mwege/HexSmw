#include "EditorStackWidget.h"
#include "capstone/capstone.h"

#include <QFile>
#include <QPainter>
#include <QMouseEvent>
#include <QFontDatabase>

#include "AsmEditorWidget.h"
#include "HexEditorWidget.h"

EditorStackWidget::EditorStackWidget(QWidget *parent) {

    auto fonts = QFontDatabase();
    auto names = fonts.families();
    for (QString n : names) {
        qDebug() << n;
    }
    
    _asmEditorWidget = new AsmEditorWidget(_currentFileContent);
    _hexEditorWidget = new HexEditorWidget(_currentFileContent);
    addWidget(_hexEditorWidget);
    addWidget(_asmEditorWidget);
}

void EditorStackWidget::setFile(QString pathToFile) {
    _currentFile = std::make_unique<QFile>(pathToFile);
    _currentFile->open(QIODeviceBase::ReadOnly);
    _currentFileContent = _currentFile->readAll();
    offset = 0;
    _hexEditorWidget->setFileContent(_currentFileContent);
    _asmEditorWidget->setFileContent(_currentFileContent);

}

void EditorStackWidget::setMode(ViewMode mode){
    switch(mode) {
        case ViewMode::DisplayAsm:
            this->mode = mode;
            setCurrentIndex(1);
            break;
        default:
            [[fallthrough]];
        case ViewMode::DisplayHex:
            // todo setup hex view
            this->mode = mode;
            setCurrentIndex(0);
            break;
    }
    update();
}

void EditorStackWidget::decreaseOffsetByLine(){
    if ( (static_cast<int64_t>(offset) - 16) > 0) {
        offset -= 16;
    } else {
        offset = 0;
    }
    qDebug() << "-16" << offset;
    _asmEditorWidget->setOffset(offset);
    _hexEditorWidget->setOffset(offset);
    update();
}

void EditorStackWidget::decreaseOffsetByOne(){
    if (offset > 0) {
        offset--;
    }
    qDebug() << "--" << offset;
    _asmEditorWidget->setOffset(offset);
    _hexEditorWidget->setOffset(offset);
    update();
}

void EditorStackWidget::increaseOffsetByOne(){
    offset++;
    qDebug() << "++" << offset;
    _asmEditorWidget->setOffset(offset);
    _hexEditorWidget->setOffset(offset);
    update();
}

void EditorStackWidget::increaseOffsetByLine(){
    offset += 16;
    qDebug() << "+16" << offset;
    _asmEditorWidget->setOffset(offset);
    _hexEditorWidget->setOffset(offset);
    update();
}