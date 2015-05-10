#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T17:18:02
#
#-------------------------------------------------

QT       += core \
              xml \
              widgets

QT       -= gui

TARGET = ProjectCalendar
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    tacheunitaire.cpp \
    tachemanager.cpp \
    tacheEditeur.cpp \
    tachecomposite.cpp \
    tache.cpp \
    projetmanager.cpp \
    projet.cpp \
    programmationmanager.cpp \
    programmation.cpp \
    precedencemanager.cpp \
    precedence.cpp \
    calendar.cpp \
    timing.cpp

HEADERS += \
    tache.h \
    tachecomposite.h \
    tacheunitaire.h \
    tachemanager.h \
    tacheEditeur.h \
    projetmanager.h \
    projet.h \
    programmationmanager.h \
    programmation.h \
    precedencemanager.h \
    precedence.h \
    calendar.h \
    timing.h
