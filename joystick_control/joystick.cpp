#include "joystick.h"
#include <QPainter>
#include <QPainterPath>
#include <QKeyEvent>
#include <QFont>
#include <QLinearGradient>
Joystick::Joystick(QWidget *parent) :
    QWidget(parent)
{
    this->setAllButtonUnpressed();
    this->init_SigSlot();
}

Joystick::~Joystick()
{
}

void Joystick::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e) ;
    QPainter paint(this) ;
    QPainterPath paint_path_mid ;
    QPainterPath paint_path_right_top ;
    QPainterPath paint_path_start_button ;
    QPainterPath paint_path_stop_button ;

    //draw the rect (container)
    paint.setPen(QPen(QBrush(QColor("#B22222")),8));
    paint.setBrush(QBrush(QColor("#F0E68C")));
    paint.drawRect(0,0,this->width(),this->height());

    //draw the round_rect at right top
    paint_path_mid.addRoundRect(this->width()*0.45,0,this->width()*0.7,this->height()*0.3,50) ;
    paint.setBrush(QBrush(QColor("#B22222")));
    paint.drawPath(paint_path_mid);


    //add two black line at the bottom
    paint.setPen(QPen(QBrush(QColor(Qt::black)),3)) ;
    paint.drawLine(QPoint(0+5,this->height()*0.7),QPoint(this->width()-5,this->height()*0.7)) ;
    paint.drawLine(QPoint(0+5,this->height()*0.8),QPoint(this->width()-5,this->height()*0.8));

    //add the round_rect in middle
    paint.setPen(QPen(QBrush(QColor("#B22222")),8));
    paint.setBrush(QBrush(QColor("#B22222")));
    paint_path_right_top.addRoundRect(this->width()*0.35,this->height()*0.4,this->width()*0.3,this->height()*0.2,30);
    paint.drawPath(paint_path_right_top);

   //draw the ABXY control button
    paint.setPen(QPen(QBrush(QColor("#B22222")),3));

    double radius = this->height()*0.08 ;

    //Button B
    this->_map_button[B] = this->ellipse2Rect(QPointF(this->width()*0.72,this->height()*0.5),radius) ;
    this->setBrushColor(B,this->_map_button[B],paint);
    paint.drawEllipse(QPointF(this->width()*0.72,this->height()*0.5),radius,radius);

    //Button Y
    this->_map_button[Y] = this->ellipse2Rect(QPointF(this->width()*0.93,this->height()*0.5),radius) ;
    this->setBrushColor(Y,this->_map_button[Y],paint);
    paint.drawEllipse(QPointF(this->width()*0.93,this->height()*0.5),radius,radius);

    //Button A
    this->_map_button[A] = this->ellipse2Rect(QPointF(this->width()*0.825,this->height()*0.3),radius) ;
   this->setBrushColor(A,this->_map_button[A],paint);
    paint.drawEllipse(QPointF(this->width()*0.825,this->height()*0.3),radius,radius);

    //Button X
    this->_map_button[X] = this->ellipse2Rect(QPointF(this->width()*0.825,this->height()*0.7),radius) ;
    this->setBrushColor(X,this->_map_button[X],paint);
    paint.drawEllipse(QPointF(this->width()*0.825,this->height()*0.7),radius,radius);



    //draw the direct control button
    double width = this->width()*0.12 ;
    double height = this->height()*0.1 ;

    //Button Left
    this->_map_button[LEFT] = QRectF(this->width()*0.02,this->height()*0.45,width,height) ;
    this->setBrushColor(LEFT,this->_map_button[LEFT],paint);
    paint.drawRect(this->width()*0.02,this->height()*0.45,width,height);

    //Button Right
    this->_map_button[RIGHT] = QRectF(this->width()*0.14+height,this->height()*0.45,width,height) ;
    this->setBrushColor(RIGHT,this->_map_button[RIGHT],paint);
    paint.drawRect(this->width()*(0.12+0.02)+height,this->height()*0.45,width,height);

    float start_height = this->height()*0.45 - width ;
    //to avoid start is smaller than zero
    start_height = start_height>0?start_height:0 ;

    //Button UP
    this->_map_button[UP] = QRectF(this->width()*(0.12+0.02),start_height,height,width) ;
    this->setBrushColor(UP,this->_map_button[UP],paint);
    paint.drawRect(this->width()*(0.12+0.02),start_height,height,width);

    //Button Down
    start_height = this->height()*0.55 ;
    this->_map_button[DOWN] = QRectF(this->width()*(0.12+0.02),start_height,height,width) ;
    this->setBrushColor(DOWN,this->_map_button[DOWN],paint);
    paint.drawRect(this->width()*(0.12+0.02),start_height,height,width);

    //draw button start
    this->_map_button[START] = QRectF(this->width()*0.37,this->height()*0.5,this->width()*0.1,this->height()*0.05) ;
    this->setBrushColor(START,this->_map_button[START],paint);
    paint_path_start_button.addRoundRect(this->width()*0.37,this->height()*0.5,this->width()*0.1,this->height()*0.05,150);
    paint.drawPath(paint_path_start_button);

    //draw button stop
    this->_map_button[STOP] = QRectF(this->width()*0.53,this->height()*0.5,this->width()*0.1,this->height()*0.05) ;
    this->setBrushColor(STOP,this->_map_button[STOP],paint);
    paint_path_stop_button.addRoundRect(this->width()*0.52,this->height()*0.5,this->width()*0.1,this->height()*0.05,150);
    paint.drawPath(paint_path_stop_button);

    //Draw mid rect in the center of control model
    paint.setPen(QPen(QBrush(QColor("#121212")),4));
    paint.setBrush(QBrush(QColor("#454545")));
    paint.drawRect(this->width()*(0.12+0.02),this->height()*0.45,height,height);
    paint.drawEllipse(this->width()*(0.12+0.02),this->height()*0.45,height,height);


    QFont control_font("verdana",(int)(radius),QFont::Bold,false) ;
    paint.setPen(QColor("#0D0D0D	"));
    paint.setFont(control_font);
    paint.drawText(this->_map_button[A],Qt::AlignCenter,"A");
    paint.drawText(this->_map_button[B],Qt::AlignCenter,"B");
    paint.drawText(this->_map_button[X],Qt::AlignCenter,"X");
    paint.drawText(this->_map_button[Y],Qt::AlignCenter,"Y");

    paint.drawImage(this->_map_button[UP],QImage(":/up.png"));
    paint.drawImage(this->_map_button[DOWN],QImage(":/down.png"));
    paint.drawImage(this->_map_button[LEFT],QImage(":/left.png"));
    paint.drawImage(this->_map_button[RIGHT],QImage(":/right.png"));

    QFont label_font("verdana",this->_map_button[START].height()*0.6,QFont::Bold,false) ;
    paint.setFont(label_font);
    paint.setPen(QColor("#0D0D0D"));
    qreal label_height = this->_map_button[LEFT].height()-this->_map_button[START].height();
    qreal label_width = this->_map_button[START].width() ;
    QRect label_start_rect(this->_map_button[START].x(),this->_map_button[RIGHT].y(),
                                        label_width,label_height) ;
    QRect label_stop_rect(this->_map_button[STOP].x(),this->_map_button[RIGHT].y(),
                                        label_width,label_height) ;
    paint.drawText(label_start_rect,Qt::AlignCenter,"START");
    paint.drawText(label_stop_rect,Qt::AlignCenter,"STOP ");

}

