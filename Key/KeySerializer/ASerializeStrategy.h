#ifndef ASERIALIZESTRATEGY_H
#define ASERIALIZESTRATEGY_H

#include "Key/KeySerializer/AKeyContainerSerializer.h"

#include <QByteArray>

class AKeyContainer;

class ASerializeStrategy
{

    AKeyContainerSerializer::SerializeFormat _format;

public:

    ASerializeStrategy(AKeyContainerSerializer::SerializeFormat format)
        : _format { format }
    {

    }

    virtual ~ASerializeStrategy() = default;

    virtual QByteArray serialize(AKeyContainer* container)                      const = 0;
    [[nodiscard]] virtual AKeyContainer* deserialize(const QByteArray& data)    const = 0;

    AKeyContainerSerializer::SerializeFormat getFormat() const noexcept { return _format; }
};


#endif // ASERIALIZESTRATEGY_H
