#include "ConcreteContainerFrame.h"
#include "ui_ConcreteContainerFrame.h"

bool TextEditEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    // Отменяем выделение текста после переключения на другие элементы
    if (event->type() == QEvent::FocusOut)
    {
        if (auto textEdit = qobject_cast<QTextEdit*>(obj))
        {
            QTextCursor cursor = textEdit->textCursor();
            cursor.clearSelection();
            textEdit->setTextCursor(cursor);
        }
    }
    return QObject::eventFilter(obj, event);
}

BaseContainerFrame::BaseContainerFrame(QWidget *parent) :
    AKeyContainerFrame  { parent },
    ui                  { new Ui::ConcreteContainerFrame }
{
    ui->setupUi(this);

    ui->statusL->setAutoFillBackground(true);
    
    BaseContainerFrame::setKeyReadyState(false);

    // Они тут ни к чему
    ui->privatePartTE->setContextMenuPolicy (Qt::NoContextMenu);
    ui->publicPartTE->setContextMenuPolicy  (Qt::NoContextMenu);

    ui->privatePartTE->installEventFilter   (new TextEditEventFilter(ui->privatePartTE));
    ui->publicPartTE->installEventFilter    (new TextEditEventFilter(ui->publicPartTE));

    ui->keyPathL->setToolTip("Расположение файла ключа");
}

BaseContainerFrame::~BaseContainerFrame()
{
    delete ui;
}

QSharedPointer<AKeyContainer> BaseContainerFrame::getKeyContainer() const
{
    return _keyContainer;
}

void BaseContainerFrame::setKeyContainer(QSharedPointer<AKeyContainer> key)
{
    if (_keyContainer = key; _keyContainer)
    {
        ui->publicPartTE->setText   (_keyContainer->getPublicPart().toHex(' '));
        ui->privatePartTE->setText  (_keyContainer->getPrivatePart().toHex(' '));
        ui->keyPathL->setText       (_keyContainer->getFileName());
    }
    else
    {
        ui->publicPartTE->setText   ("");
        ui->privatePartTE->setText  ("");
        ui->keyPathL->setText       ("");
    }
}

void BaseContainerFrame::setKeyReadyState(bool ready)
{
    if (_isKeyReady = ready; _isKeyReady)
    {
        auto palette = ui->statusL->palette();
        palette.setColor(QPalette::Window, Qt::green);                
        ui->statusL->setPalette(palette);
        ui->statusL->setToolTip("Ключ готов к работе");
    }
    else
    {
        auto palette = ui->statusL->palette();
        palette.setColor(QPalette::Window, Qt::red);
        ui->statusL->setPalette(palette);
        ui->statusL->setToolTip("Ключ не готов к работе");
    }
}

bool BaseContainerFrame::getKeyReadyState() const
{
    return _isKeyReady;
}
