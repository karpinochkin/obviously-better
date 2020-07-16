#include "qprepareurl.h"

QString QPrepareURL::ServerHttpBeginUrl(const Models::Server &server)
{
    if (server.port == "") {
        return "http://" + server.host;
    }
    return "http://" + server.host + ":" + server.port;
}

QString QPrepareURL::ServerHttpsBeginUrl(const Models::Server &server)
{
    if (server.port == "") {
        return "https://" + server.host;
    }
    return "https://" + server.host + ":" + server.port;
}

QString QPrepareURL::PrepareResponseUrl(QString url, const Models::Server &server)
{
    QRegExp regexpHTTP(ServerHttpBeginUrl(server));
    url = url.replace(regexpHTTP, "");

    QRegExp regexpHTTPS(ServerHttpsBeginUrl(server));
    url = url.replace(regexpHTTPS, "");

    return PrepareResponseUrl(url);
}

QString QPrepareURL::PrepareResponseUrl(QString url)
{
    QRegExp regexp("[0-9]+");
    return url.replace(regexp, "[0-9]+");
}

QString QPrepareURL::PrepareRequestUrl(QString url, const QVector<quint32>& vectorID)
{
    QString subStr = "[0-9]+";

    for (auto val : vectorID) {
        url = url.replace(url.indexOf(
                               subStr),
                           subStr.size(),
                        QString::number(val)
                    );
    }
    return url;
}

QString QPrepareURL::PrepareHttpRequestUrl(QString url,  const QVector<quint32> &idVector, const Models::Server &server)
{
    url = ServerHttpBeginUrl(server) + url;
    return PrepareRequestUrl(url, idVector);
}

QString QPrepareURL::PrepareHttpsRequestUrl(QString url, const QVector<quint32> &idVector, const Models::Server &server)
{
    url = ServerHttpsBeginUrl(server) + url;
    return PrepareRequestUrl(url, idVector);
}

