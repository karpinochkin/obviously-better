#include "qmiddlewareqml.h"

QMiddlewareQML::QMiddlewareQML(QObject *parent) : QObject(parent)
{
    createObjects();
    connects();
    getContestsCountFromServer();
}

void QMiddlewareQML::createObjects()
{
    contestImageProvider = new ImageProvider(QQmlImageProviderBase::Image, this);
    memberImageProvider = new ImageProvider(QQmlImageProviderBase::Image, this);
    routers = new QRouters(this);
    qmlProperty = new QQmlPropertyMap(this);
    playoff = new QPlayoffHandler(this);
}

void QMiddlewareQML::connects()
{
    connect(routers->Controllers()->Contests(), &Controllers::QContestController::signalGetByRangeLoaded,
            this, &QMiddlewareQML::contestsByRangeLoadedSlot);
    connect(routers->Controllers()->Contests(), &Controllers::QContestController::signalGet,
            this, &QMiddlewareQML::contestsGetLoadedSlot);
    connect(routers->Controllers()->Contests(), &Controllers::QContestController::signalCountMembersLoaded,
            this, &QMiddlewareQML::membersCountForContestLoadedSlot);
    connect(routers->Controllers()->Contests(), &Controllers::QContestController::signalCount,
            this, &QMiddlewareQML::contestsCountLoadedSlot);
    connect(routers->Controllers()->Members(), &Controllers::QMemberController::signalGet,
            this, &QMiddlewareQML::memberLoadedSlot);
    connect(routers->Controllers()->MemberTypes(), &Controllers::QMemberTypeController::signalRandomMembersLoaded,
            this, &QMiddlewareQML::randomMembersLoadedSlot);
    connect(routers->Controllers()->Rating(), &Controllers::QRatingController::signalGetByContest,
            this, &QMiddlewareQML::ratingByContestLoadedSlot);
    connect(contestImageProvider, &ImageProvider::signalImageFromDB,
            this, &QMiddlewareQML::getContestImageForProvider);
    connect(this, &QMiddlewareQML::signalSendContestImageForProvider,
            contestImageProvider, &ImageProvider::slotGetImageFromDB);
    connect(memberImageProvider, &ImageProvider::signalImageFromDB,
            this, &QMiddlewareQML::getMemberImageForProvider);
    connect(this, &QMiddlewareQML::signalSendMemberImageForProvider,
            memberImageProvider, &ImageProvider::slotGetImageFromDB);
    connect(routers->Controllers()->Rating(), &Controllers::QRatingController::signalCreate,
            this, &QMiddlewareQML::signalRatingWasSentToServer);
    connect(playoff, &QPlayoffHandler::signalNextStage,
            this, &QMiddlewareQML::nextPlayoffStage);
    connect(playoff, &QPlayoffHandler::signalFinish,
            this, &QMiddlewareQML::playoffFinished);
    connect(routers, &QRouters::ErrorResponse, this, [=](QString err) {
        int index = err.toStdString().find("server replied");
        auto errorDisplayText = QString::fromStdString(err.toStdString().substr(index, err.size()));
        qmlProperty->insert("errorResponse", QVariant(errorDisplayText));
        emit (signalErrorResponse());
    });
}

void QMiddlewareQML::checkPlayoffIsStart()
{
    if (!playoff->IsStart()) {
        throw QString("playoff is not start!");
    }
}

void QMiddlewareQML::checkPlayoffPairIsValid(PlayoffPair &pair)
{
    if (!pair.first.isValid() || !pair.second.isValid()) {
        throw QString("pair is not valid!");
    }
}

void QMiddlewareQML::sortByPoints(QVector<Models::Rating> &rating)
{
    std::sort(rating.begin(), rating.end(), [](const Models::Rating &a, const Models::Rating &b) {
        return (a.points > b.points);
    });
}

QVector<Models::Rating> QMiddlewareQML::ratingVectorFromMap(const MemberID_Points &eliminatedMembers)
{
    QVector<Models::Rating> ratingVector;
    Models::Rating rating;
    rating.idContest = qmlProperty->value("currentIdContest").toUInt();
    auto keys = eliminatedMembers.keys();

    for (auto key : keys) {
        rating.idMember = key;
        rating.points = eliminatedMembers.find(key).value();
        if (rating.isValid()) {
            ratingVector.push_back(rating);
        }
    }

    return ratingVector;
}

