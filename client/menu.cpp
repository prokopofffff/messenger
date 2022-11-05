#include "menu.h"

Menu::Menu(QMainWindow* parent): QToolBar(parent)
{
    buttonFile = new QMenu("File");
    buttonSettings = new QMenu("Settings");
    buttonHelp = new QMenu("Help");

    buttonConnect = new QAction("Connect");
    buttonDisconnect = new QAction("Disconnect");
    buttonSaveHistory = new QAction("Save history as XML-file");
    buttonExit = new QAction("Exit");
    buttonServer = new QAction("Server");
    buttonUserName = new QAction("Username");
    buttonStatus = new QMenu("Status");
    buttonAbout = new QAction("About");

    buttonAvailable = new QAction("Available");
    buttonAFK = new QAction("Away from keyboard");
    buttonDontDisturb = new QAction("Do not disturb");

    buttonFile->addAction(buttonConnect);
    buttonFile->addAction(buttonDisconnect);
    buttonFile->addAction(buttonSaveHistory);
    buttonFile->addAction(buttonExit);

    buttonSettings->addAction(buttonServer);
    buttonSettings->addAction(buttonUserName);
    buttonSettings->addMenu(buttonStatus);

    buttonHelp->addAction(buttonAbout);

    buttonStatus->addAction(buttonAvailable);
    buttonStatus->addAction(buttonAFK);
    buttonStatus->addAction(buttonDontDisturb);

    this->setMovable(false);
    this->addWidget(buttonFile);
    this->addWidget(buttonSettings);
    this->addWidget(buttonHelp);
    this->addSeparator();

    this->show();
}
