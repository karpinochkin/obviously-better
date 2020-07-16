#include "imageprovider.h"

ImageProvider::ImageProvider(QQmlImageProviderBase::ImageType type, QObject *parent, QQmlImageProviderBase::Flags flags)
    : QObject(parent) , QQuickImageProvider(type,flags)
{

}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)

    emit signalImageFromDB(id.toInt());

    return newImage;
}

void ImageProvider::slotGetImageFromDB(QImage image)
{
    newImage = image;
}
