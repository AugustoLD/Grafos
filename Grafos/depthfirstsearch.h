#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"

class DepthFirstSearch : public QThread
{
    Q_OBJECT
public:
    void setParameters(Grafo * g, int initial, int final) {
        this->g = g;
        this->initial = initial;
        this->final = final;
    }

    void run() {
        dfs();
    }

private:
    int tempo;
    int initial;
    int final;
    Grafo *g;
    void dfs();
    void visit(Vertice *v);

signals:
    void colorChanged();

};

#endif // DEPTHFIRSTSEARCH_H
