#ifndef BASEPUBLICKEY_H
#define BASEPUBLICKEY_H

#include "Key/Key/APublicKey.h"

class BasePublicKey : public APublicKey
{

    QByteArray _key;

public:

    BasePublicKey(const QByteArray& keyBinary);

    // AKey interface
public:
    QByteArray toByteArray() const;

    // APublicKey interface
public:
    bool verify(const QByteArray &data, const QByteArray &signature) const;
};

#endif // BASEPUBLICKEY_H
