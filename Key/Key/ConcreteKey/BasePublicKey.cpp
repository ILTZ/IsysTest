#include "BasePublicKey.h"

BasePublicKey::BasePublicKey(const QByteArray &keyBinary)
    : _key { keyBinary }
{

}

QByteArray BasePublicKey::toByteArray() const
{
    return _key;
}

bool BasePublicKey::verify(const QByteArray &data, const QByteArray &signature) const
{
    Q_UNUSED(data);
    Q_UNUSED(signature);

    /* Какая - то проверка на корректность подписи */

    return true;
}
