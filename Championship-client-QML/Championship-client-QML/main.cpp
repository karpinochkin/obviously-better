#include <QGuiApplication>
#include "src/qappstarter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("ikespil");
    QCoreApplication::setApplicationName("Mobile Client");
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

#ifdef Q_OS_ANDROID
     qApp->setQuitOnLastWindowClosed(false);
#endif

    QAppStarter appSterter;

    return app.exec();
}
