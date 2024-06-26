QT       += core gui
QT 	 += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Proyecto_informatica
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ladrillo.cpp \
    Paleta.cpp \
    Pelota.cpp \
    iniciojuegowidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Ladrillo.h \
    Paleta.h \
    Pelota.h \
    iniciojuegowidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc
