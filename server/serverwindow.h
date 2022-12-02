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
#include <QFile>
#include <QDomDocument>
#include <QFileDialog>

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

    QString ip;
    int port;

    QFile file_xml;
    QDomDocument doc_xml;
    QDomElement gen_xml;
    QDomElement txt_xml;
    QVector<QString> xmlData;
    QLineEdit* editFile;

    void updateInfo();

private slots:
    void slotConnected();
    void slotDisconnected();
    void slotActionNetwork();
    void slotActionKey();
    void slotServerChange();
    void slotGenerateKey();
    void slotEnable();
    void slotDisable();
    void slotExit();
    void slotSave();

signals:
    void signalRestart();
};

#endif // SERVERWINDOW_H
