#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "grafo.h"

#include <QPainter>
#include <QPaintEvent>
#include "depthfirstsearch.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

signals:
    void mostrar ( Grafo * );

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void mostrarGrafo ( Grafo * );

private slots:
    void on_actionLoad_triggered();
    void init();
    void paint();

private:
    Ui::MainWindow *ui;
    Grafo *grafo, *tmp;
    DepthFirstSearch *dfs;

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
