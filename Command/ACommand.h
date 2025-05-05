#ifndef ACOMMAND_H
#define ACOMMAND_H

#include <QObject>

class ACommand : public QObject
{
    Q_OBJECT

public:

    ACommand(QObject* parent = nullptr)
        : QObject { parent }
    {

    }

    Q_DISABLE_COPY(ACommand);

    virtual ~ACommand() = default;

public slots:

    virtual void execute() = 0;

};


#endif // ACOMMAND_H
