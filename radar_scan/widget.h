#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setPoint(double x , double y) ;
    void setPoint(const QPointF &point) ;
private:
    void changeScanerRegion(double start_angle) ;
    void drawBackground() ;
    void paintEvent(QPaintEvent *e) ;
private:
    Ui::Widget *ui;
    QPointF *_mid_point ;
    QRect *_rader_rect ;
    QPolygonF *_scanning_region ;
    int _max_radius ;
    double _start_angle ;
    double _angle_delt ;
    QPointF *_target_point ;
    QColor _color_current ;
    QColor _color_last ;
};

#endif // WIDGET_H
