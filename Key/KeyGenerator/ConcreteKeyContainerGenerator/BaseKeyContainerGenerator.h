#ifndef BASEKEYCONTAINERGENERATOR_H
#define BASEKEYCONTAINERGENERATOR_H

#include "Key/KeyGenerator/AKeyContainerGenerator.h"

class BaseKeyContainerGenerator : public AKeyContainerGenerator
{

public:

    BaseKeyContainerGenerator() = default;

    Q_DISABLE_COPY(BaseKeyContainerGenerator);

    // AKeyContainerGenerator interface
public:
    virtual AKeyContainer *generateContainer(AKeyGenerator *keyGen) const override;
};

#endif // BASEKEYCONTAINERGENERATOR_H
