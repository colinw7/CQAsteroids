TEMPLATE = app

TARGET = CQAsteroids

QT += widgets multimedia

DEPENDPATH += .

MOC_DIR = .moc

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

QMAKE_CXXFLAGS += -std=c++17

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
main.cpp \
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
CAsteroidsExplosion.cpp \
CAsteroidsShapeMgr.cpp \
CAsteroidsRenderer.cpp \
CQCanvas2D.cpp \
CQSound.cpp \
CSDLSound.cpp \

HEADERS += \
CQAsteroids.h \
CAsteroidsBigRock.h \
CAsteroidsBigSaucer.h \
CAsteroidsBullet.h \
CAsteroids.h \
CAsteroidsMediumRock.h \
CAsteroidsObject.h \
CAsteroidsRock.h \
CAsteroidsSaucer.h \
CAsteroidsScore.h \
CAsteroidsShip.h \
CAsteroidsSmallRock.h \
CAsteroidsSmallSaucer.h \
CAsteroidsExplosion.h \
CAsteroidsShapeMgr.h \
CAsteroidsRenderer.h \
CQCanvas2D.h \
CQSound.h \
CSDLSound.h \

unix:LIBS += \
-L../../CVFont/lib \
-L../../CQUtil/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CConfig/lib \
-L../../CFileUtil/lib \
-L../../CFile/lib \
-L../../CMath/lib \
-L../../CStrUtil/lib \
-L../../CRegExp/lib \
-L../../CUtil/lib \
-L../../COS/lib \
-lCVFont -lCQUtil -lCImageLib -lCFont \
-lCConfig -lCFileUtil -lCFile -lCMath -lCStrUtil -lCRegExp -lCUtil -lCOS \
-lSDL2 -lSDL2_mixer -lpng -ljpeg -ltre
