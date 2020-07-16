#include "qdatabases.h"
#include <QDebug>

QAbstractDatabase::QAbstractDatabase(QSqlDatabase *database, QObject *parent)
    : QObject(parent),
      currentDatabase(*database)

{
    mutexDataBase = new QMutex();

}

bool QAbstractDatabase::Contains(const Models::QAbstractModel &model)
{
    if (GetID(model) <= 0) {
        return false;
    }
    return true;
}

bool QAbstractDatabase::Contains(quint32 uid, const QString &tableName, const QString &idColumn)
{
    qint32 count{};
    bool result = false;
    QString text = "SELECT count(" + idColumn + ") FROM "
            + tableName + " WHERE " + idColumn + " = " + QString::number(uid) + ";";
    QSqlQuery *query = makeQuery(text, &result);

    if (result) {
        if (query->next()) {
            count = query->value(0).toInt();
        }
    }
    else {
        return false;
    }

    delete query;
    if (count == 0) {
        return false;
    }
    return true;
}

bool QAbstractDatabase::Clear(const QString& tableName)
{
    bool result = false;
    QString text = "DELETE FROM " + tableName + ";";

    QSqlQuery *query = makeQuery(text, &result);
    delete query;
    return result;
}

QAbstractDatabase::~QAbstractDatabase()
{
    delete mutexDataBase;
}

QSqlQuery *QAbstractDatabase::makeQuery(const QString &textQuery, bool *result)
{
    QSqlQuery *query = execQuery(textQuery, result);

    if(!(*result)) {
        printTextError(query->lastError().text(), textQuery);
    }

    return  query;
}

QSqlQuery *QAbstractDatabase::makeQuery(const QString &textQuery, QString bindName, QVariant bindValue, bool *result)
{
    QSqlQuery *query = execQuery(textQuery, bindName, bindValue, result);

    if (!(*result)) {
        printTextError(query->lastError().text(), textQuery);
    }
    return query;
}

QSqlQuery *QAbstractDatabase::execQuery(const QString &textQuery, bool *result)
{

    QSqlQuery *Output;

    mutexDataBase->lock();
    Output = new QSqlQuery(currentDatabase);

    if (currentDatabase.isValid()) {
        if (!currentDatabase.isOpen()) {
            currentDatabase.open();
        }

        if (currentDatabase.isOpen()) {
            if (Output->exec(textQuery)) {
                if (result != nullptr) {
                    *result = true;
                }
            }
            else if (result != nullptr) {
                currentDatabase.close();
                if (currentDatabase.open() && Output->exec(textQuery)) {
                    *result = true;
                }
                else {
                    *result = false;
                }
            }
        }
        else if (result != nullptr) {
            *result = false;
        }
    }
    else if (result != nullptr) {
        *result = false;
    }

    mutexDataBase->unlock();

    return Output;
}

QSqlQuery *QAbstractDatabase::execQuery(QString textQuery, QString bindName, QVariant bindValue, bool *result)
{

    QSqlQuery *Output;

    mutexDataBase->lock();

    Output = new QSqlQuery(currentDatabase);
    Output->prepare(textQuery);
    Output->bindValue(bindName,bindValue);

    if (currentDatabase.isValid()) {
        if (!currentDatabase.isOpen())
            currentDatabase.open();

        if (currentDatabase.isOpen()) {

            if (Output->exec()) {
                if (result != nullptr) *result = true;

            } else if (result != nullptr) *result = false;

        } else if (result != nullptr) *result = false;

    } else if (result != nullptr) *result = false;


    mutexDataBase->unlock();

    return Output;
}

void QAbstractDatabase::printTextError(const QString &textError, const QString &textQuery)
{
    qDebug()<<"Error query: "<<textError;
    qDebug()<<"textQuery = "<<textQuery;
}

QContestDatabase::QContestDatabase(QSqlDatabase *database, QObject *parent)
    : QAbstractDatabase(database, parent)
{

}

void QContestDatabase::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + Models::Contest::DatabaseTable() + " ("
            + Models::Contest::IdColumn() + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + Models::Contest::NameColumn() + " text,"
            + Models::Contest::DescriptionColumn() + " text,"
            + Models::Contest::CountPlayColumn() + "  INTEGER,"
            + Models::Contest::ImageColumn() + " LONGBLOB);";

    bool result = false;
    QSqlQuery *query = makeQuery(text, &result);
    if (result) {
        qDebug() << Models::Contest::DatabaseTable() + " is created";
        delete query;
        return;
    }
    delete query;
    throw QString("QContestDatabase::CreateTable() : query error");
}

