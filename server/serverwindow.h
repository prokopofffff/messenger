#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QTime>

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

    void updateInfo();

private slots:
    void slotConnected(QSslSocket *curSocket);
    void slotDisconnected(QSslSocket *curSocket);
};

#endif // SERVERWINDOW_H
