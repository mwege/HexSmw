#ifndef _HEXTOOLBARWIDGET_H_
#define _HEXTOOLBARWIDGET_H_

#include <QToolBar>

class ToolbarWidget : public QToolBar {
    Q_OBJECT

    public:
    explicit ToolbarWidget(QWidget* parent);

    private slots:
    void onArchtectureComboBoxHasChanged(QString archIdentifierString);

    signals:
    void disassemblerArchitectureChanged(QString archIdentifierString);
};

#endif