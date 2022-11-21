#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    settings = new QSettings("settings.ini", QSettings::IniFormat, this);
    uploadSettings();

    ui->setupUi(this);
    socket = new QSslSocket(this);

    nextBlockSize = 0;
    ip = "127.0.0.1";
    port = 45678;
    avatarFile = "C:\\Users\\vanba\\source\\qt\\vk 2.0\\client\\avatar.png";

    ui->textBrowser->setIconSize(QSize(320, 240));
    ui->listWidget->setIconSize(QSize(60, 40));

    ui->actionDisconnect->setDisabled(true);
    ui->actionConnect->setDisabled(false);
    ui->actionServer->setDisabled(false);
    ui->buttonSend->setDisabled(true);

    ui->actionAvailable->setDisabled(true);
    ui->actionAway_from_keyboard->setDisabled(false);
    ui->actionDo_not_disturb->setDisabled(false);
    ui->actionOther->setDisabled(false);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotWidgetMenu(QPoint)));

    connect(socket, &QSslSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QSslSocket::connected, this, &MainWindow::slotConnected);
    connect(socket, &QSslSocket::disconnected, this, &MainWindow::slotDisconnected);

    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::slotActionConnect);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::slotActionDisconnect);
    connect(ui->actionSave_as_XML_file, &QAction::triggered, this, &MainWindow::slotActionSave);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::slotActionExit);

    connect(ui->actionServer, &QAction::triggered, this, &MainWindow::slotActionServer);
    connect(ui->actionUsername, &QAction::triggered, this, &MainWindow::slotActionUsername);

    connect(ui->actionAvailable, &QAction::triggered, this, &MainWindow::slotActionAvailable);
    connect(ui->actionAway_from_keyboard, &QAction::triggered, this, &MainWindow::slotActionAwayFromKeyboard);
    connect(ui->actionDo_not_disturb, &QAction::triggered, this, &MainWindow::slotActionDoNotDisturb);
    connect(ui->actionOther, &QAction::triggered, this, &MainWindow::slotActionOtherStatus);

    connect(ui->actionPhoto, &QAction::triggered, this, &MainWindow::slotActionPhoto);

    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::slotActionAbout);

    ui->buttonSend->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->buttonSend, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(menuOnSendButton(QPoint)));

    ui->textBrowser->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->textBrowser, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(menuOnMessageField(QPoint)));
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}


void MainWindow::slotActionConnect(){
    socket->connectToHost(ip, port);
    sendToServer("newUser");
    setWindowTitle(ip + " " + QString::number(port) + "    " + status);
}

void MainWindow::slotActionDisconnect(){
    sendToServer("exitUser");
    socket->disconnectFromHost();
    ui->listWidget->clear();
    ui->textBrowser->clear();
    setWindowTitle("");
}

void MainWindow::slotActionSave(){
    QDialog* dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom);

    QPushButton* buttonClose = new QPushButton("Close");
    QPushButton* buttonSave = new QPushButton("Save");
    editFile = new QLineEdit;
    editPassword = new QLineEdit;
    buttonCheck = new QCheckBox("Hide password");

    layout->addWidget(new QLabel("Enter a name of file"));
    layout->addWidget(editFile);
    layout->addWidget(new QLabel("Enter a password"));
    layout->addWidget(editPassword);
    layout->addWidget(buttonCheck);
    layout->addWidget(buttonSave);
    layout->addWidget(buttonClose);

    dialog->setLayout(layout);
    dialog->show();

    connect(buttonCheck, &QCheckBox::clicked, this, &MainWindow::slotChangeEcho);
    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
    connect(buttonSave, &QPushButton::clicked, this, &MainWindow::slotSaveXML);
}

void MainWindow::slotChangeEcho(){
    if(buttonCheck->isChecked()) editPassword->setEchoMode(QLineEdit::Password);
    else editPassword->setEchoMode(QLineEdit::Normal);
}

