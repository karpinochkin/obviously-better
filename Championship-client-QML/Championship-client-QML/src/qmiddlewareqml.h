#ifndef QMIDDLEWAREQML_H
#define QMIDDLEWAREQML_H

#include <QObject>
#include <QQmlPropertyMap>
#include <QGuiApplication>
#include <QSettings>
#include "imageprovider.h"
#include "network/qrouters.h"
#include "tools/qpoweroftwo.h"
#include "tools/qplayoffhandler.h"
#include <algorithm>

class QMiddlewareQML : public QObject
{
    Q_OBJECT
public:
    explicit QMiddlewareQML(QObject *parent = nullptr);
    ~QMiddlewareQML() override = default;

    QQmlPropertyMap *qmlProperty = nullptr;
    ImageProvider *contestImageProvider = nullptr;
    ImageProvider *memberImageProvider = nullptr;
private:
    //    QSettings *settings = nullptr;
    QRouters *routers = nullptr;
    QPlayoffHandler *playoff = nullptr;

    void createObjects();
    void connects();
    void checkPlayoffIsStart();
    void checkPlayoffPairIsValid(PlayoffPair &pair);
    void sortByPoints(QVector<Models::Rating> &rating);
    QVector<Models::Rating> ratingVectorFromMap(const MemberID_Points &eliminatedMembers);

public slots:
    bool isAndroid();
    void exitApp();
    void getContestsCountFromServer();
    void getContestsByRange(quint32 id, quint32 quantity);
    void getContestsByRangeFromServer(quint32 id, quint32 quantity);
    void getContestsByRangeFromDatabase(quint32 id, quint32 quantity);
    void getContestImageForProvider(int id);
    void getMemberImageForProvider(int id);
    void getMemberImageForQML(int id);
    void getCountMembersForContest(quint32 idContest);
    void getValuesOfPowerOfTwo(quint32 value);
    void getMemberFromServer(quint32 id);
    void getRatingByContest(quint32 id);

    void getPlayoffPair();
    void eliminationPlayoffMember(quint32 idMember);
    void startNewContest(quint32 idContest, quint32 quantity);

private slots:
    void contestsByRangeLoadedSlot(const QVector<Models::Contest> &contests);
    void contestsCountLoadedSlot(quint32 count);
    void contestsGetLoadedSlot(const Models::Contest&);
    void membersCountForContestLoadedSlot(quint32 count);
    void startPlayoff(const QVector<Models::Member> &members);
    void nextPlayoffStage();
    void playoffFinished(const MemberID_Points& eliminatedMembers);
    void randomMembersLoadedSlot(QVector<Models::Member> &);
    void memberLoadedSlot(const Models::Member &member);
    void ratingByContestLoadedSlot(const QVector<Models::Rating> &rating);

signals:
    void contestLoaded();
    void contestsLoaded();
    void contestCountLoaded();
    void signalSendContestImageForProvider(QImage);
    void signalSendMemberImageForProvider(QImage);
    void membersCountForContestLoaded();
    void valuesOfPowerOfTwoLoaded();
    void valueOfPowerOfTwoLoaded();
    void signalSendPlayoffPair();
    void signalNextPlayoffStage();
    void signalPlayoffStarted();
    void signalMemberImageLoaded();
    void signalPlayoffFinished();
    void signalPlayoffRatingValueLoaded();
    void signalPlayoffWorldRatingValueLoaded();
    void signalRatingWasSentToServer();
    void signalRatingProcessingWait();
    void signalErrorResponse();


};

#endif // QMIDDLEWAREQML_H
