//#ifndef TST_QPLAYOFFHANDLER_H
//#define TST_QPLAYOFFHANDLER_H

//#include <gtest/gtest.h>
//#include <gmock/gmock-matchers.h>
//#include "../Championship-client-QML/src/tools/qplayoffhandler.h"
//#include <memory>


//TEST(QPlayoffHandler, handler) {
//    QVector<Models::Member> members;
//    Models::Member member;
//    member.id = 1;
//    member.name = "n1";
//    member.description = "d1";
//    members.push_back(member);

//    member.id = 2;
//    member.name = "n2";
//    member.description = "d2";
//    members.push_back(member);

//    member.id = 3;
//    member.name = "n3";
//    member.description = "d3";
//    members.push_back(member);

//    member.id = 4;
//    member.name = "n4";
//    member.description = "d4";
//    members.push_back(member);

//    member.id = 5;
//    member.name = "n5";
//    member.description = "d5";
//    members.push_back(member);

//    member.id = 6;
//    member.name = "n6";
//    member.description = "d6";
//    members.push_back(member);

//    member.id = 7;
//    member.name = "n7";
//    member.description = "d7";
//    members.push_back(member);

//    member.id = 8;
//    member.name = "n8";
//    member.description = "d8";
//    members.push_back(member);

//    PlayoffInputData data {members, 0.3};

////    auto playoff = std::make_shared<QPlayoffHandler>(data);
//    auto *playoff = new QPlayoffHandler(data);

//    auto pair = playoff->GetNextPair();
//    playoff->signalElimination(pair.first.id);

//    pair = playoff->GetNextPair();
//    playoff->signalElimination(pair.second.id);

//    pair = playoff->GetNextPair();
//    playoff->signalElimination(pair.first.id);

//    pair = playoff->GetNextPair();
//    playoff->signalElimination(pair.second.id);

//    pair = playoff->GetNextPair();
//    playoff->signalElimination(pair.first.id);

//    pair = playoff->GetNextPair();
//    playoff->signalElimination(pair.second.id);

//    pair = playoff->GetNextPair();
//    playoff->signalElimination(pair.first.id);

//    pair = playoff->GetNextPair();

////    QPair<Models::Member, Models::Member> emptyPair{};
////    ASSERT_EQ(pair.first, Models::Member{});
////    ASSERT_FALSE(pair.second.isValid());
//}

///*
// * #include <QCoreApplication>
//#include <qplayoffgridoriginator.h>


//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    QVector<Models::Member> members;
//    Models::Member member;
//    member.id = 1;
//    member.name = "n1";
//    member.description = "d1";
//    members.push_back(member);

//    member.id = 2;
//    member.name = "n2";
//    member.description = "d2";
//    members.push_back(member);

//    member.id = 3;
//    member.name = "n3";
//    member.description = "d3";
//    members.push_back(member);

//    member.id = 4;
//    member.name = "n4";
//    member.description = "d4";
//    members.push_back(member);

//    member.id = 5;
//    member.name = "n5";
//    member.description = "d5";
//    members.push_back(member);

//    member.id = 6;
//    member.name = "n6";
//    member.description = "d6";
//    members.push_back(member);

//    member.id = 7;
//    member.name = "n7";
//    member.description = "d7";
//    members.push_back(member);

//    member.id = 8;
//    member.name = "n8";
//    member.description = "d8";
//    members.push_back(member);

////    member.id = 9;
////    member.name = "n9";
////    member.description = "d9";
////    members.push_back(member);

//    PlayoffInputData data {members, 0.3};

//    QPlayoffGridOriginator *playoff = new QPlayoffGridOriginator(data);

//    qDebug() << "PAIR #1";
//    auto pair = playoff->GetNextPair();
//    qDebug() << pair.first.toString() << pair.second.toString();
//    playoff->signalElimination(pair.first.id);

//    qDebug() << "PAIR #2";
//    pair = playoff->GetNextPair();
//    qDebug() << pair.first.toString() << pair.second.toString();
//    playoff->signalElimination(pair.second.id);

//    qDebug() << "PAIR #3";
//    pair = playoff->GetNextPair();
//    qDebug() << pair.first.toString() << pair.second.toString();
//    playoff->signalElimination(pair.first.id);

//    qDebug() << "PAIR #4";
//    pair = playoff->GetNextPair();
//    qDebug() << pair.first.toString() << pair.second.toString();
//    playoff->signalElimination(pair.second.id);

//    qDebug() << "";
//    qDebug() << "NEXT STAGE!";
//    qDebug() << "PAIR #1";
//    pair = playoff->GetNextPair();
//    qDebug() << pair.first.toString() << pair.second.toString();
//    playoff->signalElimination(pair.first.id);

//    qDebug() << "PAIR #2";
//    pair = playoff->GetNextPair();
//    qDebug() << pair.first.toString() << pair.second.toString();
//    playoff->signalElimination(pair.second.id);

//    qDebug() << "";
//    qDebug() << "NEXT STAGE!";
//    qDebug() << "PAIR #1";
//    pair = playoff->GetNextPair();
//    qDebug() << pair.first.toString() << pair.second.toString();
//    playoff->signalElimination(pair.first.id);

//    pair = playoff->GetNextPair();


//    return a.exec();
//}
//*/
//#endif // TST_QPLAYOFFHANDLER_H
