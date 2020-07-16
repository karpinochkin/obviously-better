#ifndef QREQUESTERS_H
#define QREQUESTERS_H

#include <QObject>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "../../models/link.h"
#include "../links.h"
#include "../../models/rating.h"
#include "../../models/membertype.h"
#include "../../models/contest.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

class QAbstractRequester : public QObject
{
    Q_OBJECT
public:
    ~QAbstractRequester() override = default;
protected:
    explicit QAbstractRequester(QObject *parent = nullptr);

signals:
    void Request(const Models::Link&,
                 QVector<quint32>& urlParameters,
                 QByteArray *data = nullptr);
};

class QContestRequester : public QAbstractRequester
{
    Q_OBJECT
public:
    explicit QContestRequester(QContestLinks *links, QObject *parent = nullptr);
    ~QContestRequester() override = default;

    void GetAll();
    void Get(quint32 id);
    void Count();
    void GetByRange(quint32 id, quint32 quantity);
    void CountMemberTypes(quint32 id);
    void GetMemberTypes(quint32 id);
    void CountMembers(quint32 id);
    void GetRandomMembers(quint32 id, quint32 quantity);

private:
    QContestLinks *links = nullptr;
    QByteArray data {};

    QJsonObject toJSON(quint32 count);
};

class QMemberRequester : public QAbstractRequester
{
    Q_OBJECT
public:
    explicit QMemberRequester(QMemberLinks *links, QObject *parent = nullptr);
    ~QMemberRequester() override = default;

    void GetAll();
    void Get(quint32 id);
private:
    QMemberLinks *links = nullptr;
};

class QRatingRequester : public QAbstractRequester
{
    Q_OBJECT
public:
    explicit QRatingRequester(QRatingLinks *links, QObject *parent = nullptr);
    ~QRatingRequester() override = default;

    void GetByContest(quint32 id);
    void Create(QByteArray *data);
    void Create(const QVector<Models::Rating> &);

private:
    QByteArray data {};
    QRatingLinks *links = nullptr;
    QJsonValue toJSON(const Models::Rating&rating);
};

class QMemberTypeRequester : public QAbstractRequester
{
    Q_OBJECT
public:
    explicit QMemberTypeRequester(QMemberTypeLinks *links, QObject *parent = nullptr);
    ~QMemberTypeRequester() override = default;

    void Count();
    void CountMembers(quint32 id);
    void GetRandomMembers(QByteArray *data);
    void GetRandomMembers(quint32 count, const QVector<quint32> &memberTypesID);

private:
    QByteArray data {};
    QMemberTypeLinks *links = nullptr;
    QJsonObject toJSON(quint32 count, const QVector<quint32> &memberTypesID);
    QJsonArray toJSON(const QVector<quint32>& myVec);
};

class QRequesters : public QObject
{
    Q_OBJECT
public:
    explicit QRequesters(QLinks* links,  QObject *parent = nullptr);
    ~QRequesters() override = default;
    QContestRequester *Contest() const;
    QMemberRequester *Member() const;
    QRatingRequester *Rating() const;
    QMemberTypeRequester *MemberType() const;

private:
    QLinks *links = nullptr;
    QContestRequester *contest = nullptr;
    QMemberRequester *member = nullptr;
    QRatingRequester *rating = nullptr;
    QMemberTypeRequester *memberType = nullptr;

    void createObjects();
    void connects();
signals:
    void Request(const Models::Link&,
                 QVector<quint32>& urlParameters,
                 QByteArray *data = nullptr);
};

#endif // QREQUESTERS_H
