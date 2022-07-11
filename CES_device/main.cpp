#include "ces_device.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CES_Device w;
    w.show();
    return a.exec();
}
