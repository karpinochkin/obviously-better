#include "qcontrollers.h"

QControllers::QControllers(QDatabaseController *db, QObject *parent)
    : QObject(parent)
{
    contests = new Controllers::QContestController(db, this);
    members = new Controllers::QMemberController(db, this);
    rating = new Controllers::QRatingController(db, this);
    memberTypes = new Controllers::QMemberTypeController(db, this);
}

Controllers::QContestController *QControllers::Contests() const
{
    return contests;
}

Controllers::QMemberController *QControllers::Members() const
{
    return members;
}

Controllers::QRatingController *QControllers::Rating() const
{
    return rating;
}

Controllers::QMemberTypeController *QControllers::MemberTypes() const
{
    return memberTypes;
}
