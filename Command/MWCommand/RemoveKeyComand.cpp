#include "RemoveKeyComand.h"

#include "MainWindow/mainwindow.h"
#include "Key/KeyFrame/AKeyFrameContainer.h"

#include <QFile>
#include <QMessageBox>

RemoveKeyComand::RemoveKeyComand(MainWindow *wnd, AKeyContainerFrame *frame, QObject *parent)
    : ACommand      { parent }
    , _mainWindow   { wnd }
    , _keyFrame     { frame }
{

}

void RemoveKeyComand::execute()
{
    auto container = _keyFrame->getKeyContainer();
    
    if (QFile rFile(container->getFileName()); rFile.exists())
    {
        if (rFile.remove() == false)
        {
            QMessageBox::warning(_mainWindow, "Ошибка удаления ключа", "Не удалось удалить ключ, расположенный в " + rFile.fileName() + ":" + rFile.errorString());
        }
        else
        {
            _mainWindow->RemoveKeyContainerFrame(_keyFrame);
        }
    }
    else
    {
        QMessageBox::warning(_mainWindow, "Ошибка удаления ключа", "Файла ключа " + rFile.fileName() + " не существует.");

        _mainWindow->RemoveKeyContainerFrame(_keyFrame);
    }
}
