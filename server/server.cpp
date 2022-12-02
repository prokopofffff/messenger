#include "server.h"

Server::Server(){
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
    nextBlockSize = 0;
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
                QString str, name, ip;
                in >> name >> str >> ip;
                nextBlockSize = 0;
                sendToClient("newMsg", name, str, ip);
                break;
            }
            else if(com == "newUser"){
                QString ip, port, username, status, avatarFile;
                in >> ip >> port >> username >> status >> avatarFile;
                clients.push_back(new Client(ip, port.toInt(), username, status, avatarFile, curSocket));
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
                QString str, name, ip;
                in >> name >> str >> ip;
                nextBlockSize = 0;
                sendToClient("newImg", name, str, ip);
                break;
            }
            else if(com == "newFile"){
                qDebug() << "getting file";
                QString fileName, fileSize, name, ip;
                int curFileSize = 0;
                QString filePath = "C:\\Users\\vanba\\source\\qt\\vk 2.0\\server\\downloads\\";
                in >> name >> ip >> fileSize >> fileName;
                qDebug() << fileName;
                QFile file(filePath + fileName);
                if(file.open(QIODevice::WriteOnly)){
                    QDataStream sendFile(&file);
                    while(curFileSize < fileSize.toInt()){
                        QByteArray line = curSocket->readAll();
                        curFileSize += sendFile.writeRawData(line.data(), line.size());
                        curSocket->waitForReadyRead(100);
                        qDebug() << curFileSize << " vs " << fileSize << " |" << line.size();
                    }
                }
                else qDebug() << "can't get";

                file.close();

                //nextBlockSize = 0;
                sendToClient("newFile", name, file.fileName() , ip);
                break;
            }
        }
    }
    else qDebug() << "DATASTREAM ERROR";
}

void Server::sendToClient(QString com, QString name,  QString str, QString ip){
    data.clear();

    QDataStream out(&data, QIODevice::WriteOnly);

    if(com == "newMsg"){
        out << quint16(0) << com;
        out << name << str << QDate::currentDate().toString() << QTime::currentTime().toString() << ip;
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
    }
    else if(com == "newUser"){
        out << quint16(0) << com << QString::number(clients.size());

        for(int i = 0; i < clients.size(); i++){
            out << clients[i]->ip << QString::number(clients[i]->port) << clients[i]->username << clients[i]->status << clients[i]->avatarFile;
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
        out << name << str << QDate::currentDate().toString() << QTime::currentTime().toString() << ip;
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
    }
    else if(com == "restart"){
        out << quint16(0) << com;
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
        for(int i = 0; i < clients.size(); i++){
            emit clientDisconnected(clients[i]->socket);
        }
        clients.clear();
    }
    else if(com == "newFile"){
        out << quint16(0) << com;
        QFile file(str);
        QString fileName(str.split("/").last());
        QDataStream sendFile(&file);
        if (file.open(QIODevice::ReadOnly)) {
            qDebug() << "opened file";
            out << name << ip << QTime::currentTime().toString() << QString::number(file.size()) << fileName;
            out.device()->seek(0);
            out << quint16(data.size() - sizeof(quint16));
            for(int i = 0; i < sockets.size(); i++){
                sockets[i]->write(data);
                curSocket->waitForReadyRead(100);
                int curSendSize = 0;
                char bytes[8];
                bytes[7] = '\0';
                while (curSendSize < file.size()) {
                    int lenght = sendFile.readRawData(bytes, sizeof(char) * 7);
                    data.setRawData(bytes, sizeof(char) * lenght);
                    curSendSize += sockets[i]->write(data, sizeof(char) * lenght);
                    curSocket->waitForReadyRead(100);
                    qDebug() << curSendSize << " " << file.size() << " |" << lenght;
                }
            }
            file.close();
        }
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
        data.clear();
    }
    for(int i = 0; i < sockets.size(); i++){
        sockets[i]->write(data);
    }
}


int Server::getUsersCount(){
    return sockets.size();
}
