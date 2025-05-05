#ifndef AKEYGENERATOR_H
#define AKEYGENERATOR_H

#include <QByteArray>

class AKeyGenerator
{
public:

    enum class KeyGeneratorAlgorithm
    {
        BASE = 0,
    };

public:

    virtual ~AKeyGenerator() = default;

    virtual QByteArray generatePublicKey(const QByteArray& privateKey)  const = 0;
    virtual QByteArray generatePrivateKey()                             const = 0;

    virtual void setAlgorithm(AKeyGenerator::KeyGeneratorAlgorithm algorithm) = 0;
    virtual KeyGeneratorAlgorithm getAlgorithm() const noexcept = 0;
};

#endif // AKEYGENERATOR_H
