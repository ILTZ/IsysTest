#ifndef ATRAYICONFACTORY_H
#define ATRAYICONFACTORY_H

#include "ATrayIcon.h"

class MainWindow;

class ATrayIconFactory
{
public:

    virtual ~ATrayIconFactory() = default;

    [[nodiscard]] virtual ATrayIcon* createTrayIcon(QObject* parent = nullptr) const = 0;
};

#endif // ATRAYICONFACTORY_H
