#ifndef QPREPAREURL_H
#define QPREPAREURL_H

#include <QRegExp>
#include <QVector>
#include "../models/server.h"

class QPrepareURL
{
public:
    QPrepareURL() = delete;
    ~QPrepareURL() = default;

    static QString ServerHttpBeginUrl(const Models::Server &server);
    static QString ServerHttpsBeginUrl(const Models::Server &server);
    static QString PrepareResponseUrl(QString url, const Models::Server &server);
    static QString PrepareResponseUrl(QString url);
    static QString PrepareRequestUrl(QString url, const QVector<quint32> &idVector);
    static QString PrepareHttpRequestUrl(QString url, const QVector<quint32> &idVector, const Models::Server &server);
    static QString PrepareHttpsRequestUrl(QString url, const QVector<quint32> &idVector, const Models::Server &server);
};

#endif // QPREPAREURL_H
