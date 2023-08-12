#include "four.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    four w;
    w.show();
    return a.exec();
}
