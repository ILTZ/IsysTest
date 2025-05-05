#ifndef AKEYCONTAINERGENERATOR_H
#define AKEYCONTAINERGENERATOR_H

#include "Key/KeyContainer/AKeyContainer.h"
#include "AKeyGenerator.h"

class AKeyContainerGenerator
{

public:

    virtual ~AKeyContainerGenerator() = default;

    virtual AKeyContainer* generateContainer(AKeyGenerator* keyGen) const = 0;
};


#endif // AKEYCONTAINERGENERATOR_H
