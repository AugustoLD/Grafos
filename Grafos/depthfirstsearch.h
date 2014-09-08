#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

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
    void visit(Vertice *v);

signals:
    void colorChanged();

};

#endif // DEPTHFIRSTSEARCH_H
