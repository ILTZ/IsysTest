#include "UnloadKeyCommand.h"

#include "MainWindow/mainwindow.h"

#include "Key/KeyFrame/AKeyFrameContainer.h"
#include "Key/KeySerializer/ConcreteKeyContainerSerializer/BaseKeyContainerSerializer.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

UnloadKeyCommand::UnloadKeyCommand(MainWindow* wnd, AKeyContainerFrame* frame, AKeyContainerSerializer::SerializeFormat format, QObject *parent)
    : ACommand      { parent }
    , _mainWindow   { wnd }
    , _keyFrame     { frame }
    , _format       { format }
{

}

void UnloadKeyCommand::execute()
{
    if (auto path = QFileDialog::getExistingDirectory(_mainWindow, "Выгруз ключа", QDir::currentPath()); path.isEmpty() == false)
    {
        auto container = _keyFrame->getKeyContainer();

        QFileInfo fInfo(container->getFileName());
        path += '/' + fInfo.fileName();

        auto originPath = container->getFileName();

        if (path == originPath)
            return;

        BaseKeyContainerSerializer ser(_format);

        if (ser.serialize(container.get(), path))
        {            
            if (QFile rFile(originPath); rFile.exists())
            {
                if (rFile.remove() == false)
                {
                    QFile nFile(path);
                    nFile.remove();

                    QMessageBox::warning(_mainWindow, "Ошибка выгруза ключа", "Не удалось выгрузить ключ, расположенный в " + originPath + ':' + rFile.errorString());
                }
                else
                {
                    _mainWindow->RemoveKeyContainerFrame(_keyFrame);
                }
            }
        }
        else
        {
            QMessageBox::warning(_mainWindow, "Ошибка записи", "Не удалось сохранить ключ в файл " + path + ":" + ser.errorString());
        }
    }
}
