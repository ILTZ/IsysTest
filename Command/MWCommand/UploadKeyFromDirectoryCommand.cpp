#include "UploadKeyFromDirectoryCommand.h"

#include <QDir>

#include "MainWindow/mainwindow.h"
#include "Key/KeySerializer/ConcreteKeyContainerSerializer/BaseKeyContainerSerializer.h"
#include "Key/KeyFrame/ConcreteKeyContainerFrame/ConcreteContainerFrame.h"

QVector<QSharedPointer<AKeyContainer>> deserializeKeyes(const QFileInfoList& fileInfoList, AKeyContainerSerializer& ser)
{
    using SFormat = AKeyContainerSerializer::SerializeFormat;

    QHash<SFormat, QString> extensions;

    auto formats = ser.supportedFormats();

    for (auto el : formats)
        extensions.insert(el, AKeyContainerSerializer::getFileExtensions(el).join(','));

    QHash<SFormat, QStringList> files;

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    // Сначала отберем те файлы, которые сможем десереализовать сереализатором
    for (const auto& fileInfo : fileInfoList)
    {
        for (auto it = extensions.cbegin(); it != extensions.cend(); ++it)
        {
            if (it.value().contains(fileInfo.suffix()))
            {
                files[it.key()].append(fileInfo.absoluteFilePath());
                break;
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    QVector<QSharedPointer<AKeyContainer>> temp;

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    // Теперь будем разбирать доступные файлы
    for (auto it = files.cbegin(); it != files.cend(); ++it)
    {
        ser.setSerializeFormat(it.key());

        for (const auto& el : it.value())
        {
            if (QSharedPointer<AKeyContainer> container { ser.deserialize(el) }; container)
            {
                temp.append(container);
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    return temp;
}

void addKeyContainerFrame(QSharedPointer<AKeyContainer> keyContainer, MainWindow* wnd)
{
    auto keyContainerFrame = new BaseContainerFrame{ };
    keyContainerFrame->setKeyContainer(keyContainer);
    keyContainerFrame->setKeyReadyState(true);

    wnd->AddKeyContainerFrame(keyContainerFrame);
}

UploadKeyFromDirectoryCommand::UploadKeyFromDirectoryCommand(MainWindow *wnd, const QString &targetDir, const QString &keyDir, QObject *parent)
    : ACommand      { parent }
    , _mainWindow   { wnd }
    , _dirPath      { targetDir }
    , _keyDir       { keyDir }
{

}

void UploadKeyFromDirectoryCommand::execute()
{
    QDir keyDir(_dirPath);

    if (keyDir.exists())
    {
        auto fileInfoList = keyDir.entryInfoList();

        BaseKeyContainerSerializer ser;

        if (auto keyes = deserializeKeyes(fileInfoList, ser); keyes.empty() == false)
        {
            for (auto& el : keyes)
            {
                QFileInfo   cFile(el->getFileName());
                QString     cPath(_keyDir + '/' + cFile.fileName());

                if ((cFile.filePath() != cPath) && (QFile::exists(cPath) == false))
                {
                    if (QFile temp(cFile.filePath()); temp.copy(cPath) == false)
                    {
                        // Не удалось скопировать в дефолтную папку для ключей
                        continue;
                    }
                }

                addKeyContainerFrame(el, _mainWindow);
            }
        }
    }
}
