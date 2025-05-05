#include "UploadKeyFromFileCommand.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>

#include "MainWindow\mainwindow.h"

#include "Key/KeySerializer/ConcreteKeyContainerSerializer/BaseKeyContainerSerializer.h"
#include "Key/KeyFrame/ConcreteKeyContainerFrame/ConcreteContainerFrame.h"

UploadKeyFromFileCommand::UploadKeyFromFileCommand(MainWindow* wnd, const QString &baseKeyDir, AKeyContainerSerializer::SerializeFormat format, QObject* parent)
    : ACommand      { parent }
    , _mainWindow   { wnd }
    , _baseKeyDir   { baseKeyDir }
    , _format       { format }
{

}

void UploadKeyFromFileCommand::execute()
{
    auto extensions = AKeyContainerSerializer::getFileExtensions(_format);

    QString exEs;

    for (const auto& el : extensions)
        exEs += '*' + el + ' ';

    if (auto filePath = QFileDialog::getOpenFileName(_mainWindow, "Загрузка ключа", QDir::currentPath(), exEs.trimmed()); filePath.isEmpty() == false)
    {
        BaseKeyContainerSerializer ser(_format);

        if (QSharedPointer<AKeyContainer> container { ser.deserialize(filePath) }; container)
        {
            QFileInfo fInfo(filePath);
            QString savePath = _baseKeyDir + '/' + fInfo.fileName();

            if (QFile cFile(filePath); cFile.copy(savePath))
            {
                container->setFileName(savePath);
                
                auto keyFrame = new BaseContainerFrame { };
                keyFrame->setKeyContainer(container);
                keyFrame->setKeyReadyState(true);

                _mainWindow->AddKeyContainerFrame(keyFrame);
            }
            else
            {
                QDir dir(_baseKeyDir);

                QMessageBox::warning(_mainWindow, "Ошибка копирования файла", "Не скопировать файл " + filePath +
                " в директорию ключей " + dir.absolutePath() + ":" + cFile.errorString());
            }
        }
        else
        {
            QMessageBox::warning(_mainWindow, "Ошибка чтения файла", "Не удалось прочитать файл:" + ser.errorString());
        }
    }
}
