#ifndef GRAFO_H
#define GRAFO_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QColor>

#include "vertice.h"

class Grafo : public QObject {
    Q_OBJECT

public:
    Grafo ( int n, QObject *parent ) : QObject(parent)  {
        aresta      = NULL;
        this->max   = n;
        this->size  = 0;
        vertice     = new Vertice*[max];
        for (int i=0; i<max; i++)
            vertice[i] = NULL;

    }

    void add ( QString nome, int x, int y ) {
        if (size<max) {
            qDebug() << "Adicionando vertice " << nome;
            vertice[size] = new Vertice(size, nome.toUpper(), x, y);
            size++;
        } else
            qDebug() << "Número de vertices maior que o informado!";
    }

    bool addAresta ( QString source, QString target, int w ) {
        int s = getVerticeIndex(source);
        int t = getVerticeIndex(target);
        if ((s==-1) || (t==-1)) {
            qDebug() << "Vertice de [origem|destino] não encontrado: " << source << ", " << target;
            return false;
        }
        Aresta::append( &aresta, s, t, w );
        vertice[s]->add( s, t, w);
        return true;
    }

    Aresta *getAresta()        { return this->aresta; }

    Vertice **getVertice ()    { return this->vertice; }
    int     getVerticeCount()  { return this->size; }

    ~Grafo ( ) {
        qDebug() << "Eliminando o grafo";
        for (int i=0; i<size; i++)
            delete vertice[i];
        delete [] vertice;
    }


protected:
    Vertice **vertice;
    Aresta *aresta;
    int max;
    int size;

    int getVerticeIndex ( QString nome ) {
        for (int i=0; i<size; i++)
            if ((vertice[i]!=NULL) && (vertice[i]->getNome()==nome.toUpper()))
                return i;
        return -1;
    }


};



#endif // GRAFO_H
