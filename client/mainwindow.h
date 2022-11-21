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
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSettings>
#include <QRegularExpression>
#include <QDomDocument>
#include <QFile>
#include <QCheckBox>
#include <QFileDialog>
#include <QWidgetItem>
#include <QIcon>
#include <QBuffer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Client{
public:
    QString ip;
    int port;
    QString username;
    QString status;
    QString avatarFile;
    QSslSocket* socket;

    Client();
    Client(QString ip, int port, QString username, QString status){
        this->ip = ip;
        this->port = port;
        this->username = username;
        this->status = status;
    }
};

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
    void slotChangeEcho();
    void slotSaveXML();
    void slotActionExit();

    void slotActionServer();
    void slotActionUsername();
    void slotSaveUsername();

    void slotActionAvailable();
    void slotActionAwayFromKeyboard();
    void slotActionDoNotDisturb();
    void slotActionOtherStatus();
    void slotOtherStatusSave();

    void slotActionPhoto();
    void slotSelectPhoto();

    void slotActionAbout();

    void on_lineEdit_returnPressed();

    void on_buttonSend_clicked();

    void slotConnected();
    void slotDisconnected();

    void slotServerChange();

    void slotWidgetMenu(QPoint pos);
    void slotWidgetInfo();

    void menuOnSendButton(QPoint pos);
    void menuOnMessageField(QPoint pos);
    void slotClearStory();
    void slotOpenImage();
    void slotSaveImage();
    void slotSendImage();

private:
    Ui::MainWindow *ui;
    QSslSocket* socket;
    QByteArray data;
    quint16 nextBlockSize;

    QString ip;
    int port;
    QString username;
    QString avatarFile;
    QString status;

    QLineEdit* editUsername;
    QLineEdit* editIp;
    QLineEdit* editPort;
    QLineEdit* editStatus;

    QSettings* settings;

    QVector<Client*> clients;

    QFile file_xml;
    QDomDocument doc_xml;
    QDomElement gen_xml;
    QDomElement date_xml;
    QDomElement time_xml;
    QDomElement ip_xml;
    QDomElement name_xml;
    QDomElement msg_xml;
    QVector<QString> xmlData;
    QLineEdit* editFile;
    QLineEdit* editPassword;
    QCheckBox* buttonCheck;

    QPixmap curImage;

    void sendToServer(QString com, QString str = "");

    void uploadSettings();
    void saveSettings();
public slots:
    void slotReadyRead();
};
#endif // MAINWINDOW_H
