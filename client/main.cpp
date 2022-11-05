#include "mainwindow.h"

#include <QApplication>

QString CLIENT_IP = "127.0.0.1";
int CLIENT_PORT = 45678;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
