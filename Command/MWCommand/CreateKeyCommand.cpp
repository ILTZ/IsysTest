#include "CreateKeyCommand.h"

#include <QMessageBox>
#include <QInputDialog>

#include <QFile>
#include <QDir>

#include "MainWindow/mainwindow.h"

#include "Key/KeyGenerator/ConcreteKeyContainerGenerator/BaseKeyContainerGenerator.h"
#include "Key/KeyGenerator/ConcreteKeyGenerator/BaseKeyGenerator.h"

#include "Key/KeySerializer/ConcreteKeyContainerSerializer/BaseKeyContainerSerializer.h"

#include "Key/KeyFrame/ConcreteKeyContainerFrame/ConcreteContainerFrame.h"

CreateKeyCommand::CreateKeyCommand(MainWindow* mw, AKeyGenerator::KeyGeneratorAlgorithm algorithm, AKeyContainerSerializer::SerializeFormat format, const QString& keyDir, QObject* parent)
    : ACommand      { parent }
    , _mainWindow   { mw }
    , _keyDir       { keyDir }
    , _algorithm    { algorithm }
    , _format       { format }
{

}

AKeyContainer *CreateKeyCommand::generateKey(AKeyGenerator::KeyGeneratorAlgorithm algorithm)
{
    AKeyContainer* temp { nullptr };

    BaseKeyGenerator gen;
    gen.setAlgorithm(algorithm);

    QScopedPointer<BaseKeyContainerGenerator> containerGen { new BaseKeyContainerGenerator { } };

    temp = containerGen->generateContainer(&gen);

    return temp;
}

void CreateKeyCommand::execute()
{
    if (auto keyName = QInputDialog::getText(_mainWindow, "Название ключа", "Введите название нового ключа"); keyName.isEmpty() == false)
    {
        if (QSharedPointer<AKeyContainer> container { generateKey(_algorithm) }; container)
        {
            QString fileName { _keyDir + '/' + keyName + ".key" };

            BaseKeyContainerSerializer ser(_format);

            if (ser.serialize(container.get(), fileName))
            {
                container->setFileName(fileName);
                
                auto keyFrame = new BaseContainerFrame{ };
                keyFrame->setKeyContainer(container);
                keyFrame->setKeyReadyState(true);
                
                _mainWindow->AddKeyContainerFrame(keyFrame);
            }
            else
            {
                QMessageBox::warning(_mainWindow, "Ошибка записи ключа", "Не удалось записать новый ключ в память!:" + ser.errorString());
            }
        }
        else
        {
            QMessageBox::warning(_mainWindow, "Ошибка генерации ключа", "Не удалось сгенерировать новый ключ!");
        }
    }
}
