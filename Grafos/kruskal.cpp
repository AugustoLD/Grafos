/*void kruskal(Aresta *a){
       VKruskal = new Vertice *[n_vertices];
       for(int i=0;i<n_vertices;i++){
           VKruskal[i] = new Vertice(i,Vertice[i]->getNome(),Vertice[i]->getX(),Vertice[i]->getY());
       }

       int na = 0;
       while((na-1 < n_vertices) && (a != null)){
           h = a;
           a = a->getNext();
           V1 = VKruskal[a->getIdV1()];
           V2 = VKruskal[a->getIdV2()];
           if(!find(V1,V2)){
               V1->addAresta(a->getIdV1(),a->getIdV2(),a->getW());
               V2->addAresta(a->getIdV2(),a->getIdV1(),a->getW());
               UNIAO(V1,V2); //usa split se usar string, lista...
               na++;
           }
           a = a->getNext();
       }
   }
*/
