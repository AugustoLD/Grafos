void bfs(){
        if(size == 0 ) return;
        Fila *F = new Fila();
        Vertice *v, *va;
        Aresta *a;
        int i;

        for (i = 0; i<size;i++){
            //Vertice[i]->setPai(NULL);
            Vertice[i]->setCor(Qt::white);
            Vertice[i]->setD(0);
        }

        //Vertice[0]->setPai(NULL);
        Vertice[0]->setCor(Qt::gray);
        Vertice[0]->setD(0);

        F->push(Vertice[0]);

        while(!F->getIsEmpty()){
            v->F->removeInicio();
            for(a = v->getAresta();a != NULL;a = a->getNext()){
                va = a->getV2();
                if(va->getCor() == Qt::white){
                    va->setCor(Qt::gray);
                    //va->setPai(v);
                    va->setD(v->getD()+1);
                    F->appendVertice(va);
                }
                v->setCor(Qt::black);
            }
            delete F;
        }
    }
