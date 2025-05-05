#include "BasePrivateKey.h"

BasePrivateKey::BasePrivateKey(const QByteArray &keyBinary)
    : _key { keyBinary }
{

}

QByteArray BasePrivateKey::toByteArray() const
{
    return _key;
}

QByteArray BasePrivateKey::sign(const QByteArray &data) const
{
    /* Выполнили подписание */

    return data;
}
