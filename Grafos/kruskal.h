#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"

class Kruskal : public QThread
{
    Q_OBJECT
public:
    void setParameters(Grafo * g, int initial, QString final) {
        this->g = g;
        this->initial = initial;
        this->final = final.toUpper();
    }

    void run() {
        kruskal();
    }

private:
    int tempo;
    int initial;
    QString final;
    Grafo *g;
    Vertice **vKruskal;
    void kruskal();
    bool find(QString nome, QString L);
    bool join(QString L1, QString L2);

signals:
    void colorChanged();

};

#endif // KRUSKAL_H
