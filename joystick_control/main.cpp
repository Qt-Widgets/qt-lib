#include "joystick.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Joystick w;
    w.show();

    return a.exec();
}
