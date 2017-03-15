#ifndef INFORMATION_WIDGET_H
#define INFORMATION_WIDGET_H

#include <QWidget>

namespace Ui {
class InformationWidget;
}

class InformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InformationWidget(QWidget *parent = 0);
    ~InformationWidget();

private:
    Ui::InformationWidget *ui;
};

#endif // INFORMATION_WIDGET_H