Models::Contest QContestDatabase::Get(quint32 id)
{
    QString text = "SELECT "
            + Models::Contest::IdColumn() + ", "
            + Models::Contest::NameColumn() + ", "
            + Models::Contest::DescriptionColumn() + ", "
            + Models::Contest::CountPlayColumn() + ", "
            + Models::Contest::ImageColumn() + " "
            + " FROM "
            + Models::Contest::DatabaseTable()
            + " WHERE "
            + Models::Contest::IdColumn() + " = '"
            + QString::number(id)
            + "';";

    Models::Contest output;
    bool result = false;
    QSqlQuery *query = makeQuery(text, &result);
    if(result) {
        if(query->next()) {
            commonGet(query, output);
        }
    }
    delete  query;
    return output;
}

QVector<Models::Contest> QContestDatabase::GetAll()
{
    QString text = "SELECT "
            + Models::Contest::IdColumn() + ", "
            + Models::Contest::NameColumn() + ", "
            + Models::Contest::DescriptionColumn() + ", "
            + Models::Contest::CountPlayColumn() + ", "
            + Models::Contest::ImageColumn() + " "
            + " FROM "
            + Models::Contest::DatabaseTable() + ";";


    QVector<Models::Contest> contests;
    bool result = false;
    QSqlQuery *query = makeQuery(text, &result);

    if (result) {
        Models::Contest contest;
        while (query->next()) {
            this->commonGet(query, contest);
            contests.push_back(contest);
        }
    }
    delete query;
    return contests;
}

bool QContestDatabase::Add(const Models::QAbstractModel &model)
{
    auto contest = dynamic_cast<const Models::Contest&>(model);
    QString text = "INSERT INTO "
            + Models::Contest::DatabaseTable() + " ("
            + Models::Contest::IdColumn() + ", "
            + Models::Contest::NameColumn() + ", "
            + Models::Contest::DescriptionColumn() + ", "
            + Models::Contest::CountPlayColumn() + ", "
            + Models::Contest::ImageColumn() + " "
            +") VALUES ('"
            + QString::number(contest.id) + "','"
            + contest.name + "','"
            + contest.description + "','"
            + QString::number(contest.countPlay) + "',"
            + ":imageData);";

    bool result = false;
    QSqlQuery *query = makeQuery(text,
                                 ":imageData",
                                 contest.image,
                                 &result);
    delete query;
    return result;
}

bool QContestDatabase::Edit(const Models::QAbstractModel &model)
{
    auto contest = dynamic_cast<const Models::Contest&>(model);
    QString text = "UPDATE "
            + Models::Contest::DatabaseTable()
            + " SET "
            + Models::Contest::NameColumn() + " = '" + contest.name + "',"
            + Models::Contest::DescriptionColumn() + " = '" + contest.description + "',"
            + Models::Contest::CountPlayColumn() + " = '" + QString::number(contest.countPlay) + "',"
            + Models::Contest::ImageColumn() + " = :imageData"
            + " WHERE "
            + Models::Contest::IdColumn() + " = '" + QString::number(contest.id)
            + "';";

    bool result = false;
    QSqlQuery *query = makeQuery(text,
                                 ":imageData",
                                 contest.image,
                                 &result);
    delete query;
    return result;
}

