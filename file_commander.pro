#-------------------------------------------------
#
# Project created by QtCreator 2018-09-03T09:53:39
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = file_commander
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
} else: DESTDIR = build/release

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    widgets/panelwidget.cpp \
    widgets/paneltablewidget.cpp \
    windows/createpathdialog.cpp \
    windows/removepathdialog.cpp \
    windows/copyfiledialog.cpp \
    controllers/processcopyfile.cpp \
    windows/createfiledialog.cpp \
    windows/finddialog.cpp

HEADERS += \
        mainwindow.h \
    widgets/panelwidget.h \
    widgets/paneltablewidget.h \
    windows/createpathdialog.h \
    windows/removepathdialog.h \
    windows/copyfiledialog.h \
    controllers/processcopyfile.h \
    windows/createfiledialog.h \
    windows/finddialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
