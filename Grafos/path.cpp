#include "path.h"

Path::Path(QObject *parent) :
    QObject(parent)
{
}

QString Path::getPath(Grafo *g, int index) {
    Vertice *v = g->getVertice()[index];
    QString path;
    while(v->getPai() != NULL) {
        path = v->getNome() + path;
        path = " --> " + path;
        v = v->getPai();
    }

    path = v->getNome() + path;

    return path;
}

QString Path::topologicListToString(QList<Vertice *> lista) {
   QString result = "";
   for(int i = 0; i < lista.size() - 1; i++){
       result += lista[i]->getNome() + " --> ";
   }
   result += lista[lista.size()-1]->getNome();

   return result;
}
