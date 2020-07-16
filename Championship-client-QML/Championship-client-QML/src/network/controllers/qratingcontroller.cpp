#include "qratingcontroller.h"

Controllers::QRatingController::QRatingController(QDatabaseController *db, QObject *parent)
    : QAbstractController(db, parent)
{

}

void Controllers::QRatingController::Create(QByteArray data)
{
    Q_UNUSED(data)
    emit (signalCreate());
}

void Controllers::QRatingController::GetByContest(QByteArray data)
{
    try {
        QVector<Models::Rating> rating {};
        arrayModelsProcessing(data, rating);
        emit (signalGetByContest(rating));
    }
    catch(const QString& err) {
        qDebug() << "Controllers::QRatingController::GetByContest(QByteArray data) : " + err;
    }
}
