#ifndef MEMBERTYPE_H
#define MEMBERTYPE_H

#include "abstractmodel.h"

namespace Models {
class MemberType : public QAbstractModel
{
public:
    QString name {};

    MemberType() = default;
    ~MemberType() = default;

    static QString ModelJSON() {
        return "MemberType";
    }

    static QString DatabaseTable() {
        return "type_members";
    }

    static QString IdJSON() {
        return IdColumn();
    }

    static QString IdColumn() {
        return "id";
    }

    static QString NameJSON() {
        return NameColumn();
    }

    static QString NameColumn() {
        return "name";
    }

    static QString IdArrayJSON() {
        return "member_types_id";
    }

    static QString CountJSON() {
        return "count";
    }

    QString toString() const override {
        QString out = IdColumn() + " : " + QString::number(id) + "; " +
                NameColumn() + " : " + name + "; ";
        return out;
    }

    bool isValid() override {
        if (id <= 0
                || name == "") {
            return false;
        }
        return true;
    }

    void clear() override {
        id = 0;
        name = "";
    }


    void fromJSON(const QJsonValue &val) override {
        clear();

        id = val.toObject().value(Models::MemberType::IdJSON()).toInt();
        name = val.toObject().value(Models::MemberType::NameJSON()).toString();
    }
};
}

#endif // MEMBERTYPE_H
