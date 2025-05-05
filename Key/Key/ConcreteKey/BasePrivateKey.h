#ifndef BASEPRIVATEKEY_H
#define BASEPRIVATEKEY_H

#include "Key/Key/APrivateKey.h"

class BasePrivateKey : public APrivateKey
{
    QByteArray _key;

public:

    BasePrivateKey(const QByteArray& keyBinary);

    // AKey interface
public:
    QByteArray toByteArray() const;

    // APrivateKey interface
public:
    QByteArray sign(const QByteArray &data) const;
};

#endif // BASEPRIVATEKEY_H
