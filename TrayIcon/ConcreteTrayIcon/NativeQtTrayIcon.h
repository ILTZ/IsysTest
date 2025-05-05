#ifndef NATIVEQTTRAYICON_H
#define NATIVEQTTRAYICON_H

#include "TrayIcon/ATrayIcon.h"

#include <QSystemTrayIcon>
#include <QHash>
#include <QMenu>

struct TrayIconData
{
    QSystemTrayIcon* icon;
    QMenu*           menu;

    TrayIconData()
        : icon { new QSystemTrayIcon { } }
        , menu { new QMenu { } }
    {

    }

    ~TrayIconData()
    {
        if (icon)
        {
            icon->deleteLater();
            menu->deleteLater();
        }
    }
};

class NativeQtTrayIcon : public ATrayIcon
{
    Q_OBJECT

    QScopedPointer<TrayIconData> _trayIcon;

    QHash<QSystemTrayIcon::ActivationReason, std::function<void(ATrayIcon&)>>   _iconCallback;
    QHash<QAction*, std::function<void(const QAction&)>>                        _actionCallback;

public:

    NativeQtTrayIcon(QObject* parent = nullptr);

    virtual void setIcon(const QIcon& icon)                                                                                 override;
    virtual void showMessage(const QString& title, const QString& msg, QSystemTrayIcon::MessageIcon icon, quint32 duration) override;

    virtual void addMenuAction(const QString &title, const std::function<void(const QAction&)> &handler)                   override;
    virtual void addIconHandler(QSystemTrayIcon::ActivationReason reason, const std::function<void(ATrayIcon&)> &handler)  override;

private slots:

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void actionTriggered();
};

#endif // NATIVEQTTRAYICON_H
