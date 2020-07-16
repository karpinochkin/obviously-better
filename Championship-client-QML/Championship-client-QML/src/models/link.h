#ifndef LINK_H
#define LINK_H

#include <QString>
#include <QNetworkAccessManager>

namespace Models {
struct Link {
    QNetworkAccessManager::Operation method;
    QString URI;

    bool operator<(const Link & link) const {
        return (method == link.method) ? (URI > link.URI) : (method > link.method);
    }
};
}

#endif // LINK_H
