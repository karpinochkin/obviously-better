#ifndef QCONTROLLERS_H
#define QCONTROLLERS_H

#include <QObject>
#include <QDebug>
#include "qcontestscontroller.h"
#include "qmemberscontroller.h"
#include "qratingcontroller.h"
#include "qmembertypescontroller.h"

class QControllers : public QObject
{
    Q_OBJECT
public:
//    explicit QControllers(const QString &databaseName, QObject *parent = nullptr);
    explicit QControllers(QDatabaseController *db, QObject *parent = nullptr);
    ~QControllers() override = default;

    Controllers::QContestController *Contests() const;
    Controllers::QMemberController *Members() const;
    Controllers::QRatingController *Rating() const;
    Controllers::QMemberTypeController *MemberTypes() const;
//    QDatabaseController *Database() const;

private:
//    QDatabaseController *db = nullptr;
    Controllers::QContestController *contests = nullptr;
    Controllers::QMemberController *members = nullptr;
    Controllers::QRatingController *rating = nullptr;
    Controllers::QMemberTypeController *memberTypes = nullptr;
};

#endif // QCONTROLLERS_H
