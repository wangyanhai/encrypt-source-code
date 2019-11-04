TEMPLATE = app
TARGET = translate
CONFIG += console

DEPENDPATH += .
INCLUDEPATH += .
QMAKE_LEX = flex
QMAKE_YACC = bison
#unix:QMAKE_YACCFLAGS = -o graphlang.tab.c --defines=graphlang.tab.h
#win32:QMAKE_YACCFLAGS = -o y.tab.c --defines=y.tab.h
win32:QMAKE_LEXFLAGS = --nounistd --c++ --outfile=lex.translate.c
# Input
LEXSOURCES += translate.l 
#YACCSOURCES += graphlang.y
HEADERS +=	util.h \
			translate.h 
			
SOURCES += 	main.cpp \
			util.cpp \
			translate.cpp 

#LIBS += -lIECCommon -lCompilerCommon

