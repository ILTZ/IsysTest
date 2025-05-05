#include "BaseKeyContainerGenerator.h"

#include "Key/KeyContainer/ConcreteContainer/BaseKeyContainer.h"
#include "Key/Key/ConcreteKey/BasePrivateKey.h"
#include "Key/Key/ConcreteKey/BasePublicKey.h"

AKeyContainer *BaseKeyContainerGenerator::generateContainer(AKeyGenerator *keyGen) const
{
    AKeyContainer* temp { nullptr };

    if (keyGen)
    {
        auto privatePart = keyGen->generatePrivateKey();
        auto publickPart = keyGen->generatePublicKey(privatePart);

        auto privateKey = new BasePrivateKey    { privatePart };
        auto publicKey  = new BasePublicKey     { publickPart };

        temp = new BaseKeyContainer { privateKey, publicKey };
    }

    return temp;
}
