#ifndef QDATABASECONTROLLER_H
#define QDATABASECONTROLLER_H

#include <QObject>
#include <QMutex>
#include <QtSql/QSqlDatabase>
#include "../models/contest.h"
#include "../models/member.h"
#include "qdatabases.h"

class QDatabaseController : public QObject
{
    Q_OBJECT
public:
    explicit QDatabaseController(const QString &databaseName, QObject *parent = nullptr);
    ~QDatabaseController();

    QContestDatabase *Contest() const;
    QMemberDatabase *Member() const;

private:
    QSqlDatabase *database = nullptr;
    QMutex *mutex = nullptr;
    QContestDatabase *contest = nullptr;
    QMemberDatabase *member = nullptr;
    QString databaseName;

    void initDatabase();
    void createTables();
    void databaseIsInit();


};

#endif // QDATABASECONTROLLER_H
