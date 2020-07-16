#ifndef MEMBER_H
#define MEMBER_H

#include "abstractmodel.h"

namespace Models {
class Member : public QAbstractModel
{
public:
    QString name {};
    QString description {};
    QByteArray image {};

    Member() = default;
    ~Member() = default;

    static QString ModelJSON() {
        return "Member";
    }

    static QString DatabaseTable() {
        return "members";
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

    static QString DescriptionJSON() {
        return DescriptionColumn();
    }

    static QString DescriptionColumn() {
        return "description";
    }

    static QString ImageJSON() {
        return ImageColumn();
    }

    static QString ImageColumn() {
        return "image";
    }

    QString toString() const override {
        QString out = IdColumn() + " : " + QString::number(id) + "; " +
                NameColumn() + " : " + name + "; " +
                DescriptionColumn() + " : " + description + "; " +
                ImageColumn() + " : " + image + "; ";
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
        description = "";
        image = "";
    }

    void fromJSON(const QJsonValue &val) override {
        clear();

        fromJsonWithoutImage(val);
        image = QByteArray::fromBase64(val.toObject().value(Models::Member::ImageJSON()).toVariant().toByteArray());
    }

    void fromJsonWithoutImage (const QJsonValue &val) {
        clear();

        id = val.toObject().value(IdJSON()).toInt();
        name = val.toObject().value(Models::Member::NameJSON()).toString();
        description = val.toObject().value(Models::Member::DescriptionJSON()).toString();
    }

};
}
#endif // MEMBER_H
