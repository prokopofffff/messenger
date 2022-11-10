#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    server = new Server();

    ui->setupUi(this);

    updateInfo();

    connect(server, &Server::clientConnected, this, &ServerWindow::slotConnected);
    connect(server, &Server::clientDisconnected, this, &ServerWindow::slotDisconnected);

}

ServerWindow::~ServerWindow(){
    delete ui;
}

void ServerWindow::updateInfo(){
    setWindowTitle(server->serverAddress().toString() + " " + QString::number(server->serverPort()) + "     Count of users: " + QString::number((server->getUsersCount())));
    ui->label->setText("IP: " + server->serverAddress().toString() + "            PORT: " + QString::number(server->serverPort()) + "          Count of users: " + QString::number(server->getUsersCount()));
}

void ServerWindow::slotConnected(){
    ui->textBrowser->append(QTime::currentTime().toString() + " user connected ");// + curSocket->peerAddress().toString());
    updateInfo();
}

void ServerWindow::slotDisconnected(){
    ui->textBrowser->append(QTime::currentTime().toString() + " user disconnected ");// + curSocket->peerAddress().toString());
    updateInfo();
}
