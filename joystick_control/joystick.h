#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QWidget>
#include <QRect>
#include <QHash>
#include <QDebug>
typedef enum Button{
    UP = 0 ,
    LEFT = 1 ,
    RIGHT = 2,
    DOWN = 3 ,
    A = 4 ,
    B = 5 ,
    X = 6 ,
    Y = 7 ,
    START = 8 ,
    STOP = 9,
    BUTTON_NUM = 10
}Button ;


class Joystick : public QWidget
{
    Q_OBJECT

public:
    explicit Joystick(QWidget *parent = 0);
    ~Joystick();
signals:
    void hasButtonClicked(int id) ;

    void buttonUpClicked(int id) ;
    void buttonDownClicked(int id) ;
    void buttonLeftClicked(int id) ;
    void buttonRightClicked(int id) ;

    void buttonStopClicked(int id) ;
    void buttonStartClicked(int id) ;

    void buttonAClicked(int id) ;
    void buttonBClicked(int id) ;
    void buttonXClicked(int id) ;
    void buttonYClicked(int id) ;
public slots:
    void do_buttonUpClicked(int id){
        if(id==UP)this->_is_button_pressed[id] = true ;
        update();
    }
    void do_buttonDownClicked(int id){
        if(id==DOWN)this->_is_button_pressed[id] = true ;
        update();
    }
    void do_buttonLeftClicked(int id){
        if(id==LEFT)this->_is_button_pressed[id] = true ;
        update();
    }
    void do_buttonRightClicked(int id){
        if(id==RIGHT)this->_is_button_pressed[id] = true ;
        update();
    }

    void do_buttonStopClicked(int id){
        if(id==STOP)this->_is_button_pressed[id] = true ;
        update();
    }
    void do_buttonStartClicked(int id){
        if(id==START)this->_is_button_pressed[id] = true ;
        update();
    }

    void do_buttonAClicked(int id){
        if(id==A)this->_is_button_pressed[id] = true ;
        update();
    }
    void do_buttonBClicked(int id){
        if(id==B)this->_is_button_pressed[id] = true ;
        update();
    }
    void do_buttonXClicked(int id){
        if(id==X)this->_is_button_pressed[id] = true ;
        update();
    }
    void do_buttonYClicked(int id){
        if(id==Y)this->_is_button_pressed[id] = true ;
        update();
    }
private:
    void init_SigSlot() ;
    void paintEvent(QPaintEvent *e) ;
    void keyPressEvent(QKeyEvent *e) ;
    void keyReleaseEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e)  ;
    void mouseReleaseEvent(QMouseEvent *e);

    void setBrushColor(Button button,const QRectF &button_rect,QPainter &paint) ;
    inline QRectF ellipse2Rect(const QPointF &center_point , double radius) ;
    inline void setAllButtonUnpressed(){
        for(int i = 0 ; i < BUTTON_NUM ; i++){
            this->_is_button_pressed[i] = false ;
        }
    }
private:

    bool _is_button_pressed[BUTTON_NUM] ;
    QHash<Button,QRectF> _map_button ;

};

#endif // JOYSTICK_H
