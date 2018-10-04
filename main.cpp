#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w(&a);
    w.showMaximized();

    return QApplication::exec();
}
