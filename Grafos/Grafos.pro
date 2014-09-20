#-------------------------------------------------
#
# Project created by QtCreator 2014-06-26T11:25:21
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Grafos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    depthfirstsearch.cpp \
    dijkstra.cpp \
    prim.cpp \
    breadthfirstsearch.cpp \
    kruskal.cpp \
    path.cpp \
    topologica.cpp \
    fordfulkerson.cpp

HEADERS  += mainwindow.h \
    aresta.h \
    grafo.h \
    vertice.h \
    depthfirstsearch.h \
    dijkstra.h \
    prim.h \
    breadthfirstsearch.h \
    kruskal.h \
    path.h \
    topologica.h \
    fordfulkerson.h

FORMS    += mainwindow.ui
