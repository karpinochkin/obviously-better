#include "qdatabasecontroller.h"
#include <QDebug>

QDatabaseController::QDatabaseController(const QString &databaseName, QObject *parent)
    : QObject(parent),
      databaseName(databaseName)
{
    mutex = new QMutex();
    initDatabase();
}

QDatabaseController::~QDatabaseController()
{
    delete database;
    delete mutex;
}

QContestDatabase *QDatabaseController::Contest() const
{
    return contest;
}

QMemberDatabase *QDatabaseController::Member() const
{
    return member;
}

void QDatabaseController::initDatabase()
{
    try {
        if (database != nullptr) {
            throw QString("the database has already been created");
        }
        mutex->lock();
        database = new QSqlDatabase();
        *database = QSqlDatabase::addDatabase("QSQLITE", databaseName);
        database->setDatabaseName(databaseName + ".db");
        bool result = database->open();

        mutex->unlock();

        if (!result) {
            throw  QString("the database was not opened!");
        }

        databaseIsInit();

    } catch (const QString& err) {
        qDebug() << "QDatabaseController::initDatabase() :" << err;
    }

}

void QDatabaseController::createTables()
{
    contest->CreateTable();
    member->CreateTable();
    contest->Clear(Models::Contest::DatabaseTable());
//    member->Clear(Models::Contest::DatabaseTable());
}

void QDatabaseController::databaseIsInit()
{
    try {
        contest = new QContestDatabase(database, this);
        member = new QMemberDatabase(database, this);
        createTables();
    } catch (const QString& err) {
        qDebug() << "QDatabaseController::databaseIsInit() -> " << err;
    }
}
