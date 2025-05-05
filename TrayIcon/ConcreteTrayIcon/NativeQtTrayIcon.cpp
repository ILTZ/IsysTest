#include "NativeQtTrayIcon.h"

#include <QApplication>
#include <QMenu>

NativeQtTrayIcon::NativeQtTrayIcon(QObject *parent)
    : ATrayIcon     { parent }
    , _trayIcon     { new TrayIconData{ } }
{
    connect(_trayIcon->icon, &QSystemTrayIcon::activated, this, &NativeQtTrayIcon::iconActivated);

    _trayIcon->icon->setContextMenu(_trayIcon->menu);    
}

void NativeQtTrayIcon::setIcon(const QIcon &icon)
{    
    _trayIcon->icon->setIcon(icon);

    if (_trayIcon->icon->isVisible() == false)
        _trayIcon->icon->show();
}

void NativeQtTrayIcon::showMessage(const QString &title, const QString &msg, QSystemTrayIcon::MessageIcon icon, quint32 duration)
{
    _trayIcon->icon->showMessage(title, msg, icon, duration);
}

void NativeQtTrayIcon::addMenuAction(const QString &title, const std::function<void(const QAction&)> &handler)
{
    auto action = _trayIcon->menu->addAction(title);

    _actionCallback.insert(action, handler);

    connect(action, &QAction::triggered, this, &NativeQtTrayIcon::actionTriggered);
}

void NativeQtTrayIcon::addIconHandler(QSystemTrayIcon::ActivationReason reason, const std::function<void(ATrayIcon &)> &handler)
{
    _iconCallback[reason] = handler;
}

void NativeQtTrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (auto it = _iconCallback.find(reason); it != _iconCallback.end())
        it.value()(*this);
}

void NativeQtTrayIcon::actionTriggered()
{
    auto action = qobject_cast<QAction*>(sender());
    _actionCallback[action](*action);
}
