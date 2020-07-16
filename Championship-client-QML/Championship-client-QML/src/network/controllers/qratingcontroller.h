#ifndef QRATINGCONTROLLER_H
#define QRATINGCONTROLLER_H

#include <QObject>
#include "../../models/rating.h"
#include "qabstractcontroller.h"

namespace Controllers {

class QRatingController : public QAbstractController
{
    Q_OBJECT
public:
    explicit QRatingController(QDatabaseController *db, QObject *parent = nullptr);
    ~QRatingController() override = default;

    void Create(QByteArray);
    void GetByContest(QByteArray);

signals:
    void signalCreate();
    void signalGetByContest(const QVector<Models::Rating> &rating);
};

}
#endif // QRATINGCONTROLLER_H
