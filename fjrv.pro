includedir = include/
srcdir     = src/
bindir     = src/bin/
objdir     = src/obj/

QMAKE_CFLAGS += -I$${includedir}
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic

SOURCES = $${srcdir}fileHandler.cpp \
          $${srcdir}lex.cpp         \
          $${srcdir}main.cpp        \
          $${srcdir}token.cpp       

HEADERS = $${includedir}fileHandler.hpp \
          $${includedir}lex.hpp         \
          $${includedir}token.hpp       \
		      $${includedir}position.hpp    

TARGET = $${bindir}fjrv_compiler

OBJECTS_DIR = $${objdir}

CONFIG += c++11
