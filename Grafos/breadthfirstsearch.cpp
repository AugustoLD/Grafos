#include "breadthfirstsearch.h"

void BreadthFirstSearch::bfs() {
        f = new Fila();
        Vertice **v = g->getVertice();
        Vertice *v_aux, *v_atual;
        Aresta *a;
        int i;

        for (i = 0; i < g->getVerticeCount(); i++) {
            v[i]->setPai(NULL);
            v[i]->setCor(Qt::white);
            v[i]->setD(0);
        }

        v[0]->setPai(NULL);
        v[0]->setCor(Qt::gray);
        v[0]->setD(0);

        f->append(v[0]);

        while(!f->isEmpty()) {
            v_atual = (Vertice*) f->removeInicio();
            for(a = v_atual->getAresta(); a != NULL; a = a->getNext()) {
                v_aux = v[a->getIdV2()];
                if(v_aux->getCor() == Qt::white) {
                    v_aux->setCor(Qt::gray);
                    v_aux->setPai(v_atual);
                    v_aux->setD(v_atual->getD()+1);
                    f->append(v_aux);
                }
                v_atual->setCor(Qt::black);
            }
            delete f;
        }
    }

