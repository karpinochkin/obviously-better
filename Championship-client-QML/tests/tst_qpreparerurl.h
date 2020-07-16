#ifndef TST_QPREPARERURL_H
#define TST_QPREPARERURL_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../Championship-client-QML/src/tools/qprepareurl.h"

using namespace testing;

TEST(QPrepareURL, ServerHttpBeginUrl)
{
    Models::Server server {"127.0.0.1", "7777"};
    auto result = QPrepareURL::ServerHttpBeginUrl(server);
    ASSERT_EQ(result, "http://127.0.0.1:7777");
}

TEST(QPrepareURL, ServerHttpsBeginUrl)
{
    Models::Server server {"127.0.0.1", "7777"};
    auto result = QPrepareURL::ServerHttpsBeginUrl(server);
    ASSERT_EQ(result, "https://127.0.0.1:7777");
}

TEST(QPrepareURL, PrepareResponseUrlServer)
{
    Models::Server server {"127.0.0.1", "7777"};
    QString url;

    url = "http://127.0.0.1:7777/contests/3/count/membertypes";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "/contests/[0-9]+/count/membertypes");

    url = "http://127.0.0.1:7777/contests/8/quantity/2";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "/contests/[0-9]+/quantity/[0-9]+");

    url = "http://127.0.0.1:7777/contests";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "/contests");

    url = "http://127.0.0.1:7777/contests/3/count/membertypes";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "/contests/[0-9]+/count/membertypes");

    url = "https://127.0.0.1:7777/contests/8/quantity/2";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "/contests/[0-9]+/quantity/[0-9]+");

    url = "https://127.0.0.1:7777/contests";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "/contests");

    url = "http://127.0.0.1:7777";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "");

    url = "https://127.0.0.1:7777";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "");

    url = "";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "");

    url = "hello.com:123";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "hello.com:[0-9]+");

    url = "hello.com/table/1";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url, server),
              "hello.com/table/[0-9]+");
}

TEST(QPrepareURL, PrepareResponseUrl)
{
    QString url;

    url = "http://127.0.0.1:7777/contests/3/count/membertypes";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url),
              "http://[0-9]+.[0-9]+.[0-9]+.[0-9]+:[0-9]+/contests/[0-9]+/count/membertypes");

    url = "/contests/3/count/membertypes";
    ASSERT_EQ(QPrepareURL::PrepareResponseUrl(url),
              "/contests/[0-9]+/count/membertypes");
}

TEST(QPrepareURL, PrepareRequestUrl)
{
    QString url;
    url = "http://[0-9]+.[0-9]+.[0-9]+.[0-9]+:[0-9]+/contests/[0-9]+/count/membertypes";
    ASSERT_EQ(QPrepareURL::PrepareRequestUrl(url, QVector<quint32>{127, 0, 0, 1, 7777, 3}),
              "http://127.0.0.1:7777/contests/3/count/membertypes");

    url = "/contests/[0-9]+/quantity/[0-9]+";
    ASSERT_EQ(QPrepareURL::PrepareRequestUrl(url, QVector<quint32> {3, 8}),
              "/contests/3/quantity/8");

    url = "/contests/[0-9]+/quantity/[0-9]+";
    ASSERT_EQ(QPrepareURL::PrepareRequestUrl(url, QVector<quint32> {3, 8, 9}),
              "/contests/3/quantity/8");

    url = "hello";
    ASSERT_EQ(QPrepareURL::PrepareRequestUrl(url, QVector<quint32> {}),
              "hello");

    url = "/contests/[0-9]+/quantity/[0-9]+";
    ASSERT_EQ(QPrepareURL::PrepareRequestUrl(url, QVector<quint32> {}),
              "/contests/[0-9]+/quantity/[0-9]+");
}

TEST(QPrepareURL, PrepareHttpRequestUrl)
{
    Models::Server server {"127.0.0.1", "7777"};
    QString url;
    url = "/contests/[0-9]+/quantity/[0-9]+";
    ASSERT_EQ(QPrepareURL::PrepareHttpRequestUrl(url, QVector<quint32> {3, 8}, server),
              "http://127.0.0.1:7777/contests/3/quantity/8");
}

TEST(QPrepareURL, PrepareHttpsRequestUrl)
{
    Models::Server server {"127.0.0.1", "7777"};
    QString url;
    url = "/contests/[0-9]+/quantity/[0-9]+";
    ASSERT_EQ(QPrepareURL::PrepareHttpsRequestUrl(url, QVector<quint32> {3, 8}, server),
              "https://127.0.0.1:7777/contests/3/quantity/8");
}



#endif // TST_QPREPARERURL_H
