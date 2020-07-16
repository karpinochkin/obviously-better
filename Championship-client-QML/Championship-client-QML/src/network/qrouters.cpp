#include "qrouters.h"

QRouters::QRouters(QObject *parent) : QObject(parent)
{
    createObjects();
    fillRouters();
    connects();
}

QRequesters *QRouters::Requesters() const
{
    return requesters;
}

QDatabaseController *QRouters::Database() const
{
    return database;
}

QControllers *QRouters::Controllers() const
{
    return controllers;
}

void QRouters::createObjects()
{
    netManager = new QNetManager(QConfiguration::GetConfig()->GetServer(), this);
    database = new QDatabaseController(QConfiguration::GetConfig()->GetDatabaseName(), this);
    controllers = new QControllers(database, this);
    links = new QLinks(this);
    requesters = new QRequesters(links, this);
}

void QRouters::connects()
{
    connect(netManager, &QNetManager::Response,
            this, [=](QByteArray data, QUrl url, QNetworkAccessManager::Operation op){
        selectController(data, url, op);
    });
    connect(requesters, &QRequesters::Request,
            this, [=](const Models::Link &link, QVector<quint32> &urlParameters, QByteArray *data) {
        netManager->Request(link, urlParameters, data);
    });
    connect(netManager, &QNetManager::Error,
            this, &QRouters::ErrorResponse);
}

void QRouters::fillRouters()
{
    try {
        fillContestRouters();
        fillMemberRouters();
        fillRatingRouters();
        fillMemberTypesRouters();
    } catch (const QException &err) {
        qDebug() << err.what();
    }
}

void QRouters::fillContestRouters()
{
    routers.insert(links->Contest()->GetAll(),
                   Models::Router {
                       links->Contest()->GetAll(),
                       [=](QByteArray data) {
                           controllers->Contests()->GetAll(data);
                       }
                   });

    routers.insert(links->Contest()->Get(),
                   Models::Router {
                       links->Contest()->Get(),
                       [=](QByteArray data) {
                           controllers->Contests()->Get(data);
                       }
                   });

    routers.insert(links->Contest()->Count(),
                   Models::Router {
                       links->Contest()->Count(),
                       [=](QByteArray data) {
                           controllers->Contests()->Count(data);
                       }
                   });

    routers.insert(links->Contest()->GetByRange(),
                   Models::Router {
                       links->Contest()->GetByRange(),
                       [=](QByteArray data) {
                           controllers->Contests()->GetByRange(data);
                       }
                   });

    routers.insert(links->Contest()->CountMemberTypes(),
                   Models::Router {
                       links->Contest()->CountMemberTypes(),
                       [=](QByteArray data) {
                           controllers->Contests()->CountMemberTypes(data);
                       }
                   });

    routers.insert(links->Contest()->GetMemberTypes(),
                   Models::Router {
                       links->Contest()->GetMemberTypes(),
                       [=](QByteArray data) {
                           controllers->Contests()->GetMemberTypes(data);
                       }
                   });

    routers.insert(links->Contest()->CountMembers(),
                   Models::Router {
                       links->Contest()->CountMembers(),
                       [=](QByteArray data) {
                           controllers->Contests()->CountMembers(data);
                       }
                   });
    routers.insert(links->Contest()->GetRandomMembers(),
                   Models::Router {
                       links->Contest()->GetRandomMembers(),
                       [=](QByteArray data) {
                           controllers->MemberTypes()->GetRandomMembers(data);
                       }
                   });
}

void QRouters::fillMemberRouters()
{
    routers.insert(links->Member()->GetAll(),
                   Models::Router {
                       links->Member()->GetAll(),
                       [=](QByteArray data) {
                           controllers->Members()->GetAll(data);
                       }
                   });

    routers.insert(links->Member()->Get(),
                   Models::Router {
                       links->Member()->Get(),
                       [=](QByteArray data) {
                           controllers->Members()->Get(data);
                       }
                   });
}

void QRouters::fillRatingRouters()
{
    routers.insert(links->Rating()->GetByContest(),
                   Models::Router {
                       links->Rating()->GetByContest(),
                       [=](QByteArray data) {
                           controllers->Rating()->GetByContest(data);
                       }
                   });

    routers.insert(links->Rating()->Create(),
                   Models::Router {
                       links->Rating()->Create(),
                       [=](QByteArray data) {
                           controllers->Rating()->Create(data);
                       }
                   });
}

void QRouters::fillMemberTypesRouters()
{
    routers.insert(links->MemberType()->Count(),
                   Models::Router {
                       links->MemberType()->Count(),
                       [=](QByteArray data) {
                           controllers->MemberTypes()->Count(data);
                       }
                   });

    routers.insert(links->MemberType()->CountMembers(),
                   Models::Router {
                       links->MemberType()->CountMembers(),
                       [=](QByteArray data) {
                           controllers->MemberTypes()->CountMembers(data);
                       }
                   });

    routers.insert(links->MemberType()->GetRandomMembers(),
                   Models::Router {
                       links->MemberType()->GetRandomMembers(),
                       [=](QByteArray data) {
                           controllers->MemberTypes()->GetRandomMembers(data);
                       }
                   });
}

void QRouters::selectController(QByteArray data, QUrl url, QNetworkAccessManager::Operation op)
{
    QString key = QPrepareURL::PrepareResponseUrl(url.toString(), QConfiguration::GetConfig()->GetServer());
    try {
        auto router = routers.find(Models::Link {op, key});
        router.value().handler(data);
    } catch (...) {
        qDebug() << "select controller error";
    }
}
