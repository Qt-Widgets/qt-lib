#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QObject>
#include <QWidget>

#include <QWidget>
#include <QTimer>

class SwitchButton : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchButton(QWidget *parent = 0);

    bool isToggled() const;

    void setToggle(bool checked);


    void setBackgroundColor(QColor color);

    void setCheckedColor(QColor color);

    void setDisbaledColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
    void toggled(bool checked);

private slots:
    void onTimeout();

private:
    bool m_bChecked;       //is_checked
    QColor m_background;
    QColor m_checkedColor;
    QColor m_disabledColor;
    QColor m_thumbColor;
    qreal m_radius;
    qreal m_nX;
    qreal m_nY;
    qint16 m_nHeight;
    qint16 m_nMargin;
    QTimer m_timer;         //the timer for moving the "button"
};

#endif // SWITCHBUTTON_H
