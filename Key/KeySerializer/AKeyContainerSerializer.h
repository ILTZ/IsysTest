#ifndef AKEYCONTAINERSERIALIZER_H
#define AKEYCONTAINERSERIALIZER_H

#include <QVector>
#include <QStringList>
#include <QSharedPointer>

#include "../KeyContainer/AKeyContainer.h"

class AKeyContainerSerializer
{

public:

    enum class SerializeFormat
    {
        BASE_FORMAT = 0,
    };

public:

    virtual ~AKeyContainerSerializer() = default;

    virtual QByteArray serialize(AKeyContainer* container)                      const = 0;
    [[nodiscard]] virtual AKeyContainer* deserialize(const QByteArray& data)    const = 0;

    virtual bool serialize(AKeyContainer* container, const QString& fileName)   const = 0;
    [[nodiscard]] virtual AKeyContainer* deserialize(const QString& fileName)   const = 0;

    virtual void setSerializeFormat(SerializeFormat format)                           = 0;
    virtual SerializeFormat getSerializeFormat()                                const = 0;

    virtual QSet<SerializeFormat> supportedFormats()                            const = 0;

    virtual QString errorString()                                               const = 0;

    static QStringList getFileExtensions(SerializeFormat format);
};

#endif // AKEYCONTAINERSERIALIZER_H
