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
#include <QtWidgets/QTextBrowser>
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
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QPushButton *buttonSend;
    QTextBrowser *textBrowser;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuStatus;
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
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 440, 721, 28));
        buttonSend = new QPushButton(centralwidget);
        buttonSend->setObjectName(QString::fromUtf8("buttonSend"));
        buttonSend->setGeometry(QRect(730, 440, 121, 29));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 641, 421));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(660, 10, 191, 421));
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
        menuStatus->addAction(actionAvailable);
        menuStatus->addAction(actionAway_from_keyboard);
        menuStatus->addAction(actionDo_not_disturb);
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
        buttonSend->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuStatus->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
