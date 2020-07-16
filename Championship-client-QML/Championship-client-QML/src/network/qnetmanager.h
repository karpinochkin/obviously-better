#ifndef QNETMANAGER_H
#define QNETMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include "../config/qconfiguration.h"
#include "../models/server.h"
#include <QDebug>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include "../models/link.h"
#include "../tools/qprepareurl.h"

class QNetManager : public QObject
{
    Q_OBJECT
public:
    explicit QNetManager(Models::Server, QObject *parent = nullptr);
    ~QNetManager() override = default;

private:
    QNetworkAccessManager *manager = nullptr;
    Models::Server server;

    void createObjects();
    void connects();
    void deleteRequest(QNetworkRequest *request);

private slots:
    void slotRequest(QNetworkRequest *,
                     const QNetworkAccessManager::Operation,
                     const QByteArray *data = nullptr);
    void slotRequest(const Models::Link& link,
                     QVector<quint32>& urlParameters,
                     QByteArray *data = nullptr);
    void slotResponse(QNetworkReply *);

signals:
    void Request(QNetworkRequest *request,
                 const QNetworkAccessManager::Operation op,
                 const QByteArray *data);
    void Request(const Models::Link& link,
                 QVector<quint32>& urlParameters,
                 QByteArray *data = nullptr);
    void Response(QByteArray data, QUrl url, QNetworkAccessManager::Operation op);

    void Error(QString);
};

#endif // QNETMANAGER_H
