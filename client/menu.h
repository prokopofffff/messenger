#ifndef MENU_H
#define MENU_H

#include <QToolBar>
#include <QAction>
#include <QMainWindow>
#include <QMenu>

class Menu: public QToolBar
{
    Q_OBJECT

public:
    Menu(QMainWindow* parent = nullptr);

private:
    QMenu* buttonFile;
    QMenu* buttonSettings;
    QMenu* buttonHelp;

    QAction* buttonConnect;
    QAction* buttonDisconnect;
    QAction* buttonSaveHistory;
    QAction* buttonExit;
    QAction* buttonServer;
    QAction* buttonUserName;
    QMenu* buttonStatus;
    QAction* buttonAbout;

    QAction* buttonAvailable;
    QAction* buttonAFK;
    QAction* buttonDontDisturb;
};

#endif // MENU_H