void MainWindow::slotSaveXML(){
    QString path = QFileDialog::getSaveFileName(0, QObject::tr("Укажите путь для сохранения"), QDir::homePath() + "/" + editFile->text().trimmed() + ".xml", QObject::tr("XML files (*.xml)"));

    if(path != ""){
        gen_xml = doc_xml.createElement("history");
        for (int i = 0; i < xmlData.size(); i += 5){

            date_xml = doc_xml.createElement("date");
            time_xml = doc_xml.createElement("time");
            ip_xml = doc_xml.createElement("ip");
            name_xml = doc_xml.createElement("username");
            msg_xml = doc_xml.createElement("message");
            doc_xml.appendChild(gen_xml);

            QDomText date_t = doc_xml.createTextNode(xmlData[i]);
            QDomText time_t = doc_xml.createTextNode(xmlData[i + 1]);
            QDomText ip_t = doc_xml.createTextNode(xmlData[i + 2]);
            QDomText name_t = doc_xml.createTextNode(xmlData[i + 3]);
            QDomText msg_t = doc_xml.createTextNode(xmlData[i + 4]);

            gen_xml.appendChild(date_xml);
            date_xml.appendChild(date_t);
            gen_xml.appendChild(time_xml);
            time_xml.appendChild(time_t);
            gen_xml.appendChild(ip_xml);
            ip_xml.appendChild(ip_t);
            gen_xml.appendChild(name_xml);
            name_xml.appendChild(name_t);
            gen_xml.appendChild(msg_xml);
            msg_xml.appendChild(msg_t);
         }

        file_xml.setFileName(path);
        file_xml.open(QIODevice::WriteOnly);
        QTextStream out(&file_xml);
        doc_xml.save(out, 4);
        file_xml.close();
    }
}

void MainWindow::slotActionExit(){
    sendToServer("exitUser");
    socket->disconnectFromHost();
    ui->listWidget->clear();
    ui->textBrowser->clear();
    qApp->exit();
}

void MainWindow::slotActionServer(){
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);

    QPushButton *buttonClose = new QPushButton("Close");
    QPushButton *buttonSave = new QPushButton("Save");
    editIp = new QLineEdit;
    editPort = new QLineEdit;
    QLabel *labelIp = new QLabel("Server's IP:");
    QLabel *labelPort = new QLabel("Server's PORT:");

    editIp->setText(ip);
    labelIp->setBuddy(editIp);
    layout->addWidget(labelIp);
    layout->addWidget(editIp);

    editPort->setText(QString::number(port));
    labelPort->setBuddy(editPort);
    layout->addWidget(labelPort);
    layout->addWidget(editPort);

    layout->addWidget(buttonSave);
    layout->addWidget(buttonClose);

    dialog->setLayout(layout);

    dialog->show();

    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
    connect(buttonSave, &QPushButton::clicked, this, &MainWindow::slotServerChange);
}

void MainWindow::slotServerChange(){
    QRegularExpression regex("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    if(regex.match(editIp->text()).hasMatch()) {
        ip = editIp->text();
        setWindowTitle(ip + " " + QString::number(port) + "    " + status);
    }
    else{
        QDialog *dialog = new QDialog(this);
        dialog->setModal(true);

        QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
        QPushButton *buttonClose = new QPushButton("Close");

        layout->addWidget(new QLabel("Wrong IP! Please, try again"));
        layout->addWidget(buttonClose);

        dialog->setLayout(layout);
        dialog->show();

        editIp->setText(ip);

        connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
    }
    if(editPort->text().toInt() < 65535 && editPort->text().toInt() > 0){
        port = editPort->text().toInt();
        setWindowTitle(ip + " " + QString::number(port) + "    " + status);
    }
    else{
        QDialog *dialog = new QDialog(this);
        dialog->setModal(true);

        QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
        QPushButton *buttonClose = new QPushButton("Close");

        layout->addWidget(new QLabel("Wrong PORT! Please, try again"));
        layout->addWidget(buttonClose);

        dialog->setLayout(layout);
        dialog->show();

        editPort->setText(QString::number(port));

        connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
    }
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

    connect(buttonClose, &QPushButton::clicked, dialog, &MainWindow::close);
    connect(buttonSave, &QPushButton::clicked, this, &MainWindow::slotSaveUsername);
}

