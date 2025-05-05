#ifndef BASEGENERATESTRATEGY_H
#define BASEGENERATESTRATEGY_H

#include "Key/KeyGenerator/AKeyGenerateStrategy.h"

class BaseGenerateStrategy : public AKeyGenerateStrategy
{
public:

    BaseGenerateStrategy();

    Q_DISABLE_COPY(BaseGenerateStrategy);

    virtual QByteArray generatePublicKey(const QByteArray &privateKey)  const override;
    virtual QByteArray generatePrivateKey()                             const override;
};

#endif // BASEGENERATESTRATEGY_H
