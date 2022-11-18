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
                QString str, name;
                in >> name >> str;
                nextBlockSize = 0;
                sendToClient("newMsg", name, str);
                break;
            }
            else if(com == "newUser"){
                QString ip, port, username, status;
                in >> ip >> port >> username >> status;
                clients.push_back(new Client(ip, port.toInt(), username, status, curSocket));
                nextBlockSize = 0;
                sendToClient("newUser");
                break;
            }
            else if(com == "exitUser"){
                QString username;
                in >> username;
                for(int i = 0; i < clients.size(); i++){
                     if(username == clients[i]->username){
                        clients.removeAt(i);
                        break;
                     }
                }
                nextBlockSize = 0;
                sendToClient("exitUser");
                break;
            }
            else if(com == "newImg"){
                QString str, name;
                in >> name >> str;
                nextBlockSize = 0;
                sendToClient("newImg", name, str);
                break;
            }
        }
    }
    else qDebug() << "DATASTREAM ERROR";
}

void Server::sendToClient(QString com, QString name,  QString str){
    data.clear();

    QDataStream out(&data, QIODevice::WriteOnly);

    if(com == "newMsg"){
        out << quint16(0) << com;
        out << name << str << QDate::currentDate().toString() << QTime::currentTime().toString();
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
    }
    else if(com == "newUser"){
        out << quint16(0) << com << QString::number(clients.size());

        for(int i = 0; i < clients.size(); i++){
            out << clients[i]->ip << QString::number(clients[i]->port) << clients[i]->username << clients[i]->status;
        }
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
    }
    else if(com == "exitUser"){
        out << quint16(0) << com << QString::number(clients.size());

        for(int i = 0; i < clients.size(); i++){
            out << clients[i]->ip << QString::number(clients[i]->port) << clients[i]->username << clients[i]->status;
        }
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
    }
    else if(com == "newImg"){
        out << quint16(0) << com;
        out << name << str << QDate::currentDate().toString() << QTime::currentTime().toString();
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
    }
    for(int i = 0; i < sockets.size(); i++){
        sockets[i]->write(data);
    }
}

int Server::getUsersCount(){
    return sockets.size();
}