void Joystick::keyPressEvent(QKeyEvent *e)
{
    if(Qt::Key_W==e->key())emit buttonUpClicked(UP);
    else if(Qt::Key_S==e->key())emit buttonDownClicked(DOWN);
    else if(Qt::Key_A==e->key())emit buttonLeftClicked(LEFT);
    else if(Qt::Key_D==e->key())emit buttonRightClicked(RIGHT);
    else if(Qt::Key_I==e->key())emit buttonAClicked(A);
    else if(Qt::Key_J==e->key())emit buttonBClicked(B);
    else if(Qt::Key_K==e->key())emit buttonXClicked(X);
    else if(Qt::Key_L==e->key())emit buttonYClicked(Y);
    else if(Qt::Key_G==e->key())emit buttonStartClicked(START);
    else if(Qt::Key_H==e->key())emit buttonStopClicked(STOP);
    QWidget::keyPressEvent(e) ;
}

void Joystick::keyReleaseEvent(QKeyEvent *e)
{
    this->setAllButtonUnpressed();
    update();
    QWidget::keyReleaseEvent(e) ;
}

void Joystick::mousePressEvent(QMouseEvent *e)
{
    if(Qt::LeftButton!=e->button())return ;
    for(int i =0  ; i < BUTTON_NUM ; i++){
        QRectF current_rect = this->_map_button[(Button)i] ;
        if(current_rect.contains(e->pos()))emit hasButtonClicked(i);
    }
    QWidget::mousePressEvent(e) ;
}

