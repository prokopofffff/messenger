#ifndef SERVER_H
#define SERVER_H

#include <QSslSocket>
#include <QTcpServer>
#include <QVector>
#include <QNetworkInterface>
#include <QDate>
#include <QTime>
#include <QFile>

class Client{
public:
    QString ip;
    int port;
    QString username;
    QString status;
    QString avatarFile;
    QSslSocket* socket;

    Client();
    Client(QString ip, int port, QString username, QString status, QString avatarFile, QSslSocket* socket){
        this->ip = ip;
        this->port = port;
        this->username = username;
        this->status = status;
        this->avatarFile = avatarFile;
        this->socket = socket;
    }
};

extern int SERVER_PORT;

class Server: public QTcpServer {
    Q_OBJECT

public:
    Server();
    QSslSocket* curSocket;
    QVector<Client*> clients;

    int getUsersCount();

     void sendToClient(QString com, QString name = "", QString str = "", QString ip = "");

private:
    QVector<QSslSocket*> sockets;
    QByteArray data;
    quint16 nextBlockSize; 

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void slotDisconnected();
signals:
    void clientConnected(QSslSocket* soc);
    void clientDisconnected(QSslSocket* soc);
};

#endif // SERVER_H
