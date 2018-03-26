TEMPLATE = app

TARGET = CQAsteroids

QT += widgets multimedia

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++14

INCLUDEPATH += \
. \
../../CQUtil/include \
../../CVFont/include \
../../CImageLib/include \
../../CFont/include \
../../CConfig/include \
../../CFile/include \
../../CMath/include \
../../CUtil/include \
../../CStrUtil/include \
../../COS/include \

SOURCES += \
CQAsteroids.cpp \
CAsteroidsBigRock.cpp \
CAsteroidsBigSaucer.cpp \
CAsteroidsBullet.cpp \
CAsteroids.cpp \
CAsteroidsMediumRock.cpp \
CAsteroidsObject.cpp \
CAsteroidsRock.cpp \
CAsteroidsSaucer.cpp \
CAsteroidsScore.cpp \
CAsteroidsShip.cpp \
CAsteroidsSmallRock.cpp \
CAsteroidsSmallSaucer.cpp \

HEADERS += \
CQAsteroids.h \
CAsteroidsBigRock.h \
CAsteroidsBigSaucer.h \
CAsteroidsBullet.h \
CAsteroids.h \
CAsteroidsLib.h \
CAsteroidsLibI.h \
CAsteroidsMediumRock.h \
CAsteroidsObject.h \
CAsteroidsRock.h \
CAsteroidsSaucer.h \
CAsteroidsScore.h \
CAsteroidsShip.h \
CAsteroidsSmallRock.h \
CAsteroidsSmallSaucer.h \
CAsteroidsTypes.h \

unix:LIBS += -lSDL2 -lSDL2_mixer
