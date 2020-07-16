#include "qmembertypescontroller.h"

Controllers::QMemberTypeController::QMemberTypeController(QDatabaseController *db, QObject *parent)
    : QAbstractController(db, parent)
{

}

void Controllers::QMemberTypeController::Count(QByteArray data)
{
    quint32 count = data.toUInt();
    emit (signalCount(count));
}

void Controllers::QMemberTypeController::CountMembers(QByteArray data)
{
    quint32 count = data.toUInt();
    emit (signalCountMembers(count));
}

void Controllers::QMemberTypeController::GetRandomMembers(QByteArray data)
{
    try {
        QVector<Models::Member> members {};
        arrayModelsProcessing(data, members);
        sendMembersToDatabase(members);

        emit (signalRandomMembersLoaded(members));
    }
    catch(const QString& err) {
        qDebug() << "Controllers::QMemberTypesController::GetRandomMembers(QByteArray data) : " + err;
    }
}

void Controllers::QMemberTypeController::sendMembersToDatabase(const QVector<Models::Member> &members)
{
    for (auto val : members) {
        bool result = sendToDatabase(val);
        resultCheck(result);
    }
}

bool Controllers::QMemberTypeController::sendToDatabase(const Models::Member &member)
{
    bool result = false;
    if (Database()->Member()->Contains(member.id, Models::Member::DatabaseTable(), Models::Member::IdColumn())) {
        result = Database()->Member()->EditWithoutImage(member);
    } else {
        result = Database()->Member()->Add(member);
    }
    return result;
}
