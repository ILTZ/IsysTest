#include "BaseKeyGenerator.h"

#include "Key/KeyGenerator/GenerateStrategy/GenerateStrategyFactory.h"
#include "Key/KeyGenerator/AKeyGenerateStrategy.h"

BaseKeyGenerator::BaseKeyGenerator(KeyGeneratorAlgorithm algorithm)
{
    BaseKeyGenerator::setAlgorithm(algorithm);
}

QByteArray BaseKeyGenerator::generatePublicKey(const QByteArray &privateKey) const
{
    return _strategy->generatePublicKey(privateKey);
}

QByteArray BaseKeyGenerator::generatePrivateKey() const
{
    return _strategy->generatePrivateKey();
}

void BaseKeyGenerator::setAlgorithm(KeyGeneratorAlgorithm algorithm)
{

    GenerateStrategyFactory factory;

    _strategy.reset(factory.createStrategy(algorithm));

    Q_ASSERT(_strategy);
}

AKeyGenerator::KeyGeneratorAlgorithm BaseKeyGenerator::getAlgorithm() const noexcept
{
    return _strategy->getAlgorithm();
}
