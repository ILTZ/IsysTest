#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "TrayIcon/ATrayIcon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QFrame;
class AKeyContainer;
class AKeyContainerFrame;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    ATrayIcon*  _trayIcon;

    bool        _minimizeToTray;

    QString     _defaultKeyDir;

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    void maximizeWnd();

protected:

    virtual void contextMenuEvent   (QContextMenuEvent* e) override;
    virtual void changeEvent        (QEvent* e) override;

public:

    void AddKeyContainerFrame    (AKeyContainerFrame* keyContainer);

    /*!
     * \brief RemoveKeyContainerFrame
     * \param AKeyContainerFrame* keyWidget
     *
     * Remove AKeyContainer widget from scroll area and delete it.
     */
    void RemoveKeyContainerFrame (AKeyContainerFrame* keyWidget);
};
#endif // MAINWINDOW_H
