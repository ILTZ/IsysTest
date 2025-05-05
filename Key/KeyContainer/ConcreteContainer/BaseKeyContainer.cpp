#include "BaseKeyContainer.h"

BaseKeyContainer::BaseKeyContainer(APrivateKey *privateKey, APublicKey *publicKey, const QString& fileName)
    : _privateKey { privateKey }
    , _publickKey { publicKey  }
    , _fileName   { fileName }
{

}

bool BaseKeyContainer::verify(const QByteArray &data, const QByteArray &signature) const
{
    return _publickKey->verify(data, signature);
}

QByteArray BaseKeyContainer::sign(const QByteArray &data) const
{
    return _privateKey->sign(data);
}

QByteArray BaseKeyContainer::getPublicPart() const
{
    return _publickKey->toByteArray();
}

QByteArray BaseKeyContainer::getPrivatePart() const
{
    return _privateKey->toByteArray();
}

QString BaseKeyContainer::getFileName() const
{
    return _fileName;
}

void BaseKeyContainer::setFileName(const QString &fileName)
{
    _fileName = fileName;
}
