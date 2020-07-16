#include "qconfiguration.h"
#include <QDebug>

QConfiguration* QConfiguration::configuration = nullptr;

QConfiguration *QConfiguration::GetConfig()
{
    if (configuration == nullptr) {
        configuration = new QConfiguration();
    }
    return configuration;
}

QConfiguration::QConfiguration()
{
    settings = new QSettings("Championship/client-qml");
    setDefaultSettings();
//    loadSettings();
}

QConfiguration::~QConfiguration()
{
    delete settings;
}

Models::Server QConfiguration::GetServer() const
{
    return server;
}

QString QConfiguration::GetDatabaseName()
{
    return databaseName;
}

void QConfiguration::loadSettings()
{
    try {
        containsSettingsValue(settings, QString::fromStdString(
                                  GetServerHostConfigPath().string()));
        containsSettingsValue(settings, QString::fromStdString(
                                  GetServerPortConfigPath().string()));
        containsSettingsValue(settings, QString::fromStdString(
                                  GetDatabaseNameConfigPath().string()));

        setSpecifiedSettings();
    } catch (QString) {
        setDefaultSettings();
        saveSettings();
    }
}

void QConfiguration::saveSettings()
{
    settings->setValue(QString::fromStdString(
                           GetServerHostConfigPath().string()), server.host);
    settings->setValue(QString::fromStdString(
                           GetServerPortConfigPath().string()), server.port);
    settings->setValue(QString::fromStdString(
                           GetDatabaseNameConfigPath().string()), databaseName);
}

void QConfiguration::containsSettingsValue(const QSettings *settings, const QString& key) const
{
    if (!settings->contains(key)) {
        throw tr("The value is not found");
    }
}

void QConfiguration::setSpecifiedSettings()
{
    server.host = settings->value(QString::fromStdString(
                                      GetServerHostConfigPath().string())).toString();
    server.port = settings->value(QString::fromStdString(
                                      GetServerPortConfigPath().string())).toString();
    databaseName = settings->value(QString::fromStdString(
                                       GetDatabaseNameConfigPath().string())).toString();
}

void QConfiguration::setDefaultSettings()
{
    server.host = Config::server.host;
    server.port = Config::server.port;
    databaseName = Config::databaseName;
}

std::filesystem::path QConfiguration::GetServerHostConfigPath()
{
    return "server/host";
}

std::filesystem::path QConfiguration::GetServerPortConfigPath()
{
    return "server/port";
}

std::filesystem::path QConfiguration::GetDatabaseNameConfigPath()
{
    return "database/name";
}

QSettings *QConfiguration::GetSettings()
{
    return settings;
}
