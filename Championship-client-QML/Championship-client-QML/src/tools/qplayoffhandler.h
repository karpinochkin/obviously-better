#ifndef QPLAYOFFHANDLER_H
#define QPLAYOFFHANDLER_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <algorithm>
#include <random>
#include "../models/member.h"
#include "qpoweroftwo.h"

struct PlayoffInputData {
    QVector<Models::Member> members;
    double pointsForEachStage;
};

using PlayoffPair = QPair<Models::Member, Models::Member>;
using MemberID_Points = QMap<quint32, double>;

class QPlayoffHandler : public QObject
{
    Q_OBJECT
public:
    QPlayoffHandler(QObject *parent = nullptr);
    explicit QPlayoffHandler(const PlayoffInputData &input, QObject *parent = nullptr);
    ~QPlayoffHandler() = default;

    void Start();
    void Stop();
    bool IsStart();
    void Elimination(quint32 idMember);
    quint32 GetPairsInCurrentStage();
    void SetPlayoffInputData(const PlayoffInputData &input);
    PlayoffPair GetNextPair();

private:
    PlayoffInputData data;
    MemberID_Points eliminatedMembers;
    QVector<PlayoffPair> pairs;
    quint32 numberOfPairsInCurrentStage {};
    quint32 stageCount = 0;
    bool isStart = false;

    void connects();
    void checkForPowerOfTwo();
    void checkInputData();

    void nextStage();
    void makePairs();
    void shuffle();
    double getPointsInCurrentStage();
    void setNumberOfPairsInCurrentStage();
    void increaseStageCount();
    bool isFinished();
    void clearAllData();
    void sendResult();

private slots:
//    void elimination(quint32 idMember);

signals:
    void signalNextStage();
//    void signalElimination(quint32 idMember);
    void signalFinish(const QMap<quint32, double>& eliminatedMembers);

};

//#endif // QPLAYOFFGRIDORIGINATOR_H

#endif // QPLAYOFFHANDLER_H
