#include "qappstarter.h"

QAppStarter::QAppStarter(QObject *parent) : QObject(parent)
{
    engine = new QQmlApplicationEngine(this);
    middleware = new QMiddlewareQML(this);
    connect(engine, &QQmlApplicationEngine::warnings,
            this, &QAppStarter::saveQmlEngineWarnings);

    engine->rootContext()->setContextProperty("middlewareQML", middleware);
    engine->rootContext()->setContextProperty("qmlProperty", middleware->qmlProperty);
    engine->addImageProvider(QLatin1String("contests"), middleware->contestImageProvider);
    engine->addImageProvider(QLatin1String("members"), middleware->memberImageProvider);


    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    engine->load(url);

    if (engine->rootObjects().isEmpty())
        qApp->exit(-1);
}

QAppStarter::~QAppStarter()
{
    engine->deleteLater();
    middleware->deleteLater();
}

void QAppStarter::saveQmlEngineWarnings(const QList<QQmlError> &listError)
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QFile file(folder + "/qmlEngineError.txt");

    for (auto err : listError) {
        if (file.open(QIODevice::Append)) {
            QTextStream stream( &file );
            stream << "\n" << QDateTime::currentDateTime().toString()
                   << ": " << err.toString() << endl;
        }
    }

    file.close();
}
