#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QContextMenuEvent>
#include <QCloseEvent>
#include <QEvent>

#include <QDir>
#include <QSettings>
#include <QStyle>

#include "Key/KeyFrame/AKeyFrameContainer.h"

#include "Command/MWCommand/CreateKeyCommand.h"
#include "Command/MWCommand/UnloadKeyCommand.h"
#include "Command/MWCommand/RemoveKeyComand.h"

#include "Command/MWCommand/UploadKeyFromFileCommand.h"
#include "Command/MWCommand/UploadKeyFromDirectoryCommand.h"

#include "TrayIcon/ConcreteTrayIconFactory/PlatformTrayIconFactory.h"

#define SETTINGS_ARGS QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName()

template<typename T>
T* findFirstParentWidget(QWidget* widget)
{
    T* temp { nullptr };
    QWidget* tWidget = widget;

    while(tWidget)
    {
        if (auto result = qobject_cast<T*>(tWidget); result)
        {
            temp = result;
            break;
        }

        tWidget = tWidget->parentWidget();
    }

    return temp;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow   { parent }
    , ui            { new Ui::MainWindow }
    , _trayIcon     { nullptr }
{
    ui->setupUi(this);

    setWindowTitle(QApplication::applicationDisplayName());
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));

    // Для того, чтобы виджеты в QScrollArea прокручивались
    ui->keySA->setWidget(new QWidget(ui->keySA));
    ui->keySA->widget()->setLayout(new QVBoxLayout(ui->keySA->widget()));
    ui->keySA->widget()->layout()->setContentsMargins(15,15,15,15);
    ui->keySA->widget()->layout()->setSpacing(15);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Settings {
    {
        QSettings settings(SETTINGS_ARGS);

        _minimizeToTray = settings.value("Common/MinimizeToTray", false).toBool();
        _defaultKeyDir  = settings.value("Common/DefaultKeyDir", QDir::currentPath() + "/Keyes").toString();

        QDir dir { _defaultKeyDir };

        if (dir.exists() == false)
            dir.mkdir(_defaultKeyDir);
    }
    /// Settings }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Setup tray icon {
    {
        PlatformTrayIconFactory factory;

        if (_trayIcon = factory.createTrayIcon(this); _trayIcon)
        {
            _trayIcon->setIcon(windowIcon());

            #ifdef Q_OS_WIN
            {
                _trayIcon->addIconHandler(QSystemTrayIcon::DoubleClick, [this](ATrayIcon&)
                {
                    maximizeWnd();
                });
            }
            #endif

            // Не нашел способа корректно перехватывать сигнал хотябы одного клика по иконке
            // на Ubuntu 22.04 (с Gnome) - ayatan-appindicator3 не даёт такого сделать, GtkMenu
            // не вызвает сигналы по нажатию, а QSystemTrayIcon отбрабатывает лишь клики колесом.
            // Поэтому пусть будет дополнительное действие для разворота из трея.
            #ifdef Q_OS_LINUX
            {
                _trayIcon->addIconHandler(QSystemTrayIcon::MiddleClick, [this](ATrayIcon&)
                {
                    maximizeWnd();
                });

                _trayIcon->addMenuAction("Maximize", [this](const QAction&)
                {
                    maximizeWnd();
                });
            }
            #endif

            _trayIcon->addMenuAction("Quit", [&](const QAction&)
            {
                // Если пользователь из трея вызывает это действие - он точно хочет, чтобы приложение было закрыто.
                QApplication::quit();
            });

            //////////////////////////////////////////////////////////////////////////////
            /// Minimize to tray action {
            {
                QAction* minimizeToTrayAct { new QAction { ui->mwSettingsMenu } };
                minimizeToTrayAct->setText("Скрывать в трей при сворачивании");
                minimizeToTrayAct->setCheckable(true);
                minimizeToTrayAct->setChecked(_minimizeToTray);

                connect(minimizeToTrayAct, &QAction::toggled, this, [&](bool checked)
                {
                    _minimizeToTray = checked;
                });

                ui->mwSettingsMenu->addAction(minimizeToTrayAct);
            }
            /// Minimize to tray action }
            //////////////////////////////////////////////////////////////////////////////
        }
        else
        {
            _minimizeToTray = false;
        }
    }
    /// Setup tray icon }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Upload keyes from default dir {
    {
        UploadKeyFromDirectoryCommand uploadKeyesCommand(this, _defaultKeyDir, _defaultKeyDir);
        uploadKeyesCommand.execute();
    }
    /// Upload keyes from default dir }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
}

