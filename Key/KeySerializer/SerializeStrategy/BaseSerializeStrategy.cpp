#include "BaseSerializeStrategy.h"

#include "../../KeyContainer/ConcreteContainer/BaseKeyContainer.h"
#include "../../Key/ConcreteKey/BasePrivateKey.h"
#include "../../Key/ConcreteKey/BasePublicKey.h"

#include <QDataStream>

BaseSerializeStrategy::BaseSerializeStrategy()
    : ASerializeStrategy { AKeyContainerSerializer::SerializeFormat::BASE_FORMAT }
{

}

QByteArray BaseSerializeStrategy::serialize(AKeyContainer *container) const
{
    QByteArray  temp;
    QDataStream ds (&temp, QDataStream::WriteOnly);

    ds << container->getPublicPart() << container->getPrivatePart();

    return temp;
}

AKeyContainer *BaseSerializeStrategy::deserialize(const QByteArray &data) const
{
    QDataStream ds(data);

    QByteArray publicPart, privatePart;

    ds >> publicPart >> privatePart;

    APrivateKey* privKey { new BasePrivateKey { privatePart } };
    APublicKey*  pubKey  { new BasePublicKey  { publicPart  } };

    AKeyContainer* container { new BaseKeyContainer { privKey, pubKey } };

    return container;
}
