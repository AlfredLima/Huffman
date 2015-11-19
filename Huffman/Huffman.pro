#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T18:32:59
#
#-------------------------------------------------

QT       += core gui qml quick widgets

TARGET = Huffman
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    tree.cpp \
    read.cpp \
    list.cpp \
    node.cpp \
    huffman.cpp \
    dhuffman.cpp

HEADERS += \
    tree.h \
    read.h \
    list.h \
    node.h \
    huffman.h \
    dhuffman.h

RESOURCES += \
    gui.qrc \
    img.qrc
