#ifndef QDATABASES_H
#define QDATABASES_H

#include <QObject>
#include "../models/contest.h"
#include "../models/member.h"
#include <QSqlDatabase>
#include <QMutex>
#include <QSqlQuery>
#include <QSqlError>

class QAbstractDatabase : public QObject
{
public:
    ~QAbstractDatabase();
    QSqlQuery* makeQuery(const QString &textQuery,
                         bool *result);
    QSqlQuery* makeQuery(const QString &textQuery,
                         QString bindName,
                         QVariant bindValue,
                         bool *result);
    virtual bool Contains(const Models::QAbstractModel&);
    bool Contains(quint32 uid, const QString &tableName, const QString &idColumn);
    bool Clear(const QString &tableName);

protected:
    QAbstractDatabase(QSqlDatabase *database, QObject *parent = nullptr);
    virtual void CreateTable() = 0;
    virtual bool Add(const Models::QAbstractModel& model) = 0;
    virtual bool Edit(const Models::QAbstractModel& model) = 0;
    virtual qint32 GetID(const Models::QAbstractModel& model) = 0;

private:
    QMutex *mutexDataBase = nullptr;
    QSqlDatabase currentDatabase;

    QSqlQuery *execQuery(const QString &textQuery,
                         bool *result = nullptr);
    QSqlQuery *execQuery(QString textQuery,
                         QString bindName,
                         QVariant bindValue,
                         bool *result = nullptr);
    void printTextError(const QString &textError,
                        const QString &textQuery);
};

class QContestDatabase : public QAbstractDatabase
{
public:
    QContestDatabase(QSqlDatabase *database, QObject *parent = nullptr);
    ~QContestDatabase() = default;

    void CreateTable() override;
    Models::Contest Get(quint32 id);
    bool Add(const Models::QAbstractModel&model) override;
    bool Edit(const Models::QAbstractModel&model) override;
    qint32 GetID(const Models::QAbstractModel&model) override;
    QVector<Models::Contest> GetAll();

private:
    void commonGet(QSqlQuery *query, Models::Contest &contest);
};

class QMemberDatabase : public QAbstractDatabase
{
public:
    QMemberDatabase(QSqlDatabase *db, QObject *parent = nullptr);
    ~QMemberDatabase() = default;

    void CreateTable() override;
    Models::Member Get(quint32 id);
    bool Add(const Models::QAbstractModel &model) override;
    bool Edit(const Models::QAbstractModel &model) override;
    qint32 GetID(const Models::QAbstractModel &model) override;
    bool EditWithoutImage(const Models::Member &member);

private:
    void commonGet(QSqlQuery *query, Models::Member &model);
};

#endif // QDATABASES_H
