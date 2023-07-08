QT       += core gui
QT+=multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Button_Ship.cpp \
    end.cpp \
    levelselection.cpp \
    main.cpp \
    myanimation.cpp \
    mymenu.cpp \
    mypushbutton.cpp \
    pause.cpp \
    w_battle.cpp \
    worship.cpp

HEADERS += \
    Button_Ship.h \
    end.h \
    levelselection.h \
    myanimation.h \
    mymenu.h \
    mypushbutton.h \
    pause.h \
    w_battle.h \
    worship.h

FORMS += \
    end.ui \
    levelselection.ui \
    mymenu.ui \
    pause.ui \
    w_battle.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
