#ifndef CREATEKEYCOMMAND_H
#define CREATEKEYCOMMAND_H

#include "Command/ACommand.h"
#include "Key/KeyGenerator/AKeyGenerator.h"
#include "Key/KeySerializer/AKeyContainerSerializer.h"

class MainWindow;

class AKeyContainer;

class CreateKeyCommand : public ACommand
{
    Q_OBJECT

    MainWindow* _mainWindow;

    QString _keyDir;

    AKeyGenerator::KeyGeneratorAlgorithm _algorithm;

    AKeyContainerSerializer::SerializeFormat _format;

public:

    CreateKeyCommand(MainWindow* mw, AKeyGenerator::KeyGeneratorAlgorithm algorithm, AKeyContainerSerializer::SerializeFormat format, const QString& keyDir, QObject* parent = nullptr);

private:

    AKeyContainer* generateKey(AKeyGenerator::KeyGeneratorAlgorithm algorithm);

public slots:

    virtual void execute() override;
};

#endif // CREATEKEYCOMMAND_H
