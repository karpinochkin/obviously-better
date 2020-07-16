#include "tst_qconfiguration.h"
#include "tst_qpreparerurl.h"
#include "tst_qrequesters.h"
#include "tst_qdatabases.h"
#include "tst_qcontrollers.h"
//#include "tst_qplayoffhandler.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
