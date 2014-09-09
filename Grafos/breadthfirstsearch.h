#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"
#include "fila.h"

class BreadthFirstSearch : public QThread
{
    Q_OBJECT
public:
    void setGrafo(Grafo * g) {this->g = g;}

    void run() {
        bfs();
    }

private:
    int tempo;
    Grafo *g;
    Fila *f;
    void bfs();

signals:
    void colorChanged();

};


#endif // BREADTHFIRSTSEARCH_H