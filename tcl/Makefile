CDEBUG = -g
LDEBUG = -g

PROG = CTclAsteroids

CPP_SRC = \
CTclAsteroids.cpp \
CTclAsteroidsApp.cpp

TCL_FILES = CTclAsteroids.tcl

EXTRA_CFLAGS = \
-I$(INC_DIR)/CTclApp \
-I$(INC_DIR)/CXLib \
-I$(INC_DIR)/CSymbol2D \
-I$(INC_DIR)/CPixelClip \
-I$(INC_DIR)/CImageLib \
-I$(INC_DIR)/CFont \
-I$(INC_DIR)/CPen \
-I$(INC_DIR)/CBrush \
-I$(INC_DIR)/CFile \
-I$(INC_DIR)/CFileType \
-I$(INC_DIR)/CAlignType \
-I$(INC_DIR)/CMath \
-I$(INC_DIR)/CStrUtil \
-I$(INC_DIR)/CUtil \

LIBS = \
-lCAsteroidsLib -lCLFont \
-lCTclCanvasPixelRenderer \
-lCTclCanvas -lCTclApp -lCXLib -lCXLibPixelRenderer \
$(RENDERER_2D_LIBS) -lCXrtFont -lCImageLib -lCSymbol2D \
-lCImageLib -lCFont -lCConfig -lCMath -lCUtil -lCStrUtil -lCRegExp -lCGlob \
-lCAssert -lCFile -lCFileUtil -lCReadLine -lCHistory -lCEnv \
-lCOSTimer -lCOSUser -lCOSTime -lCOSRand -lCOSFile -lCOSNaN -lCOSSignal -lCOSProcess \
-lCFileParse -lCTempFile -lCWindow \
-lCRGBUtil -lCPrintF -lCTimer -lCStrNCase -lCRegExp \
$(TCL_LIBS) $(X11_LIBS) -lXss -lXft -lfontconfig \
-lreadline -lpthread -lcurses -lpng -ljpeg -ltre -ldl

EXTRA_DEPS = $(LIB_DIR)/libCAsteroidsLib.a \
             $(LIB_DIR)/libCTclCanvas.a

include $(MAKE_DIR)/bin.mk
