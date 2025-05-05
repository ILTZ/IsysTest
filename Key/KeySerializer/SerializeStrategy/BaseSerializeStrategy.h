#ifndef BASESERIALIZESTRATEGY_H
#define BASESERIALIZESTRATEGY_H

#include "Key/KeySerializer/ASerializeStrategy.h"

class BaseSerializeStrategy : public ASerializeStrategy
{
public:

    BaseSerializeStrategy();

    Q_DISABLE_COPY(BaseSerializeStrategy);

    virtual QByteArray serialize(AKeyContainer *container)      const override;
    virtual AKeyContainer *deserialize(const QByteArray &data)  const override;
};

#endif // BASESERIALIZESTRATEGY_H
