#include "GenerateStrategyFactory.h"

#include "BaseGenerateStrategy.h"

GenerateStrategyFactory::GenerateStrategyFactory()
{

}

AKeyGenerateStrategy *GenerateStrategyFactory::createStrategy(AKeyGenerator::KeyGeneratorAlgorithm algorithm)
{
    using gType = AKeyGenerator::KeyGeneratorAlgorithm;

    AKeyGenerateStrategy* temp { nullptr };

    switch (algorithm)
    {
        case gType::BASE:
        {
            temp = new BaseGenerateStrategy { };
        }

        default:
            break;
    }

    return temp;
}
