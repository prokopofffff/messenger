/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionSave_as_XML_file;
    QAction *actionExit;
    QAction *actionServer;
    QAction *actionUsername;
    QAction *actionAbout;
    QAction *actionAvailable;
    QAction *actionAway_from_keyboard;
    QAction *actionDo_not_disturb;
    QAction *actionOther;
    QAction *actionPhoto;
    QAction *actionChange_theme;
    QAction *actionChange_font;
    QAction *actionShow_message_time;
    QAction *actionDo_not_show_message_time;
    QAction *actionShow_sender_s_IP;
    QAction *actionChange_theme_2;
    QAction *actionChange_font_2;
    QAction *actionShow_message_time_2;
    QAction *actionShow_sender_s_IP_2;
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QPushButton *buttonSend;
    QListWidget *listWidget;
    QListWidget *textBrowser;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuStatus;
    QMenu *menuTheme_2;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(858, 535);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        actionSave_as_XML_file = new QAction(MainWindow);
        actionSave_as_XML_file->setObjectName(QString::fromUtf8("actionSave_as_XML_file"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionServer = new QAction(MainWindow);
        actionServer->setObjectName(QString::fromUtf8("actionServer"));
        actionServer->setCheckable(false);
        actionUsername = new QAction(MainWindow);
        actionUsername->setObjectName(QString::fromUtf8("actionUsername"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAvailable = new QAction(MainWindow);
        actionAvailable->setObjectName(QString::fromUtf8("actionAvailable"));
        actionAway_from_keyboard = new QAction(MainWindow);
        actionAway_from_keyboard->setObjectName(QString::fromUtf8("actionAway_from_keyboard"));
        actionDo_not_disturb = new QAction(MainWindow);
        actionDo_not_disturb->setObjectName(QString::fromUtf8("actionDo_not_disturb"));
        actionOther = new QAction(MainWindow);
        actionOther->setObjectName(QString::fromUtf8("actionOther"));
        actionPhoto = new QAction(MainWindow);
        actionPhoto->setObjectName(QString::fromUtf8("actionPhoto"));
        actionChange_theme = new QAction(MainWindow);
        actionChange_theme->setObjectName(QString::fromUtf8("actionChange_theme"));
        actionChange_font = new QAction(MainWindow);
        actionChange_font->setObjectName(QString::fromUtf8("actionChange_font"));
        actionShow_message_time = new QAction(MainWindow);
        actionShow_message_time->setObjectName(QString::fromUtf8("actionShow_message_time"));
        actionDo_not_show_message_time = new QAction(MainWindow);
        actionDo_not_show_message_time->setObjectName(QString::fromUtf8("actionDo_not_show_message_time"));
        actionShow_sender_s_IP = new QAction(MainWindow);
        actionShow_sender_s_IP->setObjectName(QString::fromUtf8("actionShow_sender_s_IP"));
        actionChange_theme_2 = new QAction(MainWindow);
        actionChange_theme_2->setObjectName(QString::fromUtf8("actionChange_theme_2"));
        actionChange_font_2 = new QAction(MainWindow);
        actionChange_font_2->setObjectName(QString::fromUtf8("actionChange_font_2"));
        actionShow_message_time_2 = new QAction(MainWindow);
        actionShow_message_time_2->setObjectName(QString::fromUtf8("actionShow_message_time_2"));
        actionShow_message_time_2->setCheckable(false);
        actionShow_message_time_2->setChecked(false);
        actionShow_sender_s_IP_2 = new QAction(MainWindow);
        actionShow_sender_s_IP_2->setObjectName(QString::fromUtf8("actionShow_sender_s_IP_2"));
        actionShow_sender_s_IP_2->setCheckable(false);
        actionShow_sender_s_IP_2->setChecked(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 440, 721, 28));
        buttonSend = new QPushButton(centralwidget);
        buttonSend->setObjectName(QString::fromUtf8("buttonSend"));
        buttonSend->setGeometry(QRect(730, 440, 121, 29));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(660, 10, 191, 421));
        textBrowser = new QListWidget(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 641, 421));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 858, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuStatus = new QMenu(menuSettings);
        menuStatus->setObjectName(QString::fromUtf8("menuStatus"));
        menuTheme_2 = new QMenu(menuSettings);
        menuTheme_2->setObjectName(QString::fromUtf8("menuTheme_2"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionConnect);
        menuFile->addAction(actionDisconnect);
        menuFile->addAction(actionSave_as_XML_file);
        menuFile->addAction(actionExit);
        menuSettings->addAction(actionServer);
        menuSettings->addAction(actionUsername);
        menuSettings->addAction(menuStatus->menuAction());
        menuSettings->addAction(actionPhoto);
        menuSettings->addAction(menuTheme_2->menuAction());
        menuStatus->addAction(actionAvailable);
        menuStatus->addAction(actionAway_from_keyboard);
        menuStatus->addAction(actionDo_not_disturb);
        menuStatus->addAction(actionOther);
        menuTheme_2->addAction(actionChange_theme_2);
        menuTheme_2->addAction(actionChange_font_2);
        menuTheme_2->addAction(actionShow_message_time_2);
        menuTheme_2->addAction(actionShow_sender_s_IP_2);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        actionSave_as_XML_file->setText(QCoreApplication::translate("MainWindow", "Save as XML-file", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionServer->setText(QCoreApplication::translate("MainWindow", "Server", nullptr));
        actionUsername->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionAvailable->setText(QCoreApplication::translate("MainWindow", "Available", nullptr));
        actionAway_from_keyboard->setText(QCoreApplication::translate("MainWindow", "Away from keyboard", nullptr));
        actionDo_not_disturb->setText(QCoreApplication::translate("MainWindow", "Do not disturb", nullptr));
        actionOther->setText(QCoreApplication::translate("MainWindow", "Other", nullptr));
        actionPhoto->setText(QCoreApplication::translate("MainWindow", "Photo", nullptr));
        actionChange_theme->setText(QCoreApplication::translate("MainWindow", "Change theme", nullptr));
        actionChange_font->setText(QCoreApplication::translate("MainWindow", "Change font", nullptr));
        actionShow_message_time->setText(QCoreApplication::translate("MainWindow", "Show message time", nullptr));
        actionDo_not_show_message_time->setText(QCoreApplication::translate("MainWindow", "Do not show message time", nullptr));
        actionShow_sender_s_IP->setText(QCoreApplication::translate("MainWindow", "Show sender's IP", nullptr));
        actionChange_theme_2->setText(QCoreApplication::translate("MainWindow", "Change theme", nullptr));
        actionChange_font_2->setText(QCoreApplication::translate("MainWindow", "Change font", nullptr));
        actionShow_message_time_2->setText(QCoreApplication::translate("MainWindow", "Show message time", nullptr));
        actionShow_sender_s_IP_2->setText(QCoreApplication::translate("MainWindow", "Show sender's IP", nullptr));
        buttonSend->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuStatus->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        menuTheme_2->setTitle(QCoreApplication::translate("MainWindow", "Theme", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
