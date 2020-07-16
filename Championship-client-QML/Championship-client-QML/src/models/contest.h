#ifndef CONTEST_H
#define CONTEST_H

#include "abstractmodel.h"
#include <QJsonDocument>
#include <QVector>

namespace Models {
class Contest : public QAbstractModel
{
public:
    QString name {};
    QString description {};
    quint64 countPlay {};
    QByteArray image {};
    QVector<quint32> memberTypesID {};

    explicit Contest() = default;
    ~Contest() = default;

    static QString ModelJSON() {
        return "Contest";
    }

    static QString MemberTypesModelJSON() {
        return "MemberType";
    }

    static QString IdJSON() {
        return IdColumn();
    }

    static QString NameJSON() {
        return NameColumn();
    }

    static QString DescriptionJSON() {
        return DescriptionColumn();
    }

    static QString CountPlayJSON() {
        return CountPlayColumn();
    }

    static QString CountJSON() {
        return "count";
    }

    static QString ImageJSON() {
        return ImageColumn();
    }

    static QString DatabaseTable() {
        return "contests";
    }

    static QString IdColumn() {
        return "id";
    }

    static QString NameColumn() {
        return "name";
    }

    static QString DescriptionColumn() {
        return "description";
    }

    static QString CountPlayColumn() {
        return "count_play";
    }

    static QString ImageColumn() {
        return "image";
    }

    QString toString() const override {
        QString out = IdColumn() + " : " + QString::number(id) + "; " +
                NameColumn() + " : " + name + "; " +
                DescriptionColumn() + " : " + description + "; " +
                CountPlayColumn() + " : " + QString::number(countPlay) + "; " +
                ImageColumn() + " : " + image + "; " +
                MemberTypesModelJSON() + " : ";
        for (auto val : memberTypesID) {
            out += QString::number(val) + ",";
        }
        out.replace(out.size() - 1, 1, ";");
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
        countPlay = 0;
        image = "";
        memberTypesID.clear();
    }

    void fromJSON(const QJsonValue &val) override {
        clear();

        id = val.toObject().value(Models::Contest::IdJSON()).toInt();
        name = val.toObject().value(Models::Contest::NameJSON()).toString();
        description = val.toObject().value(Models::Contest::DescriptionJSON()).toString();
        countPlay = val.toObject().value(Models::Contest::CountPlayJSON()).toInt();
        image = QByteArray::fromBase64(val.toObject().value(Models::Contest::ImageJSON()).toVariant().toByteArray());

        if (val.toObject().contains(Models::Contest::MemberTypesModelJSON())
                && val.toObject().value(Models::Contest::MemberTypesModelJSON()).isArray()) {
            QJsonArray itemArray = val.toObject().value(Models::Contest::MemberTypesModelJSON()).toArray();
            for (int i = 0; i < itemArray.size(); ++i) {
                memberTypesID.push_back(itemArray[i].toObject().value("id").toInt());
            }
        }
    }
};
}

#endif // CONTEST_H
