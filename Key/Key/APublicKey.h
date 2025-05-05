#ifndef APUBLICKEY_H
#define APUBLICKEY_H

#include "AKey.h"

class APublicKey : public AKey
{

public:

    APublicKey() = default;

    Q_DISABLE_COPY(APublicKey);

    virtual bool verify(const QByteArray& date, const QByteArray& signature) const = 0;
};

#endif // APUBLICKEY_H
