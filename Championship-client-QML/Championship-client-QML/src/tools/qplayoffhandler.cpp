#include "qplayoffhandler.h"

QPlayoffHandler::QPlayoffHandler(QObject *parent)
    : QObject(parent)
{
    connects();
}

QPlayoffHandler::QPlayoffHandler(const PlayoffInputData &input, QObject *parent)
    : QObject(parent),
      data(input)
{
    connects();
    Start();
}

void QPlayoffHandler::connects()
{
    connect(this, &QPlayoffHandler::signalFinish,
            this, [=]() {
//        clearAllData();
    });
}

/// Начало соревнования
void QPlayoffHandler::Start()
{
    try {
        isStart = true;
        checkInputData();
        checkForPowerOfTwo(); // проверка на степень 2
        nextStage();
    }
    catch (const QString& err) {
        qDebug() << "QPlayoffHandler::Start() : " << err;
    }
    catch (const std::exception& err) {
        qDebug() << "QPlayoffHandler::Start() : " << err.what();
    }
}

void QPlayoffHandler::Stop()
{
    clearAllData();
}

bool QPlayoffHandler::IsStart()
{
    return isStart;
}

void QPlayoffHandler::Elimination(quint32 idMember)
{
    for (int i = 0; i < data.members.size(); ++i) {
        if (data.members.at(i).id == idMember) {
            eliminatedMembers.insert(data.members.at(i).id, getPointsInCurrentStage());
            data.members.remove(i);
            --i;
            return;
        }
    }
}

quint32 QPlayoffHandler::GetPairsInCurrentStage()
{
    return numberOfPairsInCurrentStage;
}

/// Установка новых начальных данных
void QPlayoffHandler::SetPlayoffInputData(const PlayoffInputData &input)
{
    data = input;
}

/// Запрос на следующую пару
PlayoffPair QPlayoffHandler::GetNextPair()
{
    // Если вектор пар - пуст, пора переходить на новую стадию playoff
    if (pairs.isEmpty()) {
        nextStage();
    }

    // Если после предыдущего шага вектор заполнился - возвращаем запрашиваемую пару
    // и удаляем ее из вектора
    if (!pairs.isEmpty()) {
        QPair output = pairs.at(0);
        pairs.remove(0);

        return output;
    }

    // Если вектор все еще пуст, то возвращает пустую пару
    return QPair<Models::Member, Models::Member>{};
}

void QPlayoffHandler::nextStage()
{
    try {
        increaseStageCount(); // Увеличиваем значение стадии

        // Закончился ли турнир?
        if(isFinished()) {
            sendResult();
            return;
        }
        setNumberOfPairsInCurrentStage(); // устанавливаем количество пар в текущей стадии
        shuffle(); // перемешиваем вектор участников
        makePairs(); // формируем пары участников

        emit (signalNextStage()); // высылаем сигнал перехода на новую стадию
    } catch (const QString& err) {
        qDebug() << "QPlayoffHandler::nextStage() : " << err;
    }
    catch (const std::exception& err) {
        qDebug() << "QPlayoffHandler::nextStage() : " << err.what();
    }
}


/// Проверка на соответствие количества участников степени двойки
void QPlayoffHandler::checkForPowerOfTwo()
{
    if (!QPowerOfTwo::isPowerOfTwo(data.members.size())) {
        throw QString("!QPowerOfTwo::isPowerOfTwo");
    }
}

/// Проверка корректности входных данных
void QPlayoffHandler::checkInputData()
{
    if (data.members.isEmpty() || data.pointsForEachStage <= 0.0) {
        throw QString("data is invalid");
    }
}

/// Перемешивание вектора участников
void QPlayoffHandler::shuffle()
{
    std::random_device rng;
    std::shuffle(std::begin(data.members), std::end(data.members), rng);
}

/// Формирование пар участников
void QPlayoffHandler::makePairs()
{
    for (int i = 0; i < data.members.size(); i = i + 2) {
        pairs.push_back(QPair(data.members.at(i), data.members.at(i+1)));
    }
}

/// Получение очков за вылет на текущей стадии
double QPlayoffHandler::getPointsInCurrentStage()
{
    return stageCount * data.pointsForEachStage;
}

void QPlayoffHandler::setNumberOfPairsInCurrentStage()
{
    numberOfPairsInCurrentStage = data.members.size() / 2;
}

void QPlayoffHandler::increaseStageCount()
{
    ++stageCount;
}

bool QPlayoffHandler::isFinished()
{
    // Если остался 1 участник - турнин закончен
    if (data.members.size() == 1) {
        return true;
    }
    return false;
}

void QPlayoffHandler::clearAllData()
{
    isStart = false;
    data.members.clear();
    data.pointsForEachStage = 0;
    eliminatedMembers.clear();
    pairs.clear();
    stageCount = 0;
}

void QPlayoffHandler::sendResult()
{
    eliminatedMembers.insert(data.members.at(0).id, getPointsInCurrentStage());
    auto keys = eliminatedMembers.keys();
    emit (signalFinish(std::move(eliminatedMembers))); // Турнир закончен
}




