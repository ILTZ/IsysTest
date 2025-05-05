#ifndef PLATFORMTRAYICONFACTORY_H
#define PLATFORMTRAYICONFACTORY_H

#include "TrayIcon/ATrayIconFactory.h"

class PlatformTrayIconFactory : public ATrayIconFactory
{

public:

    PlatformTrayIconFactory() = default;

    virtual ATrayIcon* createTrayIcon(QObject* parent = nullptr) const override;
};

#endif // PLATFORMTRAYICONFACTORY_H