void QMiddlewareQML::getContestImageForProvider(int id)
{
    QImage image;

    if (Models::Contest contest = routers->Database()->Contest()->Get(id);
            contest.image.isEmpty()) {
        image.load(":/images/lock.jpg");
    } else {
        image.loadFromData(contest.image);
    }

    emit (signalSendContestImageForProvider(image));
}

void QMiddlewareQML::getMemberImageForProvider(int id)
{
    QImage image;

    if (Models::Member member = routers->Database()->Member()->Get(id);
            member.image.isEmpty()) {
        image.load(":/images/unknown.jpg");
    } else {
        image.loadFromData(member.image);
    }

    emit (signalSendMemberImageForProvider(image));
}

void QMiddlewareQML::getMemberImageForQML(int id)
{
    if (!routers->Database()->Member()->Contains(id, Models::Member::DatabaseTable(), Models::Member::IdColumn())) {
        getMemberFromServer(id);
        return;
    }

    if (Models::Member member = routers->Database()->Member()->Get(id);
            member.image.isEmpty()) {
        getMemberFromServer(id);
        return;
    }

    qmlProperty->insert("idMemberImageLoaded", QVariant(id));
    emit (signalMemberImageLoaded());
}

void QMiddlewareQML::getCountMembersForContest(quint32 idContest)
{
    routers->Requesters()->Contest()->CountMembers(idContest);
}

void QMiddlewareQML::getValuesOfPowerOfTwo(quint32 value)
{
    auto values = QPowerOfTwo::GetValuesOfPowerOfTwo(value);
    for (auto val : values) {
        qmlProperty->insert("valueOfPowerOfTwo", QVariant(val));
        emit (valueOfPowerOfTwoLoaded());
    }

    emit (valuesOfPowerOfTwoLoaded());
}

void QMiddlewareQML::getMemberFromServer(quint32 id)
{
    routers->Requesters()->Member()->Get(id);
}

void QMiddlewareQML::getRatingByContest(quint32 id)
{
    routers->Requesters()->Rating()->GetByContest(id);
}

