
TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
LIBS += -pthread
Qt += core
Qt -= gui

# use course library
include( concur2018lib/concur2018.pri )

# implement your code here:
SOURCES += \
    main.cpp


linux-g++ {
# linux only:
# make sure that we have input-files and outdir available when running
# from qtcreator (these must be in the build-directory where
# qtcreator runs our program)
datas.target = extra
datas.commands = \
    mkdir -p $$OUT_PWD/outdir ; cp -r $$PWD/inputs $$OUT_PWD

datas.depends =
QMAKE_EXTRA_TARGETS += datas
PRE_TARGETDEPS = extra
}
