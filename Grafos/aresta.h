#ifndef ARESTA_H
#define ARESTA_H

#include <QDebug>
#include <QColor>

class Aresta : public QObject {
    Q_OBJECT

public:
    Aresta (int id1, int id2, int w) {
        this->id1  = id1; // origem
        this->id2  = id2; // destino
        this->w    = w;
        this->capacity = w;
        this->flow = 0;
        this->next = NULL;
    }

    static void append ( Aresta **aresta, int id1, int id2, int w ) {
        if (*aresta==NULL)
            *aresta = new Aresta ( id1, id2, w);
        else
            append( &(*aresta)->next, id1, id2, w );
    }

    QColor getColor() { return this->color; }
    int getW ()  { return this->w; }
    int getIdV1() { return this->id1; }
    int getIdV2() { return this->id2; }
    int getFlow() { return this->flow;}
    int getCapacity() { return this->capacity; }

    Aresta *getNext() { return this->next;  }

    void setColor(QColor color) { this->color = color; }
    void setFlow(int flow) { this->flow = flow; }
    void setCapacity(int capacity) { this->capacity = capacity; }
    void decreaseCapacity(int amount) { this->capacity -= amount; }
    void increaseFlow(int amount) { this->flow += amount; }

    ~Aresta() {
        qDebug() << "Excluindo aresta (" << id1 <<","<<id2<<"," << w << ")";
        if (this->next!=NULL)
            delete this->next;
    }

private:
    Aresta *next;
    QColor color;
    int id1;
    int id2;
    int w;
    int capacity;
    int flow;

};

#endif // ARESTA_H
