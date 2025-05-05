#ifndef BASEKEYGENERATOR_H
#define BASEKEYGENERATOR_H

#include <QScopedPointer>
#include "Key/KeyGenerator/AKeyGenerator.h"
#include "Key/KeyGenerator/AKeyGenerateStrategy.h"

class BaseKeyGenerator : public AKeyGenerator
{

    QScopedPointer<AKeyGenerateStrategy> _strategy;

public:

    BaseKeyGenerator(AKeyGenerator::KeyGeneratorAlgorithm algorithm = AKeyGenerator::KeyGeneratorAlgorithm::BASE);

    Q_DISABLE_COPY(BaseKeyGenerator)

    // AKeyGenerator interface
public:
    virtual QByteArray generatePublicKey(const QByteArray &privateKey)  const override;
    virtual QByteArray generatePrivateKey()                             const override;

    virtual void setAlgorithm(AKeyGenerator::KeyGeneratorAlgorithm algorithm)   override;
    virtual KeyGeneratorAlgorithm getAlgorithm() const noexcept                 override;
};

#endif // BASEKEYGENERATOR_H
