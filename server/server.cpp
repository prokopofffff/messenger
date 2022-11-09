#include "server.h"

Server::Server(){
   if(this->listen(QHostAddress::LocalHost, SERVER_PORT)) qDebug() << "STARTING...";
   else qDebug() << "ERROR";

   nextBlockSize = 0;
}

void Server::incomingConnection(qintptr socketDescriptor){
   curSocket = new QSslSocket;
   curSocket->setSocketDescriptor(socketDescriptor);

   connect(curSocket, &QSslSocket::readyRead, this, &Server::slotReadyRead);
   connect(curSocket, &QSslSocket::disconnected, this, &Server::slotDisconnected);

   sockets.push_back(curSocket);

   qDebug() << curSocket->peerAddress().toString();
   qDebug() << "Amount of users: " << sockets.size();

   emit clientConnected(curSocket);
}

void Server::slotDisconnected(){
   curSocket = (QSslSocket*)sender();
   for(int i = 0; i < sockets.size(); i++){
       if(curSocket->socketDescriptor() == sockets[i]->socketDescriptor()){

           sockets.removeAt(i);
           clients.removeAt(i);

           emit clientDisconnected(curSocket);
           break;
       }
   }
}

void Server::slotReadyRead(){
    curSocket = (QSslSocket*)sender();
    QDataStream in(curSocket);

    if(in.status() == QDataStream::Ok){
        while(true){
            if(nextBlockSize == 0){
                if(curSocket->bytesAvailable() < 2) break;

                in >> nextBlockSize;
            }
            if(nextBlockSize > curSocket->bytesAvailable()) break;

            QString com;
            in >> com;
            qDebug() << com;
            if(com == "newMsg"){
                QString str;
                in >> str;
                nextBlockSize = 0;
                sendToClient("newMsg", str);
                break;
            }
            else if(com == "User"){
                QString ip, port, username, status;
                in >> ip >> port >> username >> status;
                clients.push_back(new Client(ip, port.toInt(), username, status, curSocket));
                nextBlockSize = 0;
                sendToClient("User", "");
                break;
            }
        }
    }
    else qDebug() << "DATASTREAM ERROR";
}

void Server::sendToClient(QString com, QString str){
    data.clear();

    QDataStream out(&data, QIODevice::WriteOnly);

    if(com == "newMsg"){
        out << quint16(0) << com;
        out << str;
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
    }
    else if(com == "User"){
        out << quint16(0) << com << QString::number(clients.size());

        for(int i = 0; i < clients.size(); i++){
            out << clients[i]->ip << QString::number(clients[i]->port) << clients[i]->username << clients[i]->status;
        }
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
    }
    for(int i = 0; i < sockets.size(); i++){
        sockets[i]->write(data);
    }
}

/*void Server::slotReadyRead(){
    curSocket = (QSslSocket*)sender();
    QDataStream in(curSocket);

    if(in.status() == QDataStream::Ok){
        while(true){
            if(nextBlockSize == 0){
                if(curSocket->bytesAvailable() < 2) break;

                in >> nextBlockSize;
            }
            if(nextBlockSize > curSocket->bytesAvailable()) break;

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
}*/

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

int Server::getUsersCount(){
    return sockets.size();
}
