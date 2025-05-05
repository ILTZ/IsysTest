#ifndef BASEKEYCONTAINERSERIALIZER_H
#define BASEKEYCONTAINERSERIALIZER_H

#include "Key/KeySerializer/AKeyContainerSerializer.h"
#include "Key/KeySerializer/ASerializeStrategy.h"

class BaseKeyContainerSerializer : public AKeyContainerSerializer
{

    QScopedPointer<ASerializeStrategy> _strategy;

    mutable QString _errorString;

public:
    
    BaseKeyContainerSerializer(AKeyContainerSerializer::SerializeFormat format = AKeyContainerSerializer::SerializeFormat::BASE_FORMAT);

    Q_DISABLE_COPY(BaseKeyContainerSerializer)

public:

    virtual QByteArray serialize(AKeyContainer* container)                     const override;
    [[nodiscard]] virtual AKeyContainer* deserialize(const QByteArray &data)   const override;

    virtual bool serialize(AKeyContainer *container, const QString &fileName)   const override;
    [[nodiscard]] virtual AKeyContainer *deserialize(const QString &fileName)   const override;

    virtual void setSerializeFormat(SerializeFormat format)                           override;
    virtual SerializeFormat getSerializeFormat()                                const override;

    virtual QSet<SerializeFormat> supportedFormats()                            const override;

    virtual QString errorString()                                               const override;
};

#endif // BASEKEYCONTAINERSERIALIZER_H
