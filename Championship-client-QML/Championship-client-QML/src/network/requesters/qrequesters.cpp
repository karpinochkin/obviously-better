#include "qrequesters.h"

QRequesters::QRequesters(QLinks* links, QObject *parent)
    : QObject(parent),
      links(links)
{
    createObjects();
    connects();
}

void QRequesters::createObjects()
{
    contest = new QContestRequester(links->Contest(), this);
    member = new QMemberRequester(links->Member(), this);
    rating = new QRatingRequester(links->Rating(), this);
    memberType = new QMemberTypeRequester(links->MemberType(), this);
}

void QRequesters::connects()
{
    connect(contest, &QContestRequester::Request,
            this, &QRequesters::Request);
    connect(member, &QMemberRequester::Request,
            this, &QRequesters::Request);
    connect(rating, &QRatingRequester::Request,
            this, &QRequesters::Request);
    connect(memberType, &QMemberTypeRequester::Request,
            this, &QRequesters::Request);
}

QAbstractRequester::QAbstractRequester(QObject *parent)
    : QObject(parent)
{

}

QContestRequester::QContestRequester(QContestLinks *links, QObject *parent)
    : QAbstractRequester(parent),
      links(links)
{

}

void QContestRequester::GetAll()
{
    QVector<quint32> parameters {};
    emit (this->Request(links->GetAll(), parameters));
}

void QContestRequester::Get(quint32 id)
{
    QVector<quint32> parameters {id};
    emit (this->Request(links->Get(), parameters));
}

void QContestRequester::Count()
{
    QVector<quint32> parameters {};
    emit (this->Request(links->Count(), parameters));
}

void QContestRequester::GetByRange(quint32 id, quint32 quantity)
{
    QVector<quint32> parameters {id, quantity};
    emit (this->Request(links->GetByRange(), parameters));
}

void QContestRequester::CountMemberTypes(quint32 id)
{
    QVector<quint32> parameters {id};
    emit (this->Request(links->CountMemberTypes(), parameters));
}

void QContestRequester::GetMemberTypes(quint32 id)
{
    QVector<quint32> parameters {id};
    emit (this->Request(links->GetMemberTypes(), parameters));
}

void QContestRequester::CountMembers(quint32 id)
{
    QVector<quint32> parameters {id};
    emit (this->Request(links->CountMembers(), parameters));
}

void QContestRequester::GetRandomMembers(quint32 id, quint32 quantity)
{
    QVector<quint32> parameters {id};

    auto json = toJSON(quantity);

    QJsonDocument dc;
    dc.setObject(json);
    data = dc.toJson();

    emit (this->Request(links->GetRandomMembers(), parameters, &data));
}

QJsonObject QContestRequester::toJSON(quint32 count)
{
    QJsonObject output;
    output.insert(Models::Contest::CountJSON(), QJsonValue::fromVariant(count));
    return output;
}

QContestRequester *QRequesters::Contest() const
{
    return contest;
}

QMemberRequester *QRequesters::Member() const
{
    return member;
}

QRatingRequester *QRequesters::Rating() const
{
    return rating;
}

QMemberTypeRequester *QRequesters::MemberType() const
{
    return memberType;
}

QMemberRequester::QMemberRequester(QMemberLinks *links, QObject *parent)
    : QAbstractRequester(parent),
      links(links)
{

}

void QMemberRequester::GetAll()
{
    QVector<quint32> parameters {};
    emit (Request(links->GetAll(), parameters));
}

void QMemberRequester::Get(quint32 id)
{
    QVector<quint32> parameters {id};
    emit (Request(links->Get(), parameters));
}

QRatingRequester::QRatingRequester(QRatingLinks *links, QObject *parent)
    : QAbstractRequester(parent),
      links(links)
{

}

void QRatingRequester::GetByContest(quint32 id)
{
    QVector<quint32> parameters {id};
    emit (Request(links->GetByContest(), parameters));
}

void QRatingRequester::Create(QByteArray *data)
{
    QVector<quint32> parameters {};
    emit (Request(links->Create(), parameters, data));
}

void QRatingRequester::Create(const QVector<Models::Rating> &rating)
{
    QVector<quint32> parameters {};

    QJsonArray ratingArray;
    data.clear();
    for (auto val : rating) {
        ratingArray.push_back(toJSON(val));
    }

    QJsonDocument dc;
    dc.setArray(ratingArray);
    data = dc.toJson();
    emit (Request(links->Create(), parameters, &data));
}

QJsonValue QRatingRequester::toJSON(const Models::Rating &rating)
{
    QJsonObject output;
    output.insert(Models::Rating::IdJSON(), QJsonValue::fromVariant(rating.id));
    output.insert(Models::Rating::PointsJSON(), QJsonValue::fromVariant(rating.points));
    output.insert(Models::Rating::IdContestJSON(), QJsonValue::fromVariant(rating.idContest));
    output.insert(Models::Rating::IdMemberJSON(), QJsonValue::fromVariant(rating.idMember));
    return output;
}

QMemberTypeRequester::QMemberTypeRequester(QMemberTypeLinks *links, QObject *parent)
    : QAbstractRequester(parent),
      links(links)
{

}

void QMemberTypeRequester::Count()
{
    QVector<quint32> parameters {};
    emit (Request(links->Count(), parameters));
}

void QMemberTypeRequester::CountMembers(quint32 id)
{
    QVector<quint32> parameters {id};
    emit (Request(links->CountMembers(), parameters));
}

void QMemberTypeRequester::GetRandomMembers(QByteArray *data)
{
    QVector<quint32> parameters {};
    emit (Request(links->GetRandomMembers(), parameters, data));
}

void QMemberTypeRequester::GetRandomMembers(quint32 count, const QVector<quint32> &memberTypesID)
{
    QVector<quint32> parameters {};

    auto json = toJSON(count, memberTypesID);

    QJsonDocument dc;
    dc.setObject(json);
    data = dc.toJson();
    emit (Request(links->GetRandomMembers(), parameters, &data));
}

QJsonObject QMemberTypeRequester::toJSON(quint32 count, const QVector<quint32> &memberTypesID)
{
    QJsonObject output;
    output.insert(Models::MemberType::CountJSON(), QJsonValue::fromVariant(count));
    output.insert(Models::MemberType::IdArrayJSON(), toJSON(memberTypesID));
    return output;
}

QJsonArray QMemberTypeRequester::toJSON(const QVector<quint32> &myVec)
{
    QJsonArray result;
    for (auto val : myVec) {
        result.push_back(QJsonValue::fromVariant(val));
    }
    return result;
}
