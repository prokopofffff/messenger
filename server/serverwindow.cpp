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

    connect(ui->actionNetwork, &QAction::triggered, this, &ServerWindow::slotActionNetwork);
    connect(ui->actionKey, &QAction::triggered, this, &ServerWindow::slotActionKey);

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

void ServerWindow::slotActionNetwork(){
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);

    QPushButton *buttonClose = new QPushButton("Close");
    QPushButton *buttonSave = new QPushButton("Save");
    editIp = new QLineEdit;
    editPort = new QLineEdit;
    QLabel *labelIp = new QLabel("Server's IP:");
    QLabel *labelPort = new QLabel("Server's PORT:");

    editIp->setText(server->serverAddress().toString());
    labelIp->setBuddy(editIp);
    layout->addWidget(labelIp);
    layout->addWidget(editIp);

    editPort->setText(QString::number(server->serverPort()));
    labelPort->setBuddy(editPort);
    layout->addWidget(labelPort);
    layout->addWidget(editPort);

    layout->addWidget(buttonSave);
    layout->addWidget(buttonClose);

    dialog->setLayout(layout);

    dialog->show();

    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
    connect(buttonSave, &QPushButton::clicked, this, &ServerWindow::slotServerChange);
}

void ServerWindow::slotServerChange(){
    QRegularExpression regex("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    if(regex.match(editIp->text()).hasMatch());
    else{
        QDialog *dialog = new QDialog(this);
        dialog->setModal(true);

        QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
        QPushButton *buttonClose = new QPushButton("Close");

        layout->addWidget(new QLabel("Wrong IP! Please, try again"));
        layout->addWidget(buttonClose);

        dialog->setLayout(layout);
        dialog->show();

        editIp->setText(server->serverAddress().toString());

        connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
    }
    if(editPort->text().toInt() < 65535 && editPort->text().toInt() > 0);
    else{
        QDialog *dialog = new QDialog(this);
        dialog->setModal(true);

        QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
        QPushButton *buttonClose = new QPushButton("Close");

        layout->addWidget(new QLabel("Wrong PORT! Please, try again"));
        layout->addWidget(buttonClose);

        dialog->setLayout(layout);
        dialog->show();

        editPort->setText(QString::number(server->serverPort()));

        connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
    }
    server->close();
    server->listen(QHostAddress(editIp->text()), editPort->text().toInt());
    updateInfo();
}

void ServerWindow::slotActionKey(){
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    QPushButton *buttonClose = new QPushButton("No");
    QPushButton *buttonGenerate = new QPushButton("Yes");

    layout->addWidget(new QLabel("Generate new key?"));
    layout->addWidget(buttonGenerate);
    layout->addWidget(buttonClose);

    dialog->setLayout(layout);
    dialog->show();

    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
}