void MainWindow::slotSaveUsername(){
    for(int i = 0; i < clients.size(); i++){
        if(editUsername->text() == clients[i]->username){
            QDialog* dialog = new QDialog(this);
            dialog->setModal(true);

            QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom);
            QPushButton* buttonClose = new QPushButton("Close");

            layout->addWidget(new QLabel("This username is already in use!"));
            layout->addWidget(buttonClose);

            dialog->setLayout(layout);

            connect(buttonClose, &QPushButton::clicked, dialog, &MainWindow::close);

            dialog->show();

            return;
        }
    }
    sendToServer("exitUser");
    QString str(username + " changed his username to " + editUsername->text());
    sendToServer("newMsg", str);
    username = editUsername->text();
    sendToServer("newUser");
}

void MainWindow::slotActionAvailable(){
    status = "Available";
    ui->actionAvailable->setDisabled(true);
    ui->actionAway_from_keyboard->setDisabled(false);
    ui->actionDo_not_disturb->setDisabled(false);
    setWindowTitle(ip + " " + QString::number(port) + "    " + status);
}

void MainWindow::slotActionAwayFromKeyboard(){
    status = "Away from keyboard";
    ui->actionAvailable->setDisabled(false);
    ui->actionAway_from_keyboard->setDisabled(true);
    ui->actionDo_not_disturb->setDisabled(false);
    setWindowTitle(ip + " " + QString::number(port) + "    " + status);
}

void MainWindow::slotActionDoNotDisturb(){
    status = "Do not disturb";
    ui->actionAvailable->setDisabled(false);
    ui->actionAway_from_keyboard->setDisabled(false);
    ui->actionDo_not_disturb->setDisabled(true);
    setWindowTitle(ip + " " + QString::number(port) + "    " + status);
}

void MainWindow::slotActionOtherStatus(){
    QDialog* dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    editStatus = new QLineEdit;
    QLabel* label = new QLabel("Your status:");
    editStatus->setText(status);

    label->setBuddy(editStatus);
    QPushButton *buttonClose = new QPushButton("Close");
    QPushButton *buttonSave = new QPushButton("Save");

    layout->addWidget(label);
    layout->addWidget(editStatus);
    layout->addWidget(buttonSave);
    layout->addWidget(buttonClose);

    dialog->setLayout(layout);
    dialog->show();

    connect(buttonSave, &QPushButton::clicked, this, &MainWindow::slotOtherStatusSave);
    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
}

void MainWindow::slotOtherStatusSave(){
    status = editStatus->text();
    ui->actionAvailable->setDisabled(false);
    ui->actionAway_from_keyboard->setDisabled(false);
    ui->actionDo_not_disturb->setDisabled(false);
    setWindowTitle(ip + " " + QString::number(port) + "    " + status);
}

void MainWindow::slotActionPhoto(){
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    QPushButton *buttonSelect = new QPushButton("Select");
    QPushButton *buttonClose = new QPushButton("Close");

    layout->addWidget(new QLabel("Select new avatar"));
    layout->addWidget(buttonSelect);
    layout->addWidget(buttonClose);

    dialog->setLayout(layout);
    dialog->show();

    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
    connect(buttonSelect, &QPushButton::clicked, this, &MainWindow::slotSelectPhoto);

}

