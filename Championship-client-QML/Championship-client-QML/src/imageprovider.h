#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "QQuickImageProvider"
#include <QDebug>

class ImageProvider : public QObject, public QQuickImageProvider
{
    Q_OBJECT
public:
    explicit ImageProvider(ImageType type, QObject *parent = nullptr, Flags flags = nullptr);
    ~ImageProvider() override = default;

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    QImage newImage;

signals:
    void signalImageFromDB(int);

public slots:
    void slotGetImageFromDB(QImage);
};

#endif // IMAGEPROVIDER_H
