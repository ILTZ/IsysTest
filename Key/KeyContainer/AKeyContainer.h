#ifndef AKEYCONTAINER_H
#define AKEYCONTAINER_H

#include <QByteArray>

class AKeyContainer
{
public:

    AKeyContainer()             = default;
    virtual ~AKeyContainer()    = default;

    virtual bool verify(const QByteArray& data, const QByteArray& signature)    const = 0;
    virtual QByteArray sign(const QByteArray& data)                             const = 0;

    virtual QByteArray getPublicPart()  const = 0;
    virtual QByteArray getPrivatePart() const = 0;

    virtual QString  getFileName()                          const = 0;
    virtual void     setFileName(const QString& fileName)         = 0;
};

#endif // AKEYCONTAINER_H
