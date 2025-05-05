#ifndef UPLOADKEYFROMDIRECTORYCOMMAND_H
#define UPLOADKEYFROMDIRECTORYCOMMAND_H

#include "Command/ACommand.h"

class MainWindow;

class UploadKeyFromDirectoryCommand : public ACommand
{

    Q_OBJECT

    MainWindow* _mainWindow;

    QString _dirPath;

    QString _keyDir;

public:

    UploadKeyFromDirectoryCommand(MainWindow* wnd, const QString& targetDir, const QString& keyDir, QObject* parent = nullptr);

    virtual void execute() override;

};

#endif // UPLOADKEYFROMDIRECTORYCOMMAND_H
