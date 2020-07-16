#ifndef QCONTESTSCONTROLLER_H
#define QCONTESTSCONTROLLER_H

#include <QObject>
#include "qabstractcontroller.h"
#include "../../models/contest.h"

namespace Controllers {

class QContestController : public QAbstractController
{
    Q_OBJECT
public:
    explicit QContestController(QDatabaseController *db, QObject *parent = nullptr);
    ~QContestController() override = default;

    void Get(QByteArray);
    void GetAll(QByteArray);
    void Count(QByteArray);
    void GetByRange(QByteArray);
    void CountMemberTypes(QByteArray);
    void GetMemberTypes(QByteArray);
    void CountMembers(QByteArray);

private:
    void sendContestsToDatabase(const QVector<Models::Contest>&);
    bool sendToDatabase(const Models::Contest&);
    void clearDatabaseTable();

signals:
    void signalGet(const Models::Contest &);
    void signalGetAll(const QVector<Models::Contest> &);
    void signalCount(quint32);
    void signalGetByRangeLoaded(const QVector<Models::Contest> &);
    void signalCountMemberTypes(quint32);
    void signalGetMemberTypes(QVector<quint32>& idMemberTypes);
    void signalCountMembersLoaded(quint32);
};

}
#endif // QCONTESTSCONTROLLER_H
