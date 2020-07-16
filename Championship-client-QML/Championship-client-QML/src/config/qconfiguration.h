#ifndef QCONFIGURATIONREADER_H
#define QCONFIGURATIONREADER_H

#include <QObject>
#include <QSettings>
#include <filesystem>
#include "../models/server.h"
#include <QDir>

namespace Config {
const Models::Server server {
    "127.0.0.1",
    "7777"
};

const QString databaseName = "db_championshipGame";
}

class QConfiguration : public QObject
{
private:
    static QConfiguration* configuration;
    explicit QConfiguration();
    ~QConfiguration() override;

public:
    QConfiguration(QConfiguration&) = delete;
    QConfiguration(QConfiguration&&) = delete;
    void operator=(QConfiguration&) = delete;
    void operator=(QConfiguration&&) = delete;

    static QConfiguration* GetConfig();
    std::filesystem::path GetServerHostConfigPath();
    std::filesystem::path GetServerPortConfigPath();
    std::filesystem::path GetDatabaseNameConfigPath();
    QSettings* GetSettings();
    Models::Server GetServer() const;
    QString GetDatabaseName();

private:
    QSettings *settings = nullptr;
    Models::Server server;
    QString databaseName;

    void loadSettings();
    void saveSettings();
    void setDefaultSettings();
    void setSpecifiedSettings();
    void containsSettingsValue(const QSettings* settings, const QString &key) const;
};

#endif // QCONFIGURATIONREADER_H
