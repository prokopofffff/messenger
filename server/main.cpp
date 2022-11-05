#include <QCoreApplication>
#include "server.h"

int SERVER_PORT = 45678;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;

    return a.exec();
}
