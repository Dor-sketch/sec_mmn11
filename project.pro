TEMPLATE = app
TARGET = USocial
INCLUDEPATH += .

# Input
SOURCES += main.cpp \
    Media.cpp \
    Message.cpp \
    Post.cpp \
    User.cpp \
    USocial.cpp \
    USocialTester.cpp \
    MainWindow.cpp \

HEADERS += MainWindow.h \
    Media.hpp \
    Message.hpp \
    Post.hpp \
    User.hpp \
    USocial.hpp \
    USocialTester.hpp \


LIBS += -lfmt

QT += widgets