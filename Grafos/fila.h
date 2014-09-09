#ifndef FILA_H
#define FILA_H

#include "aresta.h"
#include "vertice.h"

class Elemento {
protected:
    void *elemento;
    Elemento *next;
public:
    Elemento ( void *e ) {
        this->elemento = e;
    }

    void setNext ( Elemento *n ) { this->next = n;        }
    Elemento *getNext ()         { return this->next;     }
    void *getElemento ()         { return this->elemento; }

    ~Elemento  () {
        if (next!=NULL)
            delete next;
    }
};

class Fila : public QObject {
    Q_OBJECT

public:
    Fila() {
       first = NULL;
       last  = NULL;
    }

    void append  ( void *v ) {
        Elemento *e = new Elemento(v);
        if (first==NULL)
            last=e;
        else
            e->setNext (first);

        first = e;
    }

    void * removeInicio() {
        void *e = NULL;
        Elemento *tmp;
        if (first!=NULL) {
            e = first->getElemento();
            tmp = first;
            first=first->getNext();
            delete tmp;
        };
        return e;
    }

    bool isEmpty() {
        if(first == NULL) {
            return true;
        } else {
            return false;
        }
    }

    ~Fila () {
        if (first!=NULL) delete first;
    }


private:
    Elemento *first;
    Elemento *last;
};

#endif // FILA_H
