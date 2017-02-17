lessThan(QT_MAJOR_VERSION, 5): error("requires Qt 5")
lessThan(QT_MINOR_VERSION, 8): error("requires Qt 5.8")

QT += core
QT -= gui

CONFIG += c++11

TARGET = evensimplerapp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