void Joystick::mouseReleaseEvent(QMouseEvent *e)
{
    this->setAllButtonUnpressed();
    update();
    QWidget::mouseReleaseEvent(e) ;
}

void Joystick::setBrushColor(Button button, const QRectF &button_rect, QPainter &paint)
{
    QColor no_clicked("#4D4D4D") ;
    if(START==button||STOP==button)no_clicked = QColor("#030303") ;
    QLinearGradient has_clicked ;
    has_clicked.setColorAt(0,QColor("#FFFFFF"));
    has_clicked.setColorAt(1,QColor("#030303"));
    has_clicked.setStart(button_rect.topLeft());
    has_clicked.setFinalStop(button_rect.bottomRight());

    if(this->_is_button_pressed[button]){
        paint.setBrush(QBrush(has_clicked));
    }
    else{
        paint.setBrush(QBrush(no_clicked));
    }
}

QRectF Joystick::ellipse2Rect(const QPointF &center_point, double radius)
{
    double width = radius*2;
    double height = radius*2;
    return QRectF(center_point.x()-radius,center_point.y()-radius,width,height) ;
}

void Joystick::init_SigSlot()
{
    connect(this,SIGNAL(buttonAClicked(int)) ,this , SLOT(do_buttonAClicked(int))) ;
    connect(this,SIGNAL(buttonBClicked(int)) ,this , SLOT(do_buttonBClicked(int))) ;
    connect(this,SIGNAL(buttonXClicked(int)) ,this , SLOT(do_buttonXClicked(int))) ;
    connect(this,SIGNAL(buttonYClicked(int)) ,this , SLOT(do_buttonYClicked(int))) ;

    connect(this,SIGNAL(buttonUpClicked(int)) ,this , SLOT(do_buttonUpClicked(int))) ;
    connect(this,SIGNAL(buttonLeftClicked(int)) ,this , SLOT(do_buttonLeftClicked(int))) ;
    connect(this,SIGNAL(buttonRightClicked(int)) ,this , SLOT(do_buttonRightClicked(int))) ;
    connect(this,SIGNAL(buttonDownClicked(int)) ,this , SLOT(do_buttonDownClicked(int))) ;

    connect(this,SIGNAL(buttonStopClicked(int)) ,this , SLOT(do_buttonStopClicked(int))) ;
    connect(this,SIGNAL(buttonStartClicked(int)) ,this , SLOT(do_buttonStartClicked(int))) ;

    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonAClicked(int))) ;
    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonBClicked(int))) ;
    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonXClicked(int))) ;
    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonYClicked(int))) ;

    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonUpClicked(int))) ;
    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonLeftClicked(int))) ;
    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonRightClicked(int))) ;
    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonDownClicked(int))) ;

    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonStopClicked(int))) ;
    connect(this,SIGNAL(hasButtonClicked(int)) ,this , SLOT(do_buttonStartClicked(int))) ;
}

