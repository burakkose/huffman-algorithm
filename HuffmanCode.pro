#-------------------------------------------------
#
# Project created by QtCreator 2013-11-28T21:34:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HuffmanCode
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    encode.cpp \
    decode.cpp \
    huffmanTree.cpp

HEADERS  += mainwindow.h \
    encode.h \
    decode.h \
    huffmanTree.h

FORMS    += mainwindow.ui \
    encode.ui \
    decode.ui

RESOURCES += \
    image.qrc
