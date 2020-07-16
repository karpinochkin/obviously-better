#ifndef ABSTRACTMODEL_H
#define ABSTRACTMODEL_H

#include <QString>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>

namespace Models {
class QAbstractModel
{
public:
    virtual ~QAbstractModel() = default;
    quint32 id {};

protected:
    QAbstractModel() = default;
    virtual QString toString() const {
        return "id : " + QString::number(id) + ";";
    }

    virtual bool isValid() {
        if (id <= 0) {
            return false;
        }
        return true;
    }

    virtual void clear() {
        id = 0;
    }

    virtual void fromJSON(const QJsonValue &val) {
        Q_UNUSED(val)
    }

};
}

#endif // ABSTRACTMODEL_H
