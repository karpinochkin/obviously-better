#ifndef TST_QCONFIGURATION_H
#define TST_QCONFIGURATION_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#define private public
#include "../Championship-client-QML/src/config/qconfiguration.h"

using namespace testing;

TEST(qconfiguration, containsSettingsValue)
{
    auto config = std::make_unique<QConfiguration>();
    bool result;
    try {
        config->containsSettingsValue(config->GetSettings(), QString::fromStdString(
                                          config->GetServerHostConfigPath().string()));
        config->containsSettingsValue(config->GetSettings(), QString::fromStdString(
                                          config->GetServerPortConfigPath().string()));
        result = true;
    } catch (...) {
        result = false;
    }

    ASSERT_TRUE(result);

    try {
        config->containsSettingsValue(config->GetSettings(), "wrong_path");
        config->containsSettingsValue(config->GetSettings(), "wrong_path");
        result = true;
    } catch (...) {
        result = false;
    }

    ASSERT_FALSE(result);
}

#endif // TST_QCONFIGURATION_H