void MainWindow::slotSelectPhoto(){
    sendToServer("exitUser");
    QString path = QFileDialog::getOpenFileName(0, QObject::tr("Select image"),
                   "C:\\Users\\vanba\\source\\qt\\vk 2.0\\client", QObject::tr("Image files (*.png)"));
    if(path != "") avatarFile = path;
    sendToServer("newUser");
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
    QDataStream in(socket);
    if(in.status() == QDataStream::Ok){
        while(true){
            if(nextBlockSize == 0){
                if(socket->bytesAvailable() < 2) break;

                in >> nextBlockSize;
            }
            if(nextBlockSize > socket->bytesAvailable()) break;

            QString com;
            in >> com;
            if(com == "newMsg"){
                QString msg, name, date, time;
                in >> name >> msg >> date >> time;
                nextBlockSize = 0;
                ui->textBrowser->addItem(new QListWidgetItem(name + ": " + msg));
                if(status != "Do not disturb" && name != username){
                    QMediaPlayer* player = new QMediaPlayer;
                    QAudioOutput* audio = new QAudioOutput;
                    audio->setVolume(0.2);
                    player->setAudioOutput(audio);
                    player->setSource(QUrl::fromLocalFile("vk2.0.mp3"));
                    player->play();
                }
                xmlData.push_back(date);
                xmlData.push_back(time);
                xmlData.push_back(ip);
                xmlData.push_back(name);
                xmlData.push_back(msg);
                break;
            }
            else if(com == "newUser"){
                QString count;
                QString ip, port, username, status, avatarFile;
                in >> count;
                ui->listWidget->clear();
                clients.clear();
                for(int i = 0; i < count.toInt(); i++){
                    in >> ip >> port >> username >> status >> avatarFile;
                    clients.push_back(new Client(ip, port.toInt(), username, status));
                    QListWidgetItem *item = new QListWidgetItem(QIcon(avatarFile), username, ui->listWidget);
                    ui->listWidget->addItem(item);
                }

                nextBlockSize = 0;
                break;
            }
            else if(com == "exitUser"){
                QString count;
                QString ip, port, username, status;
                in >> count;
                ui->listWidget->clear();
                clients.clear();
                for(int i = 0; i < count.toInt(); i++){
                    in >> ip >> port >> username >> status;
                    clients.push_back(new Client(ip, port.toInt(), username, status));
                    ui->listWidget->addItem(username);
                }
                nextBlockSize = 0;
                break;
            }
            else if(com == "newImg"){
                QString name, msg, date, time;
                in >> name >> msg >> date >> time;
                nextBlockSize = 0;
                QPixmap image;
                image.load(msg);
                QListWidgetItem *item = new QListWidgetItem(name + ": sent a photo", ui->textBrowser);
                ui->textBrowser->addItem(item);
                item = new QListWidgetItem(QIcon(image), "", ui->textBrowser);
                ui->textBrowser->addItem(item);
                if(status != "Do not disturb" && name != username){
                    QMediaPlayer* player = new QMediaPlayer;
                    QAudioOutput* audio = new QAudioOutput;
                    audio->setVolume(0.2);
                    player->setAudioOutput(audio);
                    player->setSource(QUrl::fromLocalFile("vk2.0.mp3"));
                    player->play();
                }
                QImage img(QIcon(image).pixmap(320, 240).toImage());
                QByteArray byteArray;
                QBuffer buffer(&byteArray);
                img.save(&buffer, "PNG");
                QString base64 = QString::fromLatin1(byteArray.toBase64().data());
                xmlData.push_back(date);
                xmlData.push_back(time);
                xmlData.push_back(ip);
                xmlData.push_back(name);
                xmlData.push_back(base64);
                break;
            }
            else if(com == "restart"){
                nextBlockSize = 0;
                ui->textBrowser->addItem(new QListWidgetItem("Server is reloading..."));
                socket->disconnectFromHost();
                ui->actionDisconnect->setDisabled(true);
                ui->actionConnect->setDisabled(false);
                ui->actionServer->setDisabled(false);
                ui->buttonSend->setDisabled(true);
                ui->listWidget->clear();
                ui->textBrowser->addItem(new QListWidgetItem("Please, reconnect manually"));
                break;
            }
        }
    } else ui->textBrowser->addItem(new QListWidgetItem("READ ERROR"));
}

void MainWindow::sendToServer(QString com, QString str){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);

    out << quint16(0) << com;
    if(com == "newMsg")
        out << username << str;
    else if(com == "newUser")
        out << ip << QString::number(port) << username << status << avatarFile;
    else if(com == "exitUser"){
        out << username;
    }
    else if(com == "newImg"){
        out << username << str;
    }
    //else if(com == "updateInfo"){
    //    out << username << avatarFile << status;
    //}
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));
    socket->write(data);
    ui->lineEdit->clear();
}

