#ifndef REMOVEKEYCOMAND_H
#define REMOVEKEYCOMAND_H

#include "Command/ACommand.h"

class MainWindow;
class AKeyContainerFrame;

class RemoveKeyComand : public ACommand
{

    Q_OBJECT

    MainWindow* _mainWindow;

    AKeyContainerFrame* _keyFrame;

public:

    RemoveKeyComand(MainWindow* wnd, AKeyContainerFrame* frame, QObject* parent = nullptr);

    virtual void execute() override;
};

#endif // REMOVEKEYCOMAND_H
