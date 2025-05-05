#include "AKeyContainerSerializer.h"

QStringList AKeyContainerSerializer::getFileExtensions(SerializeFormat format)
{
    QStringList temp;

    switch (format)
    {
        case SerializeFormat::BASE_FORMAT:
        {
            temp.append(".key");
        }
        break;

        default:
            break;
    }

    return temp;
}
