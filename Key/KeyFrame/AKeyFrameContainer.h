#ifndef AKEYFRAMECONTAINER_H
#define AKEYFRAMECONTAINER_H

#include "Key/KeyContainer/AKeyContainer.h"
#include <QFrame>

class AKeyContainerFrame : public QFrame
{

    Q_OBJECT

public:

    explicit AKeyContainerFrame(QWidget* parent = nullptr)
        : QFrame { parent }
    {

    }

    virtual ~AKeyContainerFrame() = default;

    Q_DISABLE_COPY(AKeyContainerFrame);

    virtual QSharedPointer<AKeyContainer> getKeyContainer()           const = 0;
    virtual void setKeyContainer(QSharedPointer<AKeyContainer> key)         = 0;

    virtual void setKeyReadyState(bool ready)   = 0;
    virtual bool getKeyReadyState() const       = 0;
};

#endif // AKEYFRAMECONTAINER_H
