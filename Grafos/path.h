#ifndef PATH_H
#define PATH_H

#include <QObject>
#include "grafo.h"

class Path : public QObject
{
    Q_OBJECT
public:
    explicit Path(QObject *parent = 0);
    static QString getPath(Grafo *g, int index);
    static QString topologicListToString(QList<Vertice *> lista);

signals:

public slots:

};

#endif // PATH_H
