#include "BaseKeyContainerSerializer.h"

#include <QFile>
#include <QDataStream>

#include "Key/KeySerializer/SerializeStrategy/SerializeStrategyFactory.h"

BaseKeyContainerSerializer::BaseKeyContainerSerializer(SerializeFormat format)
{
    BaseKeyContainerSerializer::setSerializeFormat(format);
}

QByteArray BaseKeyContainerSerializer::serialize(AKeyContainer* container) const
{
    Q_ASSERT(container);

    return _strategy->serialize(container);
}

AKeyContainer* BaseKeyContainerSerializer::deserialize(const QByteArray &data) const
{        
    return _strategy->deserialize(data);
}

bool BaseKeyContainerSerializer::serialize(AKeyContainer *container, const QString &fileName) const
{
    auto data = BaseKeyContainerSerializer::serialize(container);

    if (QFile file{fileName}; file.open(QFile::WriteOnly))
    {
        QDataStream ds { &file };

        ds << data;

        return true;
    }
    else
    {
        _errorString = file.errorString();
    }

    return false;
}

AKeyContainer *BaseKeyContainerSerializer::deserialize(const QString &fileName) const
{
    AKeyContainer* temp { nullptr };

    if (QFile file{fileName}; file.open(QFile::ReadOnly))
    {
        QByteArray data;
        QDataStream ds { &file };

        ds >> data;

        if (auto container = BaseKeyContainerSerializer::deserialize(data); container)
        {
            container->setFileName(fileName);
            temp = container;
        }
        else
        {
            _errorString = "Can't create instance of a AKeyContainer class";
        }
    }
    else
    {
        _errorString = file.errorString();
    }

    return temp;
}

void BaseKeyContainerSerializer::setSerializeFormat(SerializeFormat format)
{
    SerializeStrategyFactory factory;

    _strategy.reset(factory.createStrategy(format));

    Q_ASSERT(_strategy);
}

AKeyContainerSerializer::SerializeFormat BaseKeyContainerSerializer::getSerializeFormat() const
{
    return _strategy->getFormat();
}

QSet<AKeyContainerSerializer::SerializeFormat> BaseKeyContainerSerializer::supportedFormats() const
{
    SerializeStrategyFactory factory;

    return factory.supportedFormats();
}

QString BaseKeyContainerSerializer::errorString() const
{
    return _errorString;
}
