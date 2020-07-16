#ifndef QMEMBERTYPESCONTROLLER_H
#define QMEMBERTYPESCONTROLLER_H

#include <QObject>
#include "qabstractcontroller.h"

namespace Controllers {

class QMemberTypeController : public QAbstractController
{
    Q_OBJECT
public:
    explicit QMemberTypeController(QDatabaseController *db, QObject *parent = nullptr);
    ~QMemberTypeController() override = default;

    void Count(QByteArray);
    void CountMembers(QByteArray);
    void GetRandomMembers(QByteArray);

private:
    void sendMembersToDatabase(const QVector<Models::Member>&);
    bool sendToDatabase(const Models::Member&member);

signals:
    void signalCount(quint32);
    void signalCountMembers(quint32);
    void signalRandomMembersLoaded(QVector<Models::Member>&);
};

}
#endif // QMEMBERTYPESCONTROLLER_H
