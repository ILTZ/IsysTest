#include "MainWindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName        ("KeyManager");
    QApplication::setApplicationDisplayName ("KeyManager");
    QApplication::setOrganizationName       ("Information Systems");
    QApplication::setApplicationVersion     ("1.0.0");

    MainWindow w;
    w.show();
    w.activateWindow();

    return a.exec();
}
