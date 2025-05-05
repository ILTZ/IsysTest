#include "SerializeStrategyFactory.h"

#include "Key/KeySerializer/SerializeStrategy/BaseSerializeStrategy.h"

using sStrategy = AKeyContainerSerializer::SerializeFormat;

ASerializeStrategy *SerializeStrategyFactory::createStrategy(AKeyContainerSerializer::SerializeFormat format) const
{    
    ASerializeStrategy* strategy { nullptr };

    switch (format)
    {
        case sStrategy::BASE_FORMAT:
        {
            strategy = new BaseSerializeStrategy{ };
        }
        break;

        default:
            break;
    }

    return strategy;
}

QSet<AKeyContainerSerializer::SerializeFormat> SerializeStrategyFactory::supportedFormats() const
{
    return { sStrategy::BASE_FORMAT };
}
