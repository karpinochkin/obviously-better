#ifndef TST_QDATABASES_H
#define TST_QDATABASES_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../Championship-client-QML/src/database/qdatabases.h"
#include <QSqlDatabase>
#include <memory>
#include <QDebug>

auto database = std::make_shared<QSqlDatabase>();
QString databaseName = "testing_championshipGame";

bool openDB() {
    *database = QSqlDatabase::addDatabase("QSQLITE", databaseName);
    database->setDatabaseName(databaseName + ".db");
    bool result = database->open();
    return result;
}

void closeDB() {
    database.get()->close();
    database.reset();
}

void removeDB() {
    QSqlDatabase::removeDatabase(databaseName);
}

TEST(QContestDatabase, CreateTable) {
    ASSERT_TRUE(openDB());
    auto contestDatabase = std::make_shared<QContestDatabase>(database.get());
    contestDatabase.get()->CreateTable();
    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + Models::Contest::DatabaseTable() + "';";
    bool result = false;
    QSqlQuery *query = contestDatabase->makeQuery(text, &result);
    ASSERT_TRUE(result);
    QString answer = "";
    if (query->next()) {
        answer = query->value(0).toString();
    }
    delete query;
    ASSERT_EQ(answer, Models::Contest::DatabaseTable());
}

TEST(QContestDatabase, Add) {
    auto contestDatabase = std::make_shared<QContestDatabase>(database.get());
    contestDatabase.get()->Clear(Models::Contest::DatabaseTable());

    Models::Contest contest{};
    contest.id = 12;
    contest.name = "test";
    contest.description = "descrpt test";
    contest.countPlay = 118;
    contest.image = QByteArray("imagetest1234567890");

    bool result = contestDatabase.get()->Add(contest);
    ASSERT_TRUE(result);

    QString text = "select * from "
            + Models::Contest::DatabaseTable()
            + " where " + Models::Contest::IdColumn()
            + "= '" + QString::number(contest.id) + "';";
    QSqlQuery *query = contestDatabase->makeQuery(text, &result);
    ASSERT_TRUE(result);

    Models::Contest answerContest{};
    if (query->next()) {
        answerContest.id = query->value(0).toUInt();
        answerContest.name = query->value(1).toString();
        answerContest.description = query->value(2).toString();
        answerContest.countPlay = query->value(3).toUInt();
        answerContest.image = query->value(4).toByteArray();
    }
    delete query;
    ASSERT_EQ(answerContest.id, contest.id);
    ASSERT_EQ(answerContest.name, contest.name);
    ASSERT_EQ(answerContest.description, contest.description);
    ASSERT_EQ(answerContest.countPlay, contest.countPlay);
    ASSERT_EQ(answerContest.image, contest.image);

    contest.id = 11;
    contest.name = "test11";
    contest.description = "descrpt test11";
    contest.countPlay = 11;
    contest.image = QByteArray("imagetest123456789011");

    result = contestDatabase.get()->Add(contest);
    ASSERT_TRUE(result);

    text = "select * from "
            + Models::Contest::DatabaseTable()
            + " where " + Models::Contest::IdColumn()
            + "= '" + QString::number(contest.id) + "';";
    query = contestDatabase->makeQuery(text, &result);
    ASSERT_TRUE(result);

    if (query->next()) {
        answerContest.id = query->value(0).toUInt();
        answerContest.name = query->value(1).toString();
        answerContest.description = query->value(2).toString();
        answerContest.countPlay = query->value(3).toUInt();
        answerContest.image = query->value(4).toByteArray();
    }
    delete query;
    ASSERT_EQ(answerContest.id, contest.id);
    ASSERT_EQ(answerContest.name, contest.name);
    ASSERT_EQ(answerContest.description, contest.description);
    ASSERT_EQ(answerContest.countPlay, contest.countPlay);
    ASSERT_EQ(answerContest.image, contest.image);
}

TEST(QContestDatabase, Edit) {
    auto contestDatabase = std::make_shared<QContestDatabase>(database.get());
    Models::Contest contest{};
    contest.id = 12;
    contest.name = "testedit";
    contest.description = "descrpt test edit";
    contest.countPlay = 1;
    contest.image = QByteArray("imagetest123456edit7890");

    bool result = contestDatabase.get()->Edit(contest);
    ASSERT_TRUE(result);

    QString text = "select * from "
            + Models::Contest::DatabaseTable()
            + " where " + Models::Contest::IdColumn()
            + "= '" + QString::number(contest.id) + "';";
    QSqlQuery *query = contestDatabase->makeQuery(text, &result);
    ASSERT_TRUE(result);

    Models::Contest answerContest{};
    if (query->next()) {
        answerContest.id = query->value(0).toUInt();
        answerContest.name = query->value(1).toString();
        answerContest.description = query->value(2).toString();
        answerContest.countPlay = query->value(3).toUInt();
        answerContest.image = query->value(4).toByteArray();
    }
    delete query;
    ASSERT_EQ(answerContest.id, contest.id);
    ASSERT_EQ(answerContest.name, contest.name);
    ASSERT_EQ(answerContest.description, contest.description);
    ASSERT_EQ(answerContest.countPlay, contest.countPlay);
    ASSERT_EQ(answerContest.image, contest.image);
}

