QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_unittesting.cpp \
    Models/user.cpp \
    Models/patient.cpp \
    Models/device.cpp \
    Models/system.cpp \
    Models/recording.cpp \
    Models/analysis.cpp

HEADERS += \
    Models/user.h \
    Models/patient.h \
    Models/device.h \
    Models/binarypatient.h \
    Models/system.h \
    globals.h \
    Exceptions/exceptionemptyform.h \
    Models/recording.h \
    Models/analysis.h \
    Exceptions/exceptioninvalidenumtype.h
