#ifndef ATRAYICON_H
#define ATRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>

class QAction;

class ATrayIcon : public QObject
{
    Q_OBJECT

public:

    ATrayIcon(QObject* parent = nullptr)
        : QObject { parent }
    {

    }

    virtual ~ATrayIcon() = default;

    virtual void setIcon(const QIcon& icon)                                                                                 = 0;
    virtual void showMessage(const QString& title, const QString& msg, QSystemTrayIcon::MessageIcon icon, quint32 duration) = 0;

    virtual void addMenuAction  (const QString& title, const std::function<void(const QAction&)>& handler)                  = 0;
    virtual void addIconHandler (QSystemTrayIcon::ActivationReason reason, const std::function<void( ATrayIcon&)>& handler) = 0;
};


#endif // ATRAYICON_H
