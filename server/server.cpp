#include "server.h"

Server::Server(){
    if(this->listen(QHostAddress::Any, SERVER_PORT)) qDebug() << "STARTING...";
    else qDebug() << "ERROR";

    nextBlockSize = 0;
}

void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    sockets.push_back(socket);

    qDebug() << getIP();
    qDebug() << "Amount of users: " << sockets.size();//доделать количество пользователей!!!!!!!!!!!!!!!!!!!!!!!
}

void Server::slotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);

    if(in.status() == QDataStream::Ok){
        while(true){
            if(nextBlockSize == 0){
                if(socket->bytesAvailable() < 2) break;

                in >> nextBlockSize;
            }
            if(nextBlockSize > socket->bytesAvailable()) break;

            QString str;
            in >> str;
            nextBlockSize = 0;
            sendToClient(str);
            break;
        }
    }
    else qDebug() << "DATASTREAM ERROR";
}

void Server::sendToClient(QString str){
    data.clear();

    QDataStream out(&data, QIODevice::WriteOnly);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));

    for(int i = 0; i < sockets.size(); i++){
        sockets[i]->write(data);
    }
}

QString Server::getIP(){
    QString localIP;
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             localIP.push_back(address.toString());
        break;
    }

    return localIP;
}
