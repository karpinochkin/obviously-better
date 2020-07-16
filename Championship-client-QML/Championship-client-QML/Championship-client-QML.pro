QT += quick
QT += core gui
QT += sql
QT += network
QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/config/qconfiguration.cpp \
        src/database/qdatabasecontroller.cpp \
        src/database/qdatabases.cpp \
        src/imageprovider.cpp \
        src/network/controllers/qcontestscontroller.cpp \
        src/network/controllers/qcontrollers.cpp \
        src/network/controllers/qmemberscontroller.cpp \
        src/network/controllers/qmembertypescontroller.cpp \
        src/network/controllers/qratingcontroller.cpp \
        src/network/qnetmanager.cpp \
        src/network/qrouters.cpp \
        src/network/requesters/qrequesters.cpp \
        src/qappstarter.cpp \
        src/qmiddlewareqml.cpp \
        src/tools/qplayoffhandler.cpp \
        src/tools/qpoweroftwo.cpp \
        src/tools/qprepareurl.cpp

RESOURCES += qml.qrc \
    images.qrc \
    sounds.qrc

TRANSLATIONS += \
    Championship-client-QML_ru_BY.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/config/qconfiguration.h \
    src/database/qdatabasecontroller.h \
    src/database/qdatabases.h \
    src/imageprovider.h \
    src/models/abstractmodel.h \
    src/models/contest.h \
    src/models/link.h \
    src/models/member.h \
    src/models/membertype.h \
    src/models/rating.h \
    src/models/router.h \
    src/models/server.h \
    src/network/controllers/qabstractcontroller.h \
    src/network/controllers/qcontestscontroller.h \
    src/network/controllers/qcontrollers.h \
    src/network/controllers/qmemberscontroller.h \
    src/network/controllers/qmembertypescontroller.h \
    src/network/controllers/qratingcontroller.h \
    src/network/links.h \
    src/network/qnetmanager.h \
    src/network/qrouters.h \
    src/network/requesters/qrequesters.h \
    src/qappstarter.h \
    src/qmiddlewareqml.h \
    src/tools/qplayoffhandler.h \
    src/tools/qpoweroftwo.h \
    src/tools/qprepareurl.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}


defineReplace(droidVersionCode) {
        segments = $$split(1, ".")
        for (segment, segments): vCode = "$$first(vCode)$$format_number($$segment, width=3 zeropad)"

        contains(ANDROID_TARGET_ARCH, arm64-v8a): \
            suffix = 1
        else:contains(ANDROID_TARGET_ARCH, armeabi-v7a): \
            suffix = 0
        # add more cases as needed

        return($$first(vCode)$$first(suffix))
}

VERSION = 1.2.3
ANDROID_VERSION_NAME = $$VERSION
ANDROID_VERSION_CODE = $$droidVersionCode($$ANDROID_VERSION_NAME)