TEST(QContestDatabase, Get) {
    auto contestDatabase = std::make_shared<QContestDatabase>(database.get());
    auto model = contestDatabase.get()->Get(11);

    Models::Contest contest{};
    contest.id = 11;
    contest.name = "test11";
    contest.description = "descrpt test11";
    contest.countPlay = 11;
    contest.image = QByteArray("imagetest123456789011");

    ASSERT_EQ(model.id, contest.id);
    ASSERT_EQ(model.name, contest.name);
    ASSERT_EQ(model.description, contest.description);
    ASSERT_EQ(model.countPlay, contest.countPlay);
    ASSERT_EQ(model.image, contest.image);

}

TEST(QContestDatabase, GetAll) {
    auto contestDatabase = std::make_shared<QContestDatabase>(database.get());
    Models::Contest contest11{};
    contest11.id = 11;
    contest11.name = "test11";
    contest11.description = "descrpt test11";
    contest11.countPlay = 11;
    contest11.image = QByteArray("imagetest123456789011");

    Models::Contest contest12{};
    contest12.id = 12;
    contest12.name = "testedit";
    contest12.description = "descrpt test edit";
    contest12.countPlay = 1;
    contest12.image = QByteArray("imagetest123456edit7890");

    QVector<Models::Contest> contests = contestDatabase.get()->GetAll();
    ASSERT_EQ(contest11.id, contests.at(0).id);
    ASSERT_EQ(contest11.name, contests.at(0).name);
    ASSERT_EQ(contest11.description, contests.at(0).description);
    ASSERT_EQ(contest11.countPlay, contests.at(0).countPlay);
    ASSERT_EQ(contest11.image, contests.at(0).image);

    ASSERT_EQ(contest12.id, contests.at(1).id);
    ASSERT_EQ(contest12.name, contests.at(1).name);
    ASSERT_EQ(contest12.description, contests.at(1).description);
    ASSERT_EQ(contest12.countPlay, contests.at(1).countPlay);
    ASSERT_EQ(contest12.image, contests.at(1).image);
}

TEST(QAbstractDatabase, Contains) {
    auto contestDatabase = std::make_shared<QContestDatabase>(database.get());
    Models::Contest contest{};
    contest.id = 11;
    contest.name = "test11";
    contest.description = "descrpt test11";
    contest.countPlay = 11;
    contest.image = QByteArray("imagetest123456789011");
    bool result = contestDatabase.get()->Contains(contest);
    ASSERT_TRUE(result);

    result = contestDatabase.get()->Contains(contest.id, Models::Contest::DatabaseTable(), Models::Contest::IdColumn());
    ASSERT_TRUE(result);

    result = contestDatabase.get()->Contains(99, Models::Contest::DatabaseTable(), Models::Contest::IdColumn());
    ASSERT_FALSE(result);

    contest.image = QByteArray("new image");
    result = contestDatabase.get()->Contains(contest);
    ASSERT_FALSE(result);

    contest.countPlay = 45;
    result = contestDatabase.get()->Contains(contest);
    ASSERT_FALSE(result);
}

TEST(QMemberDatabase, CreateTable) {
    auto memberDatabase = std::make_shared<QMemberDatabase>(database.get());
    memberDatabase->CreateTable();

    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + Models::Member::DatabaseTable() + "';";
    bool result = false;
    QSqlQuery *query = memberDatabase->makeQuery(text, &result);
    ASSERT_TRUE(result);
    QString answer = "";
    if (query->next()) {
        answer = query->value(0).toString();
    }
    delete query;
    ASSERT_EQ(answer, Models::Member::DatabaseTable());
}

