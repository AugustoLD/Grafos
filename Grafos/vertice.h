#ifndef VERTICE_H
#define VERTICE_H

#include <QObject>
#include <QDebug>
#include <QColor>
#include "aresta.h"

#define INF 1000000

class Vertice : public QObject {
    Q_OBJECT

public:
    Vertice ( int id, QString nome, int x, int y ) {
        this->id     = id;
        this->nome   = nome;
        this->x      = x;
        this->y      = y;
        this->ti     = 0;
        this->to     = 0;
        this->d      = 0;
        this->n_a    = 0;
        this->cor    = Qt::white;
        this->aresta = NULL;

    }

    void add ( int id1, int id2, int w ) { Aresta::append( &aresta, id1, id2, w ); }
    Aresta *getAresta ()                 { return this->aresta; }
    QString getNome ()                   { return this->nome; }
    int     getId()                      { return this->id;   }
    int     getX ()                      { return this->x;    }
    int     getY ()                      { return this->y;    }
    int     getD ()                      { return this->d;    }
    QColor  getCor ()                    { return this->cor;  }
    Vertice*  getPai ()                  { return this->pai;  }
    QString getKruskalList()             { return this->kruskalList; }
    void setCor(QColor cor)              { this->cor = cor;   }
    void setPai(Vertice *pai)            { this->pai = pai;   }
    void setTi(int ti)                   { this->ti = ti;     }
    void setTo(int to)                   { this->to = to;     }
    void setD(int d)                     { this->d = d;       }
    void setKruskalList(QString kruskalList) { this->kruskalList = kruskalList; }

    ~Vertice() {
        qDebug() << "Excluindo vertice " << nome;
        if (this->aresta!=NULL)
            delete this->aresta;
    }

protected:
    int id; // Index do v�rtice no vetor
    QString nome;
    int ti; // tempo de entrada
    int to; // tempo de saida
    int d;  // dist�ncia
    int n_a; // n�mero de arestas
    QColor cor; // cor do v�rtice
    Aresta *aresta;
    Vertice *pai;
    QString kruskalList;

    int x;
    int y;

};

#endif // VERTICE_H
