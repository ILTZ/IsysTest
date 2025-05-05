#ifndef UPLOADKEYFROMFILECOMMAND_H
#define UPLOADKEYFROMFILECOMMAND_H

#include "Command/ACommand.h"
#include "Key/KeySerializer/AKeyContainerSerializer.h"

class MainWindow;

class UploadKeyFromFileCommand : public ACommand
{
    Q_OBJECT

    MainWindow* _mainWindow;

    QString _baseKeyDir;

    AKeyContainerSerializer::SerializeFormat _format;

public:

    UploadKeyFromFileCommand(MainWindow* wnd, const QString& baseKeyDir, AKeyContainerSerializer::SerializeFormat format, QObject* parent = nullptr);

public slots:

    virtual void execute() override;
};

#endif // UPLOADKEYFROMFILECOMMAND_H
