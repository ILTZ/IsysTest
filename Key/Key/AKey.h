#ifndef AKEY
#define AKEY

#include <QByteArray>

class AKey
{

public:

    AKey()          = default;
    virtual ~AKey() = default;

    Q_DISABLE_COPY(AKey);

    virtual QByteArray toByteArray() const = 0;    
};

#endif // AKEY
