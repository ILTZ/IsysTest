#ifndef BASEKEYCONTAINER_H
#define BASEKEYCONTAINER_H

#include <QString>
#include <QScopedPointer>

#include "Key/KeyContainer/AKeyContainer.h"
#include "Key/Key/APrivateKey.h"
#include "Key/Key/APublicKey.h"

class BaseKeyContainer : public AKeyContainer
{

    QScopedPointer<APrivateKey> _privateKey;
    QScopedPointer<APublicKey>  _publickKey;

    QString _fileName;

public:

    explicit BaseKeyContainer(APrivateKey* privateKey, APublicKey* publicKey, const QString& fileName = { });

public:

    bool verify(const QByteArray &data, const QByteArray &signature)    const override;
    QByteArray sign(const QByteArray &data)                             const override;

    virtual QByteArray getPublicPart()                                  const override;
    virtual QByteArray getPrivatePart()                                 const override;

    virtual QString    getFileName()                                    const override;
    virtual void       setFileName(const QString& fileName)                   override;
};

#endif // BASEKEYCONTAINER_H
