#ifndef APRIVATEKEY_H
#define APRIVATEKEY_H

#include "AKey.h"

class APrivateKey : public AKey
{
public:

    APrivateKey() = default;

    virtual QByteArray sign(const QByteArray& data) const = 0;
};

#endif // APRIVATEKEY_H
