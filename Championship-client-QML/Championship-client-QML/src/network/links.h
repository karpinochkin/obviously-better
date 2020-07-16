#ifndef QLINKS_H
#define QLINKS_H

#include <QObject>
#include "../models/link.h"

class QAbstractLinks : public QObject
{
public:
    virtual ~QAbstractLinks() override = default;

protected:
    QAbstractLinks(QObject *parent = nullptr) : QObject(parent) {

    }
    virtual Models::Link GetAll() const = 0;
    virtual Models::Link Get() const = 0;
};

class QContestLinks : public QAbstractLinks
{
public:
    QContestLinks(QObject *parent = nullptr) : QAbstractLinks(parent) {

    }
    ~QContestLinks() override = default;

    Models::Link GetAll() const override {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/contests"};
    }

    Models::Link Get() const override {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/contests/[0-9]+"};
    }

    Models::Link Count() const {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/count/contests"};
    }

    Models::Link GetByRange() const {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/contests/[0-9]+/quantity/[0-9]+"};
    }

    Models::Link CountMemberTypes() const {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/contests/[0-9]+/count/membertypes"};
    }

    Models::Link GetMemberTypes() const {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/contests/[0-9]+/membertypes"};
    }

    Models::Link CountMembers() const {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/contests/[0-9]+/members"};
    }

    Models::Link GetRandomMembers() const {
        return Models::Link{QNetworkAccessManager::Operation::PostOperation, "/contests/[0-9]+/random/members"};
    }
};

class QMemberLinks : public QAbstractLinks
{
public:
    QMemberLinks(QObject *parent = nullptr) : QAbstractLinks(parent) {

    }
    ~QMemberLinks() override = default;

    Models::Link GetAll() const override {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/members"};
    }

    Models::Link Get() const override {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/members/[0-9]+"};
    }

    Models::Link GetImage() const {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/members/[0-9]+/image"};
    }
};

class QRatingLinks : public QAbstractLinks
{
public:
    QRatingLinks(QObject *parent = nullptr) : QAbstractLinks(parent) {

    }
    ~QRatingLinks() override = default;

    Models::Link GetAll() const override {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/rating"};
    }

    Models::Link Get() const override {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/rating/[0-9]+"};
    }

    Models::Link GetByContest() const {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/rating/contests/[0-9]+"};
    }

    Models::Link Create() const {
        return Models::Link{QNetworkAccessManager::Operation::PostOperation, "/rating"};
    }
};

class QMemberTypeLinks : public QAbstractLinks
{
public:
    QMemberTypeLinks(QObject *parent = nullptr) : QAbstractLinks(parent) {

    }
    ~QMemberTypeLinks() override = default;

    Models::Link GetAll() const override {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/membertypes"};
    }

    Models::Link Count() const {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/count/membertypes"};
    }

    Models::Link Get() const override {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/membertypes/[0-9]+"};
    }

    Models::Link CountMembers() const {
        return Models::Link{QNetworkAccessManager::Operation::GetOperation, "/membertypes/[0-9]+/count/members"};
    }

    Models::Link GetRandomMembers() const {
        return Models::Link{QNetworkAccessManager::Operation::PostOperation, "/membertypes/random/members"};
    }
};

class QLinks : public QObject
{
public:
    QLinks(QObject *parent = nullptr) : QObject(parent) {
        contest = new QContestLinks(this);
        member = new QMemberLinks(this);
        rating = new QRatingLinks(this);
        memberType = new QMemberTypeLinks(this);
    }

    QContestLinks *Contest() const {
        return contest;
    }

    QMemberLinks *Member() const {
        return member;
    }

    QRatingLinks *Rating() const {
        return rating;
    }

    QMemberTypeLinks *MemberType() const {
        return memberType;
    }

private:
    QContestLinks *contest = nullptr;
    QMemberLinks *member = nullptr;
    QRatingLinks *rating = nullptr;
    QMemberTypeLinks *memberType = nullptr;
};

#endif // QLINKS_H
