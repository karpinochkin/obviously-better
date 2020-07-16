#ifndef RATING_H
#define RATING_H

#include "abstractmodel.h"

namespace Models {
class Rating : public QAbstractModel
{
public:
    quint32 idContest {};
    quint32 idMember {};
    double points {};

    explicit Rating() = default;
    ~Rating() = default;

    static QString DatabaseTable() {
        return "rating";
    }

    static QString ModelJSON() {
        return "Rating";
    }

    static QString IdJSON() {
        return IdColumn();
    }

    static QString IdColumn() {
        return "id";
    }

    static QString PointsJSON() {
        return "Points";
    }

    static QString PointsColumn() {
        return "points";
    }

    static QString IdContestJSON() {
        return IdContestColumn();
    }

    static QString IdContestColumn() {
        return "contest_id";
    }

    static QString IdMemberJSON() {
        return IdMemberColumn();
    }

    static QString IdMemberColumn() {
        return "member_id";
    }

    QString toString() const override {
        QString out = IdColumn() + " : " + QString::number(id) + ";"
                + PointsColumn() + " : " + QString::number(points) + ";"
                + IdContestColumn() + " : " + QString::number(idContest) + ";"
                + IdMemberColumn() + " : " + QString::number(idMember) + ";";
        return out;
    }

    bool isValid() override {
        if (points <= 0.0
                || idContest <= 0
                || idMember <= 0) {
            return false;
        }
        return true;
    }

    void clear() override {
        id = 0;
        idContest = 0;
        idMember = 0;
        points = 0.0;
    }

    void fromJSON(const QJsonValue &val) override {
        clear();

        id = val.toObject().value(Models::Rating::IdJSON()).toInt();
        points = val.toObject().value(Models::Rating::PointsJSON()).toDouble();
        idContest = val.toObject().value(Models::Rating::IdContestJSON()).toInt();
        idMember = val.toObject().value(Models::Rating::IdMemberJSON()).toInt();
    }

//    bool operator < (const Rating& rate) const
//        {
//            return (points < rate.points);
//        }

};
}

#endif // RATING_H