bool QMiddlewareQML::isAndroid()
{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

void QMiddlewareQML::exitApp()
{
    qmlProperty->deleteLater();
    qGuiApp->quit();
}

void QMiddlewareQML::getContestsCountFromServer()
{
    routers->Requesters()->Contest()->Count();
}

// Получает значения из диапазона (если такого элемента нет в бд, то запрашивает с сервера)
void QMiddlewareQML::getContestsByRange(quint32 id, quint32 quantity)
{
    QVector<Models::Contest> contests {};

    for (quint32 i = id; i < (id + quantity); ++i) {
        if (auto model = routers->Database()->Contest()->Get(i); model.isValid()) {
            contests.push_back(model);
        }
        else {
            routers->Requesters()->Contest()->Get(i);
        }
    }
    contestsByRangeLoadedSlot(contests);
    emit (contestsLoaded());

}

// Получает значения из диапазона запрашивая данные с сервера
void QMiddlewareQML::getContestsByRangeFromServer(quint32 id, quint32 quantity)
{
    routers->Requesters()->Contest()->GetByRange(id, quantity);
}

// Получает значения из диапазона запрашивая данные из базы данных
void QMiddlewareQML::getContestsByRangeFromDatabase(quint32 id, quint32 quantity)
{
    try {
        QVector<Models::Contest> contests {};

        for (quint32 i = id; i < (id + quantity); ++i) {
            auto model = routers->Database()->Contest()->Get(i);
            if (!model.isValid()) {
                throw QString("model is not valid");
            }
            contests.push_back(model);
        }

        contestsByRangeLoadedSlot(contests);
        emit (contestsLoaded());
    } catch (const QString &err) {
        qDebug() << "QMiddlewareQML::getContestsByRangeFromDatabase(quint32 id, quint32 quantity) : " << err;
    }

}

void QMiddlewareQML::contestsByRangeLoadedSlot(const QVector<Models::Contest> &contests)
{
    for (auto contest : contests) {
        contestsGetLoadedSlot(contest);
        emit (contestsLoaded());
    }
}

void QMiddlewareQML::contestsCountLoadedSlot(quint32 count)
{
    qmlProperty->insert("contestsCount", QVariant(count));
    emit(contestCountLoaded());
}

void QMiddlewareQML::contestsGetLoadedSlot(const Models::Contest &contest)
{
    if (contest.id > 0) {
        qmlProperty->insert("idContest", QVariant(contest.id));
        qmlProperty->insert("nameContest", QVariant(contest.name));
        qmlProperty->insert("descriptionContest", QVariant(contest.description));
        qmlProperty->insert("countPlayContest", QVariant(contest.countPlay));
        emit (contestLoaded());
    }
}

void QMiddlewareQML::membersCountForContestLoadedSlot(quint32 count)
{
    qmlProperty->insert("membersCountForContest", QVariant(count));
    emit (membersCountForContestLoaded());
}

void QMiddlewareQML::startPlayoff(const QVector<Models::Member>& members)
{
    PlayoffInputData data {members, 0.3};
    playoff->Stop();
    playoff->SetPlayoffInputData(data);
    playoff->Start();
}

void QMiddlewareQML::nextPlayoffStage()
{
    checkPlayoffIsStart();
    auto numberPairsInCurrentStage = playoff->GetPairsInCurrentStage();
    qmlProperty->insert("numberPairsInCurrentStage", QVariant(numberPairsInCurrentStage));
    emit (signalNextPlayoffStage());
}

void QMiddlewareQML::playoffFinished(const MemberID_Points &eliminatedMembers)
{
    signalRatingProcessingWait();
    auto ratingVector = ratingVectorFromMap(std::move(eliminatedMembers));
    sortByPoints(ratingVector);

    int i = 0;
    for (auto val : ratingVector) {

        qmlProperty->insert("ratingNameMember",
                            routers->Database()->Member()->Get(
                                val.idMember).name);
        qmlProperty->insert("ratingIdContest", val.idContest);
        qmlProperty->insert("ratingIdMember", val.idMember);
        qmlProperty->insert("ratingPoints", val.points);
        qmlProperty->insert("ratingItemNumber", ++i);
        emit (signalPlayoffRatingValueLoaded());

    }

    // Отправка данных на сервер
    routers->Requesters()->Rating()->Create(ratingVector);

}

void QMiddlewareQML::randomMembersLoadedSlot(QVector<Models::Member> &members)
{
    startPlayoff(members);
    emit (signalPlayoffStarted());
}

void QMiddlewareQML::memberLoadedSlot(const Models::Member &member)
{
    qmlProperty->insert("idMemberImageLoaded", QVariant(member.id));
    emit (signalMemberImageLoaded());
}

void QMiddlewareQML::ratingByContestLoadedSlot(const QVector<Models::Rating> &rating)
{
    int i = 0;
    for (auto val : rating) {
        if (val.isValid()) {
            qmlProperty->insert("ratingWorldNameMember",
                                routers->Database()->Member()->Get(
                                    val.idMember).name);
            qmlProperty->insert("ratingWorldIdContest", val.idContest);
            qmlProperty->insert("ratingWorldIdMember", val.idMember);
            qmlProperty->insert("ratingWorldPoints", val.points);
            qmlProperty->insert("ratingWorldItemNumber", ++i);

            emit (signalPlayoffWorldRatingValueLoaded());
        }
    }
    emit (signalPlayoffFinished());
}

void QMiddlewareQML::getPlayoffPair()
{
    try {
        checkPlayoffIsStart();
        auto pair = playoff->GetNextPair();
        checkPlayoffPairIsValid(pair);
        quint32 countPairsInStage = playoff->GetPairsInCurrentStage();

        // Записываем пару для использования в qml
        qmlProperty->insert("firstMemberInPairID", QVariant(pair.first.id));
        qmlProperty->insert("firstMemberInPairName", QVariant(pair.first.name));
        qmlProperty->insert("firstMemberInPairDecription", QVariant(pair.first.description));
        qmlProperty->insert("secondMemberInPairID", QVariant(pair.second.id));
        qmlProperty->insert("secondMemberInPairName", QVariant(pair.second.name));
        qmlProperty->insert("secondMemberInPairDecription", QVariant(pair.second.description));
        qmlProperty->insert("countPairsInStage", QVariant(countPairsInStage));

        emit (signalSendPlayoffPair());
    } catch (const QString &err) {
        qDebug() << "QMiddlewareQML::getPlayoffPair() : " << err;
    }
}

void QMiddlewareQML::eliminationPlayoffMember(quint32 idMember)
{
    playoff->Elimination(idMember);
}

void QMiddlewareQML::startNewContest(quint32 idContest, quint32 quantity)
{
    qmlProperty->insert("currentIdContest", QVariant(idContest));
    routers->Requesters()->Contest()->GetRandomMembers(idContest, quantity);
}
