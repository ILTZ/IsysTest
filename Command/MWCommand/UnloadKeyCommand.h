#ifndef UNLOADKEYCOMMAND_H
#define UNLOADKEYCOMMAND_H

#include "Command/ACommand.h"
#include "Key/KeySerializer/AKeyContainerSerializer.h"

class MainWindow;
class AKeyContainerFrame;

class UnloadKeyCommand : public ACommand
{

    Q_OBJECT

    MainWindow* _mainWindow;

    AKeyContainerFrame* _keyFrame;

    AKeyContainerSerializer::SerializeFormat _format;

public:

    UnloadKeyCommand(MainWindow* wnd, AKeyContainerFrame* frame, AKeyContainerSerializer::SerializeFormat format, QObject* parent = nullptr);

    virtual void execute() override;

};

#endif // UNLOADKEYCOMMAND_H
