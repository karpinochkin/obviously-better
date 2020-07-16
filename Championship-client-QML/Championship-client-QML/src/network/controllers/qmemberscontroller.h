#ifndef QMEMBERSCONTROLLER_H
#define QMEMBERSCONTROLLER_H

#include "qabstractcontroller.h"

namespace Controllers {

class QMemberController : public QAbstractController
{
    Q_OBJECT
public:
    explicit QMemberController(QDatabaseController *db, QObject *parent = nullptr);
    ~QMemberController() override = default;

    void Get(QByteArray data);
    void GetAll(QByteArray data);

private:
    void sendMembersToDatabase(const QVector<Models::Member>&);
    bool sendToDatabase(const Models::Member&);
    void clearDatabaseTable();

signals:
    void signalGet(const Models::Member&);
    void signalGetAll(const QVector<Models::Member> &);
};

}

#endif // QMEMBERSCONTROLLER_H
