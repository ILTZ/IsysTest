#ifndef AKEYGENERATESTRATEGY_H
#define AKEYGENERATESTRATEGY_H

#include <QByteArray>

#include "Key/KeyGenerator/AKeyGenerator.h"

class AKeyGenerateStrategy
{

    AKeyGenerator::KeyGeneratorAlgorithm _algorithm;

public:

    AKeyGenerateStrategy(AKeyGenerator::KeyGeneratorAlgorithm algorithm)
        : _algorithm { algorithm }
    {

    }

    virtual ~AKeyGenerateStrategy() = default;

    virtual QByteArray generatePublicKey(const QByteArray& privateKey)  const = 0;
    virtual QByteArray generatePrivateKey()                             const = 0;

    AKeyGenerator::KeyGeneratorAlgorithm getAlgorithm() const noexcept { return _algorithm; }
};

#endif // AKEYGENERATESTRATEGY_H
