#ifndef TST_QCONTROLLERS_H
#define TST_QCONTROLLERS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#define protected public
#include "../Championship-client-QML/src/network/controllers/qcontestscontroller.h"
#include <memory>

auto db = std::make_shared<QDatabaseController>("testing_championshipGame");
auto controller = std::make_shared<Controllers::QContestController>(db.get());

TEST(QAbstractControllers, arrayModelsProcessing) {
    QVector<Models::Contest> contests {};
    QByteArray data = "[{\"id\":2,\"name\":\"contest 22\",\"description\":\"22\",\"count_play\":22,\"image\":\"ijj123123\",\"MemberType\":[{\"id\":1,\"name\":\"first\",\"Member\":null}]},{\"id\":3,\"name\":\"contest3\",\"description\":\"3\",\"count_play\":3,\"image\":null,\"MemberType\":[]}]\n";
    controller.get()->arrayModelsProcessing(data, contests);

    Models::Contest testContest2;
    testContest2.id = 2;
    testContest2.name = "contest 22";
    testContest2.description = "22";
    testContest2.countPlay = 22;
    testContest2.image = QByteArray::fromBase64("ijj123123");
    testContest2.memberTypesID = {1};

    Models::Contest testContest3;
    testContest3.id = 3;
    testContest3.name = "contest3";
    testContest3.description = "3";
    testContest3.countPlay = 3;
    testContest3.image = "";
    testContest3.memberTypesID = {};

    ASSERT_EQ(contests.at(0).id, testContest2.id);
    ASSERT_EQ(contests.at(0).name, testContest2.name);
    ASSERT_EQ(contests.at(0).description, testContest2.description);
    ASSERT_EQ(contests.at(0).countPlay, testContest2.countPlay);
    ASSERT_EQ(contests.at(0).image, testContest2.image);
    ASSERT_EQ(contests.at(0).memberTypesID, testContest2.memberTypesID);

    ASSERT_EQ(contests.at(1).id, testContest3.id);
    ASSERT_EQ(contests.at(1).name, testContest3.name);
    ASSERT_EQ(contests.at(1).description, testContest3.description);
    ASSERT_EQ(contests.at(1).countPlay, testContest3.countPlay);
    ASSERT_EQ(contests.at(1).image, testContest3.image);
    ASSERT_EQ(contests.at(1).memberTypesID, testContest3.memberTypesID);
}

TEST(QAbstractControllers, modelProcessing) {
    Models::Contest contest {};
    QByteArray data = "{\"id\":2,\"name\":\"contest 22\",\"description\":\"22\",\"count_play\":22,\"image\":\"ijj123123\",\"MemberType\":[{\"id\":1,\"name\":\"first\",\"Member\":null}]}\n";
    controller.get()->modelProcessing(data, contest);

    Models::Contest testContest2;
    testContest2.id = 2;
    testContest2.name = "contest 22";
    testContest2.description = "22";
    testContest2.countPlay = 22;
    testContest2.image = QByteArray::fromBase64("ijj123123");
    testContest2.memberTypesID = {1};

    ASSERT_EQ(contest.id, testContest2.id);
    ASSERT_EQ(contest.name, testContest2.name);
    ASSERT_EQ(contest.description, testContest2.description);
    ASSERT_EQ(contest.countPlay, testContest2.countPlay);
    ASSERT_EQ(contest.image, testContest2.image);
    ASSERT_EQ(contest.memberTypesID, testContest2.memberTypesID);

}
#endif // TST_QCONTROLLERS_H
