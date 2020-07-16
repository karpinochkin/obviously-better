#include "qmemberscontroller.h"

Controllers::QMemberController::QMemberController(QDatabaseController *db, QObject *parent)
    : QAbstractController(db, parent)
{

}

void Controllers::QMemberController::Get(QByteArray data)
{
    Models::Member member {};
    try {
        modelProcessing(data, member);
        bool result = sendToDatabase(member);
        resultCheck(result);

        emit (signalGet(member));
    }
    catch(const QString& err) {
        qDebug() << "error : Controllers::QMembersController::Get(QByteArray data) : " + err;
    }
}

void Controllers::QMemberController::GetAll(QByteArray data)
{
    try {
        QVector<Models::Member> members {};
        arrayModelsProcessing(data, members);
        clearDatabaseTable();
        sendMembersToDatabase(members);
        emit (signalGetAll(members));
    }
    catch(const QString& err) {
        qDebug() << "Controllers::QMembersController::GetAll(QByteArray data) : " + err;
    }
    catch (...) {
        qDebug() << "Controllers::QMembersController::GetAll(QByteArray data)";
    }
}

void Controllers::QMemberController::sendMembersToDatabase(const QVector<Models::Member> &members)
{
    for (auto val : members) {
        bool result = sendToDatabase(val);
        resultCheck(result);
    }
}

bool Controllers::QMemberController::sendToDatabase(const Models::Member &member)
{
    bool result = false;
    if (Database()->Member()->Contains(
                member.id, Models::Member::DatabaseTable(), Models::Member::IdColumn())) {
        result = Database()->Member()->Edit(member);
    } else {
        result = Database()->Member()->Add(member);
    }
    return result;
}

void Controllers::QMemberController::clearDatabaseTable()
{
    if (!Database()->Member()->Clear(Models::Member::DatabaseTable())) {
        throw QString("!Database()->Member()->Clear(Models::QMember::DatabaseTable())");
    }
}
