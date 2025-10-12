# lab_01.pro

TEMPLATE = app
TARGET = app.exe

OBJECTS_DIR = obj

CONFIG += c++20
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE += -O0

QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O
QMAKE_CFLAGS_RELEASE += -O0
QMAKE_CXXFLAGS += -std=c++20 -fconcepts-diagnostics-depth=2

# Исходные файлы
SOURCES += \
    src/main.cpp \
    \
    src/Defs/definitions.cpp \
    \
    src/IO/io.cpp \
    \
    src/Solution/solution.cpp \
    \
    src/Extras/extras.cpp \
    \

# Заголовочные файлы
HEADERS += \
    src/Defs/definitions.hpp \
    \
    src/Errors/err.hpp \
    \
    src/IO/io.hpp \
    \
    src/Solution/solution.hpp \
    \
    src/Extras/extras.hpp \
    \

# Пути для поиска заголовков
INCLUDEPATH += \
    . \
    src/Defs \
    src/Errors \
    src/IO \
    src/Solution \
    src/Extras

# Для генерации makefile
QMAKE_CLEAN += *.o