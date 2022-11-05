#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    settings = new QSettings("settings.ini", QSettings::IniFormat, this);
    uploadSettings();

    ui->setupUi(this);
    socket = new QTcpSocket(this);

    nextBlockSize = 0;

    ui->actionDisconnect->setDisabled(true);
    ui->actionConnect->setDisabled(false);
    ui->actionServer->setDisabled(false);
    ui->buttonSend->setDisabled(true);

    ui->actionAvailable->setDisabled(true);
    ui->actionAway_from_keyboard->setDisabled(false);
    ui->actionDo_not_disturb->setDisabled(false);

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::connected, this, &MainWindow::slotConnected);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::slotDisconnected);

    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::slotActionConnect);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::slotActionDisconnect);
    connect(ui->actionSave_as_XML_file, &QAction::triggered, this, &MainWindow::slotActionSave);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::slotActionExit);

    connect(ui->actionServer, &QAction::triggered, this, &MainWindow::slotActionServer);
    connect(ui->actionUsername, &QAction::triggered, this, &MainWindow::slotActionUsername);

    connect(ui->actionAvailable, &QAction::triggered, this, &MainWindow::slotActionAvailable);
    connect(ui->actionAway_from_keyboard, &QAction::triggered, this, &MainWindow::slotActionAwayFromKeyboard);
    connect(ui->actionDo_not_disturb, &QAction::triggered, this, &MainWindow::slotActionDoNotDisturb);

    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::slotActionAbout);
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}


void MainWindow::slotActionConnect(){
    socket->connectToHost(ip, port);
}

void MainWindow::slotActionDisconnect(){
    socket->disconnectFromHost();
}

void MainWindow::slotActionSave(){

}

void MainWindow::slotActionExit(){
    socket->disconnectFromHost();
    qApp->exit();
}

void MainWindow::slotActionServer(){
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);

    QPushButton *button = new QPushButton("Close");

    layout->addWidget(new QLabel("Server's IP " + ip));
    layout->addWidget(new QLabel("Server's PORT " + QString::number(port)));
    layout->addWidget(button);

    dialog->setLayout(layout);

    dialog->show();

    connect(button, &QPushButton::clicked, dialog, &QDialog::close);
}

void MainWindow::slotActionUsername(){
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);

    QPushButton *buttonSave = new QPushButton("Save");
    QPushButton *buttonClose = new QPushButton("Close");

    QLabel *label = new QLabel("Your Username: ");

    editUsername = new QLineEdit;

    editUsername->setText(username);

    label->setBuddy(editUsername);

    layout->addWidget(label);
    layout->addWidget(editUsername);
    layout->addWidget(buttonSave);
    layout->addWidget(buttonClose);

    dialog->setLayout(layout);

    dialog->show();

    //connect(editUsername, SIGNAL(textChanged(const QString&)), dialog, SLOT(setText(const QString&)));
    connect(buttonClose, &QPushButton::clicked, dialog, &MainWindow::close);
    connect(buttonSave, &QPushButton::clicked, this, &MainWindow::slotSaveUsername);
}

void MainWindow::slotSaveUsername(){
    QString str(username + " changed his username to " + editUsername->text());
    ui->textBrowser->setStyleSheet("color: rgb(0, 190, 0)");
    ui->textBrowser->append(str);
    username = editUsername->text();
    ui->textBrowser->setStyleSheet("color: rgb(0, 0, 0)");
}

void MainWindow::slotActionAvailable(){
    status = "Available";
    ui->actionAvailable->setDisabled(true);
    ui->actionAway_from_keyboard->setDisabled(false);
    ui->actionDo_not_disturb->setDisabled(false);
}

void MainWindow::slotActionAwayFromKeyboard(){
    status = "Away from keyboard";
    ui->actionAvailable->setDisabled(false);
    ui->actionAway_from_keyboard->setDisabled(true);
    ui->actionDo_not_disturb->setDisabled(false);
}

void MainWindow::slotActionDoNotDisturb(){
    status = "Do not disturb";
    ui->actionAvailable->setDisabled(false);
    ui->actionAway_from_keyboard->setDisabled(false);
    ui->actionDo_not_disturb->setDisabled(true);
}

void MainWindow::slotActionAbout(){
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    QImage img("author.jpg");
    QImage author = img.scaled(img.width() / 6, img.height() / 6);
    QString data = QDate::currentDate().toString("dd.MM.yyyy");
    QLabel *label = new QLabel;
    QPushButton *buttonClose = new QPushButton("Close");

    label->setPixmap(QPixmap::fromImage(author));
    label->setScaledContents(true);

    layout->addWidget(new QLabel("Author: Kukharenko Ivan"));
    layout->addWidget(label);
    layout->addWidget(new QLabel("Building date: " + data));
    layout->addWidget(new QLabel("Building version QT: 6.3.1"));
    layout->addWidget(new QLabel("Launching version QT: " + QString(QT_VERSION_STR)));

    dialog->setLayout(layout);
    dialog->show();

    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
}

void MainWindow::slotReadyRead(){
    QSoundEffect sound;
    sound.setSource(QUrl::fromLocalFile("vk2.0.mp3"));
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
            ui->textBrowser->append(username + ": " + str);
            if(status != "Do not disturb") sound.play();
            break;
        }
    } else ui->textBrowser->append("READ ERROR");
}

void MainWindow::sendToServer(QString str){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));
    socket->write(data);
    ui->lineEdit->clear();
}

void MainWindow::on_lineEdit_returnPressed()
{
    sendToServer(ui->lineEdit->text());
}


void MainWindow::on_buttonSend_clicked()
{
    sendToServer(ui->lineEdit->text());
}

void MainWindow::uploadSettings(){
    ip = settings->value("ip", "127.0.0.1").toString();
    port = settings->value("port", "45678").toInt();
    username = settings->value("username", "user").toString();
    status = settings->value("status", "Available").toString();
}

void MainWindow::saveSettings(){
    settings->setValue("ip", ip);
    settings->setValue("port", port);
    settings->setValue("username", username);
    settings->setValue("status", status);
}

void MainWindow::slotConnected(){
    ui->actionConnect->setDisabled(true);
    ui->actionDisconnect->setDisabled(false);
    ui->actionServer->setDisabled(true);
    ui->buttonSend->setDisabled(false);
}

void MainWindow::slotDisconnected(){
    ui->actionConnect->setDisabled(false);
    ui->actionDisconnect->setDisabled(true);
    ui->actionServer->setDisabled(false);
    ui->buttonSend->setDisabled(true);
}