qint32 QContestDatabase::GetID(const Models::QAbstractModel &model)
{
    auto contest = dynamic_cast<const Models::Contest&>(model);
    QString text = "SELECT "
            + Models::Contest::IdColumn()
            + " FROM "
            + Models::Contest::DatabaseTable()
            + " WHERE "
            + Models::Contest::NameColumn() + " = '" + contest.name + "' "
            + " AND "
            + Models::Contest::DescriptionColumn() + " = '" + contest.description + "' "
            + " AND "
            + Models::Contest::CountPlayColumn() + " = '" + QString::number(contest.countPlay) + "' "
            + " AND "
            + Models::Contest::ImageColumn() + " = :imageData"
            + ";";
    qint32 output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(text,
                                 ":imageData",
                                 contest.image,
                                 &result);
    if (result) {
        if (query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

void QContestDatabase::commonGet(QSqlQuery *query, Models::Contest &contest)
{
    contest.id = query->value(0).toInt();
    contest.name = query->value(1).toString();
    contest.description = query->value(2).toString();
    contest.countPlay = query->value(3).toInt();
    contest.image = query->value(4).toByteArray();
}

QMemberDatabase::QMemberDatabase(QSqlDatabase *db, QObject *parent)
    : QAbstractDatabase(db, parent)
{

}

void QMemberDatabase::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + Models::Member::DatabaseTable() + " ("
            + Models::Member::IdColumn() + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + Models::Member::NameColumn() + " text,"
            + Models::Member::DescriptionColumn() + " text,"
            + Models::Member::ImageColumn() + " LONGBLOB);";

    bool result = false;
    QSqlQuery *query = makeQuery(text, &result);
    if (result) {
        qDebug() << Models::Member::DatabaseTable() + " is created";
        delete query;
        return;
    }
    delete query;
    throw QString("QMemberDatabase::CreateTable() : query error");
}

Models::Member QMemberDatabase::Get(quint32 id)
{
    QString text = "SELECT "
            + Models::Member::IdColumn() + ", "
            + Models::Member::NameColumn() + ", "
            + Models::Member::DescriptionColumn() + ", "
            + Models::Member::ImageColumn() + " "
            + " FROM "
            + Models::Member::DatabaseTable()
            + " WHERE "
            + Models::Member::IdColumn() + " = '"
            + QString::number(id)
            + "';";

    Models::Member output;
    bool result = false;
    QSqlQuery *query = makeQuery(text, &result);
    if(result) {
        if(query->next()) {
            commonGet(query, output);
        }
    }
    delete  query;
    return output;
}

bool QMemberDatabase::Add(const Models::QAbstractModel &model)
{
    auto member = dynamic_cast<const Models::Member&>(model);
    QString text = "INSERT INTO "
            + Models::Member::DatabaseTable() + " ("
            + Models::Member::IdColumn() + ", "
            + Models::Member::NameColumn() + ", "
            + Models::Member::DescriptionColumn() + ", "
            + Models::Member::ImageColumn() + " "
            +") VALUES ('"
            + QString::number(member.id) + "','"
            + member.name + "','"
            + member.description + "',"
            + ":imageData);";

    bool result = false;
    QSqlQuery *query = makeQuery(text,
                                 ":imageData",
                                 member.image,
                                 &result);
    delete query;
    return result;
}

bool QMemberDatabase::Edit(const Models::QAbstractModel &model)
{
    auto member = dynamic_cast<const Models::Member&>(model);
    QString text = "UPDATE "
            + Models::Member::DatabaseTable()
            + " SET "
            + Models::Member::NameColumn() + " = '" + member.name + "',"
            + Models::Member::DescriptionColumn() + " = '" + member.description + "',"
            + Models::Member::ImageColumn() + " = :imageData"
            + " WHERE "
            + Models::Member::IdColumn() + " = '" + QString::number(member.id)
            + "';";

    bool result = false;
    QSqlQuery *query = makeQuery(text,
                                 ":imageData",
                                 member.image,
                                 &result);
    delete query;
    return result;
}

qint32 QMemberDatabase::GetID(const Models::QAbstractModel &model)
{
    auto member = dynamic_cast<const Models::Member&>(model);
    QString text = "SELECT "
            + Models::Member::IdColumn()
            + " FROM "
            + Models::Member::DatabaseTable()
            + " WHERE "
            + Models::Member::NameColumn() + " = '" + member.name + "' "
            + " AND "
            + Models::Member::DescriptionColumn() + " = '" + member.description + "' ;";
    qint32 output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(text,
                                 "imageData",
                                 member.image,
                                 &result);
    if (result) {
        if (query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

bool QMemberDatabase::EditWithoutImage(const Models::Member &member)
{
    QString text = "UPDATE "
            + Models::Member::DatabaseTable()
            + " SET "
            + Models::Member::NameColumn() + " = '" + member.name + "',"
            + Models::Member::DescriptionColumn() + " = '" + member.description + "'"
                        + " WHERE "
            + Models::Member::IdColumn() + " = '" + QString::number(member.id)
            + "';";

    bool result = false;
    QSqlQuery *query = makeQuery(text,
                                 &result);
    delete query;
    return result;
}

void QMemberDatabase::commonGet(QSqlQuery *query, Models::Member &model)
{
    model.id = query->value(0).toInt();
    model.name = query->value(1).toString();
    model.description = query->value(2).toString();
    model.image = query->value(3).toByteArray();
}
