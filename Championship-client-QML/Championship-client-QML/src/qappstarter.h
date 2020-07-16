#ifndef QAPPSTARTER_H
#define QAPPSTARTER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QFile>
#include <QStandardPaths>
#include "qmiddlewareqml.h"

class QAppStarter : public QObject
{
    Q_OBJECT
public:
    explicit QAppStarter(QObject *parent = nullptr);
    ~QAppStarter() override;

    QQmlApplicationEngine *engine = nullptr;
    QMiddlewareQML *middleware = nullptr;

public slots:
    void saveQmlEngineWarnings(const QList<QQmlError> &listError);

};

#endif // QAPPSTARTER_H
