QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        botLib.cpp \
        carLib.cpp \
        gameLib.cpp \
        main.cpp \
        playerLib.cpp \
        speedometer.cpp \
        utils.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../../SDL2-2.0.12/x86_64-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../SDL2-2.0.12/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../SDL2-2.0.12/x86_64-w64-mingw32/include

win32: LIBS += -L$$PWD/../../SDL2_image-2.0.5/x86_64-w64-mingw32/lib/ -lSDL2_image

INCLUDEPATH += $$PWD/../../SDL2_image-2.0.5/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../SDL2_image-2.0.5/x86_64-w64-mingw32/include

win32: LIBS += -L$$PWD/../../SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib/ -lSDL2_mixer

INCLUDEPATH += $$PWD/../../SDL2_mixer-2.0.4/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../SDL2_mixer-2.0.4/x86_64-w64-mingw32/include

HEADERS += \
    Bot.h \
    Car.h \
    Player.h \
    Race.h \
    Direction.h \
    Race.h \
    Speedometer.h \
    Speedway.h \
    botLib.h \
    carLib.h \
    gameLib.h \
    playerLib.h \
    speedometerlib.h \
    utils.h



win32: LIBS += -L$$PWD/../../SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib/ -lSDL2_mixer

INCLUDEPATH += $$PWD/../../SDL2_mixer-2.0.4/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../SDL2_mixer-2.0.4/x86_64-w64-mingw32/include
