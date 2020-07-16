#ifndef QABSTRACTCONTROLLER_H
#define QABSTRACTCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "../../database/qdatabasecontroller.h"

namespace Controllers {

class QAbstractController : public QObject
{
public:
    ~QAbstractController() = default;
    QDatabaseController *Database() const {
        return db;
    }

protected:
    QAbstractController(QDatabaseController *db, QObject *parent = nullptr)
        : QObject(parent), db(db) {
    }

    template<typename T>
    void arrayModelsProcessing(QByteArray &data, QVector<T>& models) {
        auto json = QJsonDocument::fromJson(data);
        arrayCheck(json);

        QJsonArray modelsJSON = json.array();
        for (auto val : modelsJSON) {
            T model;

            model.fromJSON(val);
            validCheck(model);
            models.push_back(model);
        }
    }

    template<typename T>
    void modelProcessing(QByteArray &data, T &model) {
        QJsonDocument json = QJsonDocument::fromJson(data);
        model.fromJSON(json.object());
        validCheck(model);
    }

    void arrayCheck(QJsonDocument &json) const {
        if (!json.isArray()) {
            throw QString("!json.isArray()");
        }
    }

    void resultCheck(bool result) {
        if (!result) {
            throw QString("!result");
        }
    }

private:
    QDatabaseController *db = nullptr;

    template<typename T>
    void validCheck(T &model) const {
        if (!model.isValid()) {
            throw QString("!model.isValid()");
        }
    }
};

}

#endif // QABSTRACTCONTROLLER_H
