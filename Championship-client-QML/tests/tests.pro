include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += thread
CONFIG += core
QT += widgets
QT += network
QT += testlib
QT += sql

HEADERS += \
        ../Championship-client-QML/src/config/qconfiguration.h \
        ../Championship-client-QML/src/database/qdatabasecontroller.h \
        ../Championship-client-QML/src/database/qdatabases.h \
        ../Championship-client-QML/src/models/abstractmodel.h \
        ../Championship-client-QML/src/models/contest.h \
        ../Championship-client-QML/src/models/link.h \
        ../Championship-client-QML/src/models/member.h \
        ../Championship-client-QML/src/models/membertype.h \
        ../Championship-client-QML/src/network/requesters/qrequesters.h \
        ../Championship-client-QML/src/models/rating.h \
        ../Championship-client-QML/src/models/router.h \
        ../Championship-client-QML/src/models/server.h \
        ../Championship-client-QML/src/network/controllers/qabstractcontroller.h \
        ../Championship-client-QML/src/network/controllers/qcontestscontroller.h \
        ../Championship-client-QML/src/network/controllers/qcontrollers.h \
        ../Championship-client-QML/src/network/controllers/qmemberscontroller.h \
        ../Championship-client-QML/src/network/controllers/qmembertypescontroller.h \
        ../Championship-client-QML/src/network/controllers/qratingcontroller.h \
        ../Championship-client-QML/src/network/links.h \
        ../Championship-client-QML/src/network/qnetmanager.h \
        ../Championship-client-QML/src/network/qrouters.h \
        ../Championship-client-QML/src/tools/qplayoffhandler.h \
        ../Championship-client-QML/src/tools/qpoweroftwo.h \
        ../Championship-client-QML/src/tools/qprepareurl.h \
        tst_qconfiguration.h \
        tst_qcontrollers.h \
        tst_qdatabases.h \
        tst_qplayoffhandler.h \
        tst_qpreparerurl.h \
        tst_qrequesters.h

SOURCES += \
        ../Championship-client-QML/src/config/qconfiguration.cpp \
        ../Championship-client-QML/src/database/qdatabasecontroller.cpp \
        ../Championship-client-QML/src/database/qdatabases.cpp \
        ../Championship-client-QML/src/network/requesters/qrequesters.cpp \
        ../Championship-client-QML/src/network/controllers/qcontestscontroller.cpp \
        ../Championship-client-QML/src/network/controllers/qcontrollers.cpp \
        ../Championship-client-QML/src/network/controllers/qmemberscontroller.cpp \
        ../Championship-client-QML/src/network/controllers/qmembertypescontroller.cpp \
        ../Championship-client-QML/src/network/controllers/qratingcontroller.cpp \
        ../Championship-client-QML/src/network/qnetmanager.cpp \
        ../Championship-client-QML/src/network/qrouters.cpp \
        ../Championship-client-QML/src/tools/qplayoffhandler.cpp \
        ../Championship-client-QML/src/tools/qpoweroftwo.cpp \
        ../Championship-client-QML/src/tools/qprepareurl.cpp \
        main.cpp
