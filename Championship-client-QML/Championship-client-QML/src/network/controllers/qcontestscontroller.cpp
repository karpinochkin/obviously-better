#include "qcontestscontroller.h"
#include <QDebug>

Controllers::QContestController::QContestController(QDatabaseController *db, QObject *parent)
    : QAbstractController(db, parent)
{

}

void Controllers::QContestController::Get(QByteArray data)
{
    Models::Contest contest {};
    try {
        modelProcessing(data, contest);
        bool result = sendToDatabase(contest);
        resultCheck(result);
        emit (signalGet(contest));
    }
    catch(const QString& err) {
        qDebug() << "error : Controllers::QContestsController::GetAll(QByteArray data) : " + err;
    }
}

void Controllers::QContestController::GetAll(QByteArray data)
{
    try {
        QVector<Models::Contest> contests {};
        arrayModelsProcessing(data, contests);
        clearDatabaseTable();
        sendContestsToDatabase(contests);
        emit (signalGetAll(contests));
    }
    catch(const QString& err) {
        qDebug() << "Controllers::QContestsController::Get(QByteArray data) : " + err;
    }
}

void Controllers::QContestController::Count(QByteArray data)
{
    quint32 count = data.toUInt();
    emit (signalCount(count));
}

void Controllers::QContestController::GetByRange(QByteArray data)
{
    QVector<Models::Contest> contests {};
    try {
        arrayModelsProcessing(data, contests);
        sendContestsToDatabase(contests);
        emit (signalGetByRangeLoaded(contests));
    }
    catch(const QString& err) {
        qDebug() << "Controllers::QContestsController::GetByRange(QByteArray data) : " + err;
    }
}

void Controllers::QContestController::CountMemberTypes(QByteArray data)
{
    quint32 count = data.toUInt();
    emit (signalCountMemberTypes(count));
}

void Controllers::QContestController::GetMemberTypes(QByteArray data)
{
    QVector<quint32> output;
    auto json = QJsonDocument::fromJson(data);
    try {
        arrayCheck(json);
        QJsonArray memberTypesJSON = json.array();
        for (auto val : memberTypesJSON) {
            if (val.toObject().contains("id")) {
                output.push_back(val.toObject().value("id").toInt());
            }
        }

        if (output.size() == 0) {
            throw QString("output.size() == 0");
        }

        emit(signalGetMemberTypes(output));
    } catch (const QString& err) {
        qDebug() << "Controllers::QContestsController::GetMemberTypes(QByteArray data) : " + err;
    }
}

void Controllers::QContestController::CountMembers(QByteArray data)
{
    quint32 count = data.toUInt();
    emit (signalCountMembersLoaded(count));
}

void Controllers::QContestController::sendContestsToDatabase(const QVector<Models::Contest> &contests)
{
    for (auto val : contests) {
        bool result = sendToDatabase(val);
        resultCheck(result);
    }
}

bool Controllers::QContestController::sendToDatabase(const Models::Contest &contest)
{
    bool result = false;
    if (Database()->Contest()->Contains(
                contest.id, Models::Contest::DatabaseTable(), Models::Contest::IdColumn())) {
        result = Database()->Contest()->Edit(contest);
    } else {
        result = Database()->Contest()->Add(contest);
    }
    return result;
}

void Controllers::QContestController::clearDatabaseTable()
{
    if (!Database()->Contest()->Clear(Models::Contest::DatabaseTable())) {
        throw QString("!Database()->Contest()->Clear(Models::QContest::DatabaseTable())");
    }
}
