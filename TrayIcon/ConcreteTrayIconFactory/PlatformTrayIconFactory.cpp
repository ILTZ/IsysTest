#include "PlatformTrayIconFactory.h"

#ifdef USE_NATIVE_QT_TRAY_ICON

    #include "TrayIcon/ConcreteTrayIcon/NativeQtTrayIcon.h"
    #define PlatformIconInstance new NativeQtTrayIcon{ parent }

#else

    #define PlatformIconInstance nullptr

#endif

ATrayIcon *PlatformTrayIconFactory::createTrayIcon(QObject* parent) const
{
    return PlatformIconInstance;
}
