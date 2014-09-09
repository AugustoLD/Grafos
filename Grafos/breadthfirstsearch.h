#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"

class DepthFirstSearch : public QThread
{
    Q_OBJECT
public:
    void setGrafo(Grafo * g) {  this->g = g;}

    void run() {
        bfs();
    }

private:
    int tempo;
    Grafo *g;
    void bfs();
    void (Vertice *v);

signals:
    void colorChanged();

};


#endif // BREADTHFIRSTSEARCH_H
