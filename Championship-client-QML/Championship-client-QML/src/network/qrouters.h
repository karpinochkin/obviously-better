#ifndef QROUTER_H
#define QROUTER_H

#include <QObject>
#include "qnetmanager.h"
#include "controllers/qcontrollers.h"
#include <QException>
#include "../models/router.h"
#include "links.h"
#include "../tools/qprepareurl.h"
#include "requesters/qrequesters.h"

class QRouters : public QObject
{
    Q_OBJECT
public:
    explicit QRouters(QObject *parent = nullptr);
    ~QRouters() override = default;

    QRequesters *Requesters() const;
    QDatabaseController *Database() const;
    QControllers *Controllers() const;

private:
    QNetManager *netManager = nullptr;
    QControllers *controllers = nullptr;
    QLinks *links = nullptr;
    QRequesters *requesters = nullptr;
    QDatabaseController *database = nullptr;

    QMap<Models::Link, Models::Router> routers;

    void createObjects();
    void connects();

    void fillRouters();
    void fillContestRouters();
    void fillMemberRouters();
    void fillRatingRouters();
    void fillMemberTypesRouters();

    void selectController(QByteArray data, QUrl url, QNetworkAccessManager::Operation op);

signals:
    void ErrorResponse(QString);
};

#endif // QROUTER_H
