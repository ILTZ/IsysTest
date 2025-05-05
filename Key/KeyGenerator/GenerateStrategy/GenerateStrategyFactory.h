#ifndef GENERATESTRATEGYFACTORY_H
#define GENERATESTRATEGYFACTORY_H

#include "Key/KeyGenerator/AKeyGenerator.h"
#include "Key/KeyGenerator/AKeyGenerateStrategy.h"

class GenerateStrategyFactory
{

public:

    GenerateStrategyFactory();
    virtual ~GenerateStrategyFactory() = default;

    Q_DISABLE_COPY(GenerateStrategyFactory);

    [[nodiscard]] virtual AKeyGenerateStrategy* createStrategy(AKeyGenerator::KeyGeneratorAlgorithm algorithm);

};

#endif // GENERATESTRATEGYFACTORY_H
