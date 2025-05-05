#ifndef CONCRETECONTAINERFRAME_H
#define CONCRETECONTAINERFRAME_H

#include "Key/KeyFrame/AKeyFrameContainer.h"

namespace Ui {
class ConcreteContainerFrame;
}

class TextEditEventFilter : public QObject
{

    Q_OBJECT

public:

    using QObject::QObject;

    virtual bool eventFilter(QObject *obj, QEvent *event) override;
};

class BaseContainerFrame : public AKeyContainerFrame
{
    Q_OBJECT

    Ui::ConcreteContainerFrame *ui;

    QSharedPointer<AKeyContainer> _keyContainer;

    bool _isKeyReady;

public:

    explicit BaseContainerFrame(QWidget *parent = nullptr);
    ~BaseContainerFrame();

    Q_DISABLE_COPY(BaseContainerFrame);


    // AKeyFrameContainer interface
public:

    virtual QSharedPointer<AKeyContainer> getKeyContainer() const   override;
    virtual void setKeyContainer(QSharedPointer<AKeyContainer> key) override;

    virtual void setKeyReadyState(bool ready)                       override;
    virtual bool getKeyReadyState() const                           override;
};

#endif // CONCRETECONTAINERFRAME_H
