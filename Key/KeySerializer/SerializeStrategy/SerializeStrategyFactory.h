#ifndef SERIALIZESTRATEGYFACTORY_H
#define SERIALIZESTRATEGYFACTORY_H

#include "Key/KeySerializer/ASerializeStrategy.h"
#include "Key/KeySerializer/AKeyContainerSerializer.h"

#include <QSet>

class SerializeStrategyFactory
{

public:

    SerializeStrategyFactory() = default;
    
    [[nodiscard]] virtual ASerializeStrategy* createStrategy(AKeyContainerSerializer::SerializeFormat format) const;

    virtual QSet<AKeyContainerSerializer::SerializeFormat> supportedFormats() const;
};

#endif // SERIALIZESTRATEGYFACTORY_H
