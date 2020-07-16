#ifndef TST_QREQUESTERS_H
#define TST_QREQUESTERS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../Championship-client-QML/src/network/requesters/qrequesters.h"
#include "../Championship-client-QML/src/network/links.h"
#include <memory>
#include <QSignalSpy>
#include <QTest>
#include <QDebug>
#include <QVariant>
#include <QByteArray>

using namespace testing;

template< typename T >
T unpack( const QVariant& var, const T& defVal = T() ) {
    if( var.isValid() && var.canConvert< T >() ) {
        return var.value< T >();
    }
    return defVal;
}

auto links = std::make_shared<QLinks>();
auto requesters = std::make_shared<QRequesters>(links.get());

Q_DECLARE_METATYPE(Models::Link)
Q_DECLARE_METATYPE(QByteArray*)
Q_DECLARE_METATYPE(QByteArray)

TEST(QRequester, requesterMethods) {
    qRegisterMetaType<Models::Link>("Models::Link");
    qRegisterMetaType<QVector<quint32>>("QVector<quint32>&");
    qRegisterMetaType<QByteArray*>("QByteArray*");
    QSignalSpy spy(requesters.get(), &QRequesters::Request);

    requesters->Contest()->GetAll();
    requesters->Contest()->Get(1);
    requesters->Contest()->Count();
    requesters->Contest()->GetByRange(1, 8);
    requesters->Contest()->GetMemberTypes(2);
    requesters->Contest()->CountMemberTypes(3);

    requesters->Member()->GetAll();
    requesters->Member()->Get(1);

    requesters->Rating()->GetByContest(1);
    QVector<Models::Rating> ratingModels;
    Models::Rating ratingModel;
    ratingModel.points = 222;
    ratingModel.idMember = 3;
    ratingModel.idContest = 18;
    ratingModels.push_back(ratingModel);

    ratingModel.id = 6;
    ratingModel.points = 77;
    ratingModel.idMember = 1;
    ratingModel.idContest = 3;
    ratingModels.push_back(ratingModel);
    requesters->Rating()->Create(ratingModels);

    requesters->MemberType()->Count();
    requesters->MemberType()->CountMembers(2);
    requesters->MemberType()->GetRandomMembers(3, QVector<quint32>{1, 4, 5});
//    spy.wait();
    // contest get all
    auto list = spy.takeFirst();
    Models::Link model {QNetworkAccessManager::Operation::GetOperation, "/contests"};
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{});
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);

    // contest get
    list = spy.takeFirst();
    model.URI = "/contests/[0-9]+";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{1});
    ASSERT_EQ(list.at(2).toByteArray(), nullptr);

    // contest count
    list = spy.takeFirst();
    model.URI= "/count/contests";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{});
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);

    // contest get by range
    list = spy.takeFirst();
    model.URI = "/contests/[0-9]+/quantity/[0-9]+";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    QVector<quint32> vector {1, 8};
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), vector);
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);

    // contest get member types
    list = spy.takeFirst();
    model.URI = "/contests/[0-9]+/membertypes";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{2});
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);


    // contest count member types
    list = spy.takeFirst();
    model.URI = "/contests/[0-9]+/count/membertypes";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{3});
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);


    // member get all
    list = spy.takeFirst();
    model.URI = "/members";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{});
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);

    // member get
    list = spy.takeFirst();
    model.URI = "/members/[0-9]+";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{1});
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);

    // rating get by contest
    list = spy.takeFirst();
    model.URI = "/rating/contests/[0-9]+";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{1});
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);

    // rating create
    list = spy.takeFirst();
    model.URI = "/rating";
    model.method = QNetworkAccessManager::Operation::PostOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{});
    ASSERT_FALSE(*list[2].value<QByteArray*>() == nullptr);
    ASSERT_EQ(*list[2].value<QByteArray*>(), "[\n"
                                             "    {\n"
                                             "        \"Points\": 222,\n"
                                             "        \"contest_id\": 18,\n"
                                             "        \"id\": 0,\n"
                                             "        \"member_id\": 3\n"
                                             "    },\n"
                                             "    {\n"
                                             "        \"Points\": 77,\n"
                                             "        \"contest_id\": 3,\n"
                                             "        \"id\": 6,\n"
                                             "        \"member_id\": 1\n"
                                             "    }\n"
                                             "]\n");

    // member types count
    list = spy.takeFirst();
    model.URI = "/count/membertypes";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{});
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);

    // member types count members
    list = spy.takeFirst();
    model.URI = "/membertypes/[0-9]+/count/members";
    model.method = QNetworkAccessManager::Operation::GetOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{2});
    ASSERT_EQ(list.at(2).value<QByteArray*>(), nullptr);

    // member types get random members
    list = spy.takeFirst();
    model.URI = "/membertypes/random/members";
    model.method = QNetworkAccessManager::Operation::PostOperation;
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).URI, model.URI);
    ASSERT_EQ(unpack<Models::Link>(list.at(0)).method, model.method);
    ASSERT_EQ(list.at(1).value<QVector<quint32>>(), QVector<quint32>{});
    ASSERT_FALSE(*list[2].value<QByteArray*>() == nullptr);
    ASSERT_EQ(*list[2].value<QByteArray*>(), "{\n"
                                             "    \"count\": 3,\n"
                                             "    \"member_types_id\": [\n"
                                             "        1,\n"
                                             "        4,\n"
                                             "        5\n"
                                             "    ]\n"
                                             "}\n");
}

#endif // TST_QREQUESTERS_H
