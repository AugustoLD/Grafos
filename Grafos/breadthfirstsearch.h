#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"

class BreadthFirstSearch : public QThread
{
    Q_OBJECT
public:
    void setGrafo(Grafo * g, int initial, int final) {
        this->g = g;
        this->initial = initial;
        this->final = final;
    }

    void run() {
        bfs();
    }

private:
    int tempo;
    int initial;
    int final;
    Grafo *g;
    void bfs();

signals:
    void colorChanged();

};


#endif // BREADTHFIRSTSEARCH_H