void MainWindow::on_lineEdit_returnPressed()
{
    if(ui->lineEdit->text() != "")
    sendToServer("newMsg", ui->lineEdit->text());
}


void MainWindow::on_buttonSend_clicked()
{
    if(ui->lineEdit->text() != "")
    sendToServer("newMsg", ui->lineEdit->text());
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

void MainWindow::slotWidgetMenu(QPoint pos){
    QMenu *menu = new QMenu(this);
    QAction *infoAct = new QAction("Info");
    connect(infoAct, &QAction::triggered, this, &MainWindow::slotWidgetInfo);
    menu->addAction(infoAct);
    menu->popup(ui->listWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::slotWidgetInfo(){
    for (int i = 0; i < clients.size(); i++){
        if (ui->listWidget->currentItem()->text() == clients[i]->username) {
            QDialog *dialog = new QDialog(this);
            dialog->setModal(true);

            QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
            QPushButton *buttonClose = new QPushButton("Close");
            QImage img = QImage(QIcon(avatarFile).pixmap(320, 240).toImage());
            QLabel *label = new QLabel;

            label->setPixmap(QPixmap::fromImage(img));
            label->setScaledContents(true);

            layout->addWidget(label);
            layout->addWidget(new QLabel(username));
            layout->addWidget(new QLabel(status));
            layout->addWidget(new QLabel(ip));
            layout->addWidget(new QLabel(QString::number(port)));

            dialog->setLayout(layout);
            dialog->show();

            connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
            break;
        }
    }
}

void MainWindow::menuOnSendButton(QPoint pos)
{
    QMenu *menu = new QMenu;
    QAction *sendImg = new QAction("Send Image");

    menu->addAction(sendImg);
    menu->popup(ui->buttonSend->mapFromGlobal(pos));

    connect(sendImg, &QAction::triggered, this, &MainWindow::slotSendImage);
}

void MainWindow::slotSendImage(){
    QString path = QFileDialog::getOpenFileName(0, QObject::tr("Select image"),
                   "C:\\Users\\vanba\\source\\qt\\vk 2.0\\client", QObject::tr("Image files (*.png)"));
    if (path != "") sendToServer("newImg", path);
}

void MainWindow::menuOnMessageField(QPoint pos)
{
    if (ui->textBrowser->count()) {
        QMenu *menu = new QMenu(this);
        QAction *actionClear = new QAction("Clear");
        QAction *actionShow = new QAction("Full-sized image");

        menu->addAction(actionClear);
        menu->addAction(actionShow);
        menu->popup(ui->textBrowser->viewport()->mapToGlobal(pos));

        connect(actionClear, &QAction::triggered, this, &MainWindow::slotClearStory);
        connect(actionShow, &QAction::triggered, this, &MainWindow::slotOpenImage);
    }
}

void MainWindow::slotClearStory(){
    ui->textBrowser->clear();
}

void MainWindow::slotOpenImage(){
    if (ui->textBrowser->currentItem()->text() == "") {
        QDialog* dialog = new QDialog(this);
        QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
        QPushButton* buttonSave = new QPushButton("Save");
        QPushButton* buttonClose = new QPushButton("Close");

        QLabel *label = new QLabel;

        curImage = ui->textBrowser->currentItem()->icon().pixmap(ui->textBrowser->currentItem()->icon().actualSize(QSize(1920, 1080)));
        label->setPixmap(curImage);
        label->setScaledContents(true);

        layout->addWidget(label);
        layout->addWidget(buttonSave);
        layout->addWidget(buttonClose);

        dialog->setLayout(layout);
        dialog->show();

        connect(buttonSave, &QPushButton::clicked, this, &MainWindow::slotSaveImage);
        connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
    }
}

void MainWindow::slotSaveImage(){
    QString path = QFileDialog::getSaveFileName(0, QObject::tr("Select saving path"), "C:\\Users\\vanba\\source\\qt\\vk 2.0\\client", QObject::tr("Image files (*.png)"));
    if (path != ""){
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::WriteOnly);
        curImage.save(&file, "PNG");
        file.close();
    }
}

