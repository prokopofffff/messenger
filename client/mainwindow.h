#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSslSocket>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QDialog>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QImage>
#include <QDate>
#include <QPixmap>
#include <QSoundEffect>
#include <QSettings>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotActionConnect();
    void slotActionDisconnect();
    void slotActionSave();
    void slotActionExit();

    void slotActionServer();
    void slotActionUsername();
    void slotSaveUsername();

    void slotActionAvailable();
    void slotActionAwayFromKeyboard();
    void slotActionDoNotDisturb();

    void slotActionAbout();

    void on_lineEdit_returnPressed();

    void on_buttonSend_clicked();

    void slotConnected();
    void slotDisconnected();

    void slotServerChange();

private:
    Ui::MainWindow *ui;
    QSslSocket* socket;
    QByteArray data;
    quint16 nextBlockSize;

    QString ip;
    int port;
    QString username;
    QString status;

    QLineEdit* editUsername;
    QLineEdit* editIp;
    QLineEdit* editPort;

    QSettings* settings;

    void sendToServer(QString com, QString str);
    //void sendToServer(QString str);

    void uploadSettings();
    void saveSettings();
public slots:
    void slotReadyRead();
};
#endif // MAINWINDOW_H
