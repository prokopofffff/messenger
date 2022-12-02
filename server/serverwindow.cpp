#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ip = "127.0.0.1";
    port = 45678;

    server = new Server();

    ui->setupUi(this);

    ui->label->setDisabled(true);
    ui->actionDisable->setDisabled(true);
    ui->actionEnable->setDisabled(false);

    connect(server, &Server::clientConnected, this, &ServerWindow::slotConnected);
    connect(server, &Server::clientDisconnected, this, &ServerWindow::slotDisconnected);

    connect(ui->actionNetwork, &QAction::triggered, this, &ServerWindow::slotActionNetwork);
    connect(ui->actionKey, &QAction::triggered, this, &ServerWindow::slotActionKey);
    connect(ui->actionEnable, &QAction::triggered, this, &ServerWindow::slotEnable);
    connect(ui->actionDisable, &QAction::triggered, this, &ServerWindow::slotDisable);
    connect(ui->actionSave_as_XML, &QAction::triggered, this, &ServerWindow::slotSave);
    connect(ui->actionExit, &QAction::triggered, this, &ServerWindow::slotExit);

}

ServerWindow::~ServerWindow(){
    delete ui;
}

void ServerWindow::updateInfo(){
    setWindowTitle(server->serverAddress().toString() + " " + QString::number(server->serverPort()) + "     Count of users: " + QString::number((server->getUsersCount())));
    ui->label->setText("IP: " + server->serverAddress().toString() + "            PORT: " + QString::number(server->serverPort()) + "          Count of users: " + QString::number(server->getUsersCount()));
}

void ServerWindow::slotConnected(){
    ui->textBrowser->append(QTime::currentTime().toString() + " user connected ");
    xmlData.push_back(QTime::currentTime().toString() + " user connected ");
    updateInfo();
}

void ServerWindow::slotDisconnected(){
    ui->textBrowser->append(QTime::currentTime().toString() + " user disconnected ");
    xmlData.push_back(QTime::currentTime().toString() + " user disconnected ");
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
    ip = editIp->text();
    port = editPort->text().toInt();

    server->close();
    server->listen(QHostAddress(ip), port);
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
    connect(buttonGenerate, &QPushButton::clicked, this, &ServerWindow::slotGenerateKey);
}

void ServerWindow::slotGenerateKey(){
    server->sendToClient("restart");
    ui->textBrowser->append("Server is reloading...");
    xmlData.push_back("Server is reloading...");
    server->close();
    server->listen(QHostAddress(ip), port);
}

void ServerWindow::slotEnable(){
    server->listen(QHostAddress(ip), port);
    ui->actionDisable->setDisabled(false);
    ui->actionEnable->setDisabled(true);
    ui->label->setDisabled(false);
    updateInfo();
}

void ServerWindow::slotDisable(){
    server->close();
    ui->actionEnable->setDisabled(false);
    ui->actionDisable->setDisabled(true);
    ui->label->setDisabled(true);
}

void ServerWindow::slotExit(){
    delete server;
    this->close();
}

void ServerWindow::slotSave(){
    QString path = QFileDialog::getSaveFileName(0, QObject::tr("Укажите путь для сохранения"), QDir::homePath() + "/" + editFile->text().trimmed() + ".xml", QObject::tr("XML files (*.xml)"));

    if(path != ""){
        gen_xml = doc_xml.createElement("history");
        for (int i = 0; i < xmlData.size(); i++){

            txt_xml = doc_xml.createElement("text");
            doc_xml.appendChild(gen_xml);

            QDomText text = doc_xml.createTextNode(xmlData[i]);

            gen_xml.appendChild(txt_xml);
            txt_xml.appendChild(text);
         }

        file_xml.setFileName(path);
        file_xml.open(QIODevice::WriteOnly);
        QTextStream out(&file_xml);
        doc_xml.save(out, 4);
        file_xml.close();
    }
}
