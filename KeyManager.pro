QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += USE_NATIVE_QT_TRAY_ICON

SOURCES += \
    Key/Key/ConcreteKey/BasePrivateKey.cpp \
    Key/Key/ConcreteKey/BasePublicKey.cpp \
    Key/KeyContainer/ConcreteContainer/BaseKeyContainer.cpp \
    Key/KeyFrame/ConcreteKeyContainerFrame/ConcreteContainerFrame.cpp \
    Key/KeyGenerator/ConcreteKeyContainerGenerator/BaseKeyContainerGenerator.cpp \
    Key/KeyGenerator/ConcreteKeyGenerator/BaseKeyGenerator.cpp \
    Key/KeyGenerator/GenerateStrategy/BaseGenerateStrategy.cpp \
    Key/KeyGenerator/GenerateStrategy/GenerateStrategyFactory.cpp \
    Key/KeySerializer/AKeyContainerSerializer.cpp \
    Key/KeySerializer/ConcreteKeyContainerSerializer/BaseKeyContainerSerializer.cpp \
    Key/KeySerializer/SerializeStrategy/BaseSerializeStrategy.cpp \
    Key/KeySerializer/SerializeStrategy/SerializeStrategyFactory.cpp \
    Command/MWCommand/CreateKeyCommand.cpp \
    Command/MWCommand/RemoveKeyComand.cpp \
    Command/MWCommand/UnloadKeyCommand.cpp \
    Command/MWCommand/UploadKeyFromDirectoryCommand.cpp \
    Command/MWCommand/UploadKeyFromFileCommand.cpp \
    TrayIcon/ConcreteTrayIcon/NativeQtTrayIcon.cpp \
    TrayIcon/ConcreteTrayIconFactory/PlatformTrayIconFactory.cpp \
    main.cpp \
    MainWindow\mainwindow.cpp

HEADERS += \
    Key/Key/AKey.h \
    Key/Key/APrivateKey.h \
    Key/Key/APublicKey.h \
    Key/Key/ConcreteKey/BasePrivateKey.h \
    Key/Key/ConcreteKey/BasePublicKey.h \
    Key/KeyContainer/AKeyContainer.h \
    Key/KeyContainer/ConcreteContainer/BaseKeyContainer.h \
    Key/KeyFrame/AKeyFrameContainer.h \
    Key/KeyFrame/ConcreteKeyContainerFrame/ConcreteContainerFrame.h \
    Key/KeyGenerator/AKeyContainerGenerator.h \
    Key/KeyGenerator/AKeyGenerateStrategy.h \
    Key/KeyGenerator/AKeyGenerator.h \
    Key/KeyGenerator/ConcreteKeyContainerGenerator/BaseKeyContainerGenerator.h \
    Key/KeyGenerator/ConcreteKeyGenerator/BaseKeyGenerator.h \
    Key/KeyGenerator/GenerateStrategy/BaseGenerateStrategy.h \
    Key/KeyGenerator/GenerateStrategy/GenerateStrategyFactory.h \
    Key/KeySerializer/AKeyContainerSerializer.h \
    Key/KeySerializer/ASerializeStrategy.h \
    Key/KeySerializer/ConcreteKeyContainerSerializer/BaseKeyContainerSerializer.h \
    Key/KeySerializer/SerializeStrategy/BaseSerializeStrategy.h \
    Key/KeySerializer/SerializeStrategy/SerializeStrategyFactory.h \
    Command/ACommand.h \
    Command/MWCommand/CreateKeyCommand.h \
    Command/MWCommand/RemoveKeyComand.h \
    Command/MWCommand/UnloadKeyCommand.h \
    Command/MWCommand/UploadKeyFromDirectoryCommand.h \
    Command/MWCommand/UploadKeyFromFileCommand.h \
    TrayIcon/ATrayIcon.h \
    TrayIcon/ATrayIconFactory.h \
    TrayIcon/ConcreteTrayIcon/NativeQtTrayIcon.h \
    TrayIcon/ConcreteTrayIconFactory/PlatformTrayIconFactory.h \
    MainWindow\mainwindow.h

FORMS += \
    Key/KeyFrame/ConcreteKeyContainerFrame/ConcreteContainerFrame.ui \
    MainWindow\mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
