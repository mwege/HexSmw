#include "ToolbarWidget.h"
#include <QComboBox>
#include <QLabel>
#include <QOverload>

ToolbarWidget::ToolbarWidget(QWidget* parent) : QToolBar(parent) {
    addSeparator();

    QLabel* lbSelectAsmArchitecture = new QLabel("Architecture");
    QComboBox* cbSelectAsmArchitecture = new QComboBox(this);
    cbSelectAsmArchitecture->addItem("x86 (16 bit)");
    cbSelectAsmArchitecture->addItem("x86 (32 bit)");
    cbSelectAsmArchitecture->addItem("x86 (64 bit)");
    addWidget(lbSelectAsmArchitecture);
    addWidget(cbSelectAsmArchitecture);
    addSeparator();

    connect(cbSelectAsmArchitecture, &QComboBox::currentTextChanged, this, &ToolbarWidget::onArchtectureComboBoxHasChanged);
}

void ToolbarWidget::onArchtectureComboBoxHasChanged(QString architectureIdentString) {
    qDebug() << "ToolbarWidget::onArchtectureComboBoxHasChanged";
    emit disassemblerArchitectureChanged(architectureIdentString); 
}