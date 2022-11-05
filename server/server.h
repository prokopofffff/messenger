#ifndef SERVER_H
#define SERVER_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QVector>
#include <QNetworkInterface>

extern int SERVER_PORT;

class Server: public QTcpServer {
    Q_OBJECT

public:
    Server();
    QTcpSocket* socket;

private:
    QVector<QTcpSocket*> sockets;
    QByteArray data;
    quint16 nextBlockSize;

    void sendToClient(QString str);
    QString getIP();

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H
