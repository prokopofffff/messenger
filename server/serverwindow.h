#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRegularExpression>
#include <QHostAddress>

#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ServerWindow: public QMainWindow
{
    Q_OBJECT
public:
    ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    Ui::MainWindow *ui;

    Server* server;

    QLineEdit* editIp;
    QLineEdit* editPort;

    void updateInfo();

private slots:
    void slotConnected();
    void slotDisconnected();
    void slotActionNetwork();
    void slotActionKey();
    void slotServerChange();
    void slotGenerateKey();

signals:
    void signalRestart();
};

#endif // SERVERWINDOW_H
