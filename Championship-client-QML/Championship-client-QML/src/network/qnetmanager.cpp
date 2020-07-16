#include "qnetmanager.h"

QNetManager::QNetManager(Models::Server server, QObject *parent)
    : QObject(parent),
      server(server)
{
    createObjects();
    connects();
}

void QNetManager::createObjects()
{
    manager = new QNetworkAccessManager(this);
}

void QNetManager::connects()
{
    connect(this, static_cast<void(QNetManager::*)
            (QNetworkRequest*, const QNetworkAccessManager::Operation, const QByteArray *)>(&QNetManager::Request),
            this, static_cast<void(QNetManager::*)
            (QNetworkRequest*, const QNetworkAccessManager::Operation, const QByteArray *)>(&QNetManager::slotRequest));
    connect(this, static_cast<void(QNetManager::*)
            (const Models::Link &, QVector<quint32> &, QByteArray *)>(&QNetManager::Request),
            this, static_cast<void(QNetManager::*)
            (const Models::Link &, QVector<quint32> &, QByteArray *)>(&QNetManager::slotRequest));
    connect(manager, &QNetworkAccessManager::finished,
            this, &QNetManager::slotResponse);
}

void QNetManager::slotRequest(QNetworkRequest *request, const QNetworkAccessManager::Operation op, const QByteArray *data)
{
    try {
        if (op == QNetworkAccessManager::Operation::GetOperation) {
            manager->get(*request);
            return;
        }
        if (op == QNetworkAccessManager::Operation::PostOperation) {
            request->setRawHeader("Content-Type", "application/json");
            manager->post(*request, *data);
            return;
        }
        if (op == QNetworkAccessManager::Operation::PutOperation) {
            manager->put(*request, *data);
            return;
        }
        if (op == QNetworkAccessManager::Operation::DeleteOperation) {
            manager->deleteResource(*request);
            return;
        }
        if (op == QNetworkAccessManager::Operation::HeadOperation) {
            manager->head(*request);
            return;
        }
    } catch (...) {
        qDebug() << "QNetManager : request error";
    }

    delete request;
}

void QNetManager::slotRequest(const Models::Link &link, QVector<quint32> &urlParameters, QByteArray *data)
{
    QNetworkRequest *req = new QNetworkRequest(QPrepareURL::PrepareHttpRequestUrl(link.URI, urlParameters, server));
    this->slotRequest(req, link.method, data);
}

void QNetManager::slotResponse(QNetworkReply *reply)
{
    try {
        if (reply->error() != QNetworkReply::NoError) {
            throw reply->error();
        }
        emit (Response(reply->readAll(), reply->url(), reply->operation()));
    } catch (QNetworkReply::NetworkError) {
        qDebug() << "QNetManager : response error #"
                 << reply->error() << "(" << reply->errorString() << ")";
        emit (Error(reply->errorString()));
    }
    reply->deleteLater();
}