MainWindow::~MainWindow()
{
    QSettings settings(SETTINGS_ARGS);

    settings.setValue("Common/MinimizeToTray", _minimizeToTray);

    delete ui;
}

void MainWindow::maximizeWnd()
{
    if (isHidden())
    {
        setWindowState(windowState() & ~Qt::WindowMinimized);
        show();
        activateWindow();
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *e)
{
    auto contextMenuPos = e->globalPos();

    auto vPos        = ui->keySA->viewport()->mapFromGlobal(e->globalPos());
    auto widgetPos   = ui->keySA->widget()->mapFrom(ui->keySA->viewport(), vPos);
    auto childWidget = ui->keySA->widget()->childAt(widgetPos);

    QMenu menu(this);

    if (childWidget)
    {
        // Так мы и понимаем, что кликнули по нужному виджету, и получаем указатель на...
        // ...AKeyContainerFrame, необходимый для команд
        if (auto keyFrame = findFirstParentWidget<AKeyContainerFrame>(childWidget); keyFrame)
        {
            /////////////////////////////////////////////////////////////////////////
            /// Remove key {
            {
                auto action  = menu.addAction("Удалить ключ");
                auto command = new RemoveKeyComand(this, keyFrame, action);

                connect(action, &QAction::triggered, command, &ACommand::execute);
            }
            /// Remove key }
            /////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////
            /// Unload key {
            {
                auto action  = menu.addAction("Выгрузить ключ");
                auto command = new UnloadKeyCommand(this, keyFrame, AKeyContainerSerializer::SerializeFormat::BASE_FORMAT, action);

                // Если нужно выбирать формат - можно обернуть создание команды в лямбду (лямбду для сигнала QAction),
                // внутри устанавливать нужные значения и вызывать execute напрямую (или прописать отдельный обработчик для MainWindow)
                connect(action, &QAction::triggered, command, &ACommand::execute);
            }
            /// Unload key }
            /////////////////////////////////////////////////////////////////////////
        }
    }
    else
    {
        /////////////////////////////////////////////////////////////////////////
        /// Upload Key {
        {
            auto action     = menu.addAction("Загрузить ключ");
            auto command    = new UploadKeyFromFileCommand { this, _defaultKeyDir, AKeyContainerSerializer::SerializeFormat::BASE_FORMAT, action };

            // Если нужно выбирать формат - можно обернуть создание команды в лямбду (лямбду для сигнала QAction),
            // внутри устанавливать нужные значения и вызывать execute напрямую (или прописать отдельный обработчик для MainWindow)
            connect(action, &QAction::triggered, command, &ACommand::execute);
        }
        /// Upload Key }
        /////////////////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////////////////////////////
        /// Create key {
        {
            auto action   = menu.addAction("Создать новый ключ");
            auto command  = new CreateKeyCommand(this, AKeyGenerator::KeyGeneratorAlgorithm::BASE, AKeyContainerSerializer::SerializeFormat::BASE_FORMAT, _defaultKeyDir, action);

            // Если нужно выбирать алгоритм или формат - можно обернуть создание команды в лямбду (лямбду для сигнала QAction),
            // внутри устанавливать нужные значения и вызывать execute напрямую (или прописать отдельный обработчик для MainWindow)
            connect(action, &QAction::triggered, command, &ACommand::execute);
        }
        /// Create key }
        /////////////////////////////////////////////////////////////////////////
    }

    menu.exec(contextMenuPos);
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::WindowStateChange)
    {
        if (isMinimized() && _minimizeToTray)
        {
            hide();

            _trayIcon->showMessage("Информация", "Приложение продолжит работать в фоновом режиме", QSystemTrayIcon::Information, 1000);

            return;
        }
    }

    QMainWindow::changeEvent(e);    
}

void MainWindow::AddKeyContainerFrame(AKeyContainerFrame *keyContainer)
{
    if (keyContainer)
    {
        keyContainer->setParent(ui->keySA->widget());
        ui->keySA->widget()->layout()->addWidget(keyContainer);
    }
}

void MainWindow::RemoveKeyContainerFrame(AKeyContainerFrame *keyWidget)
{
    if (ui->keySA->widget()->children().contains(keyWidget))
    {
        ui->keySA->widget()->layout()->removeWidget(keyWidget);
        keyWidget->setParent(nullptr);
        keyWidget->deleteLater();
    }    
}