TEST(QMemberDatabase, Add) {
    auto memberDatabase = std::make_shared<QMemberDatabase>(database.get());
    memberDatabase.get()->Clear(Models::Member::DatabaseTable());
    Models::Member member1{};
    member1.id = 7;
    member1.name = "test 1";
    member1.description = "desc test 1";
    member1.image = QByteArray("byteimagearray1873");

    Models::Member member2{};
    member2.id = 2;
    member2.name = "test 2";
    member2.description = "desc test 2";
    member2.image = QByteArray("byteimagearray122222222222");

    bool result = memberDatabase.get()->Add(member1);
    ASSERT_TRUE(result);

    result = memberDatabase.get()->Add(member2);
    ASSERT_TRUE(result);

    QString text = "select * from "
            + Models::Member::DatabaseTable()
            + " where " + Models::Member::IdColumn()
            + "= '" + QString::number(member1.id) + "';";
    QSqlQuery *query = memberDatabase->makeQuery(text, &result);
    ASSERT_TRUE(result);

    Models::Member answerMember{};
    if(query->next()) {
        answerMember.id = query->value(0).toUInt();
        answerMember.name = query->value(1).toString();
        answerMember.description = query->value(2).toString();
        answerMember.image = query->value(3).toByteArray();
    }
    ASSERT_EQ(answerMember.id, member1.id);
    ASSERT_EQ(answerMember.name, member1.name);
    ASSERT_EQ(answerMember.description, member1.description);
    ASSERT_EQ(answerMember.image, member1.image);

    text = "select * from "
            + Models::Member::DatabaseTable()
            + " where " + Models::Member::IdColumn()
            + "= '" + QString::number(member2.id) + "';";
    query = memberDatabase->makeQuery(text, &result);
    ASSERT_TRUE(result);

    if(query->next()) {
        answerMember.id = query->value(0).toUInt();
        answerMember.name = query->value(1).toString();
        answerMember.description = query->value(2).toString();
        answerMember.image = query->value(3).toByteArray();
    }
    ASSERT_EQ(answerMember.id, member2.id);
    ASSERT_EQ(answerMember.name, member2.name);
    ASSERT_EQ(answerMember.description, member2.description);
    ASSERT_EQ(answerMember.image, member2.image);
    delete query;
}

TEST(QMemberDatabase, Edit) {
    auto memberDatabase = std::make_shared<QMemberDatabase>(database.get());
    Models::Member member {};
    member.id = 7;
    member.name = "testedit";
    member.description = "descrpt test edit";
    member.image = QByteArray("imagetest123456edit7890");

    bool result = memberDatabase.get()->Edit(member);
    ASSERT_TRUE(result);

    QString text = "select * from "
            + Models::Member::DatabaseTable()
            + " where " + Models::Member::IdColumn()
            + "= '" + QString::number(member.id) + "';";
    QSqlQuery *query = memberDatabase->makeQuery(text, &result);
    ASSERT_TRUE(result);

    Models::Member answerMember{};
    if (query->next()) {
        answerMember.id = query->value(0).toUInt();
        answerMember.name = query->value(1).toString();
        answerMember.description = query->value(2).toString();
        answerMember.image = query->value(3).toByteArray();
    }
    delete query;
    ASSERT_EQ(answerMember.id, member.id);
    ASSERT_EQ(answerMember.name, member.name);
    ASSERT_EQ(answerMember.description, member.description);
    ASSERT_EQ(answerMember.image, member.image);
}

TEST(QMemberDatabase, Get) {
    auto memberDatabase = std::make_shared<QMemberDatabase>(database.get());
    auto model = memberDatabase.get()->Get(7);

    Models::Member member{};
    member.id = 7;
    member.name = "testedit";
    member.description = "descrpt test edit";
    member.image = QByteArray("imagetest123456edit7890");

    ASSERT_EQ(model.id, member.id);
    ASSERT_EQ(model.name, member.name);
    ASSERT_EQ(model.description, member.description);
    ASSERT_EQ(model.image, member.image);
}

TEST(QMemberDatabase, GetAll) {
    {
        auto memberDatabase = std::make_shared<QMemberDatabase>(database.get());
        Models::Member newMember;
        newMember.id = 2;
        newMember.name = "new member";
        newMember.description = "desc new member test 2";
        newMember.image = QByteArray("");

        Models::Member oldMember{};
        oldMember.id = 2;
        oldMember.name = "test 2";
        oldMember.description = "desc test 2";
        oldMember.image = QByteArray("byteimagearray122222222222");

        bool result = memberDatabase.get()->EditWithoutImage(newMember);
        ASSERT_TRUE(result);

        auto memberFromDB = memberDatabase.get()->Get(newMember.id);
        ASSERT_EQ(newMember.id, memberFromDB.id);
        ASSERT_EQ(newMember.name, memberFromDB.name);
        ASSERT_EQ(newMember.description, memberFromDB.description);
        ASSERT_EQ(oldMember.image, memberFromDB.image);
        closeDB();
    }
    removeDB();
}

#endif // TST_QDATABASES_H
