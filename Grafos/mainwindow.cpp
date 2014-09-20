#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "grafo.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPoint>
#include "path.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    this->ui->toolBar->addWidget(this->ui->algorithmLabel);
    this->ui->toolBar->addWidget(this->ui->algorithmComboBox);
    this->ui->toolBar->addSeparator();
    this->ui->toolBar->addWidget(this->ui->labelInicial);
    this->ui->toolBar->addWidget(this->ui->cbOrigem);
    for(int i = 0; i < 5; i++) this->ui->toolBar->addSeparator();
    this->ui->toolBar->addWidget(this->ui->startButton);
    this->ui->statusBar->addWidget(this->ui->labelFinal);
    this->ui->statusBar->addWidget(this->ui->cbFinal);
    this->ui->statusBar->addWidget(this->ui->textEdit, 5);
    this->ui->statusBar->addWidget(this->ui->pathButton, 2);

    this->ui->algorithmComboBox->addItem("Depth First Search");
    this->ui->algorithmComboBox->addItem("Breadth First Search");
    this->ui->algorithmComboBox->addItem("Topologic Ordenation");
    this->ui->algorithmComboBox->addItem("Prim");
    this->ui->algorithmComboBox->addItem("Dijkstra");
    this->ui->algorithmComboBox->addItem("Kruskal");
    this->ui->algorithmComboBox->addItem("Ford-Fulkerson");

    isFordFulkerson = false;

    QMainWindow::paintEvent(new QPaintEvent(this->geometry()));
    this->grafo=this->tmp=NULL;
    connect( this, SIGNAL (mostrar(Grafo * )), this, SLOT(mostrarGrafo(Grafo*)) );
    connect(ui->startButton, SIGNAL(clicked()), SLOT(init()));
    connect(this->ui->pathButton, SIGNAL(clicked()), SLOT(showPath()));

}

void MainWindow::paintEvent(QPaintEvent *) {
    if (this->tmp==NULL) return;

    QPainter painter(this);

    Vertice **vertice = tmp->getVertice();
    Vertice *v, *v1, *v2;
    Aresta *a;
    int n = tmp->getVerticeCount();

    // Pintar primeiramente as arestas

    for (int i=0; i<n; i++) {
        if(isFordFulkerson) a = vertice[i]->getAresta();
        else a = tmp->getAresta();
        while (a!=NULL) {
            v1 = vertice[a->getIdV1()];
            v2 = vertice[a->getIdV2()];
            painter.setPen(a->getColor());
            QPoint p1 = QPoint (v1->getX(), v1->getY());
            QPoint p2 = QPoint (v2->getX(), v2->getY());
            painter.drawLine(p1, p2);
            int x = (p1.x()+p2.x())/2;
            int y = (p1.y()+p2.y())/2;
            QRect rect ( x-4,  y, x,  y );
            if(isFordFulkerson) {
                 painter.drawText (rect, QString::number(a->getFlow()) + "/" +
                                   QString::number(a->getCapacity()));
            } else {
                painter.drawText (rect, QString::number(a->getW()));
            }
            a = a->getNext();
        }
    }
    for (int i=0; i<n; i++) {
        v=vertice[i];
        painter.setBrush ( v->getCor() );
        painter.setPen((v->getCor()==Qt::black)? Qt::white : Qt::black);
        painter.drawEllipse( v->getX()-20,  v->getY()-20, 40, 40 );
        QRect r1 ( v->getX()-4,  v->getY()-8, v->getX()+4,  v->getY()+8 );
        painter.drawText( r1, v->getNome() );
    }
}

void MainWindow::mostrarGrafo ( Grafo *g ) {
    this->tmp=g;
    update ();
}

void MainWindow::on_actionLoad_triggered() {
    QDir::setCurrent("../files");
    qDebug() << QDir::currentPath();
    QString filename =  QFileDialog::getOpenFileName( this, tr("Open Document"),
                                                     QDir::currentPath(),
                                                     tr("Document files (*.txt);All files (*.*)"), 0,
                                                     QFileDialog::DontUseNativeDialog );
    if( !filename.isNull() ) {
        qDebug() << filename;

        QFile file( filename );
        if(!file.open(QIODevice::ReadOnly)) {
            qDebug() << "error " << file.errorString();
            QMessageBox::critical(this, "Lendo arquivo", "Erro na leitura do arquivo selecionado");
            return;
        }
        QTextStream in(&file);
        QString line;
        QStringList sl;

        if (grafo!=NULL) delete grafo;
        line = in.readLine();     // número de vértices
        grafo = new Grafo(line.toInt(), this);

        ui->cbOrigem->clear();
        ui->cbFinal->clear();
        bool loadvertice = true;
        while(!in.atEnd() && loadvertice) {
            line = in.readLine();
            if (line.length()>0 && line.at(0)!='(') {
                //line = 1,100,100 ==> nome vértice, coordenada x, coordenada y
                sl = line.split(",");
                if (sl.count()==3) {
                    grafo->add( sl[0], sl[1].toInt(), sl[2].toInt() );
                    ui->cbOrigem->addItem( sl[0] );
                    ui->cbFinal->addItem( sl[0] );
                } else {
                    QMessageBox::critical(this,"Carregar vértices", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
                    return;
                }
            } else
                loadvertice = false;
        }
        if (!in.atEnd()) {
            do {
                // line = (1,2,5)
                line = line.mid(1, line.length() -2 );

                // line = 1,2,5
                //qDebug() << line;
                sl = line.split(",");
                if (sl.count()==3)
                    grafo->addAresta(sl[0], sl[1], sl[2].toInt() );
                else {
                    QMessageBox::critical(this,"Carregar arestas", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
                    return;
                }

                line = in.readLine();
            } while(!in.atEnd());
        }

        qDebug() << "Carregado com sucesso!";
        file.close();

        emit mostrar ( grafo );
        ui->startButton->setDisabled(false);
    }
}

void MainWindow::init() {
    int selectedAlgorithm = this->ui->algorithmComboBox->currentIndex();
    this->ui->startButton->setDisabled(true);
    this->ui->pathButton->setDisabled(true);

    Aresta *a = grafo->getAresta();
    while(a != NULL) {
        a->setColor(Qt::black);
        a = a->getNext();
    }
    isFordFulkerson = false;

    switch (selectedAlgorithm) {
    case 0:
        dfs = new DepthFirstSearch();
        dfs->setParameters(grafo, ui->cbOrigem->currentIndex());
        dfs->start();
        connect(dfs, SIGNAL(colorChanged()), SLOT(update()));
        connect(dfs, SIGNAL(finished()), SLOT(freeButtons()));
        break;
    case 1:
        bfs = new BreadthFirstSearch();
        bfs->setGrafo(grafo, ui->cbOrigem->currentIndex());
        bfs->start();
        connect(bfs, SIGNAL(colorChanged()), SLOT(paint()));
        connect(bfs, SIGNAL(finished()), SLOT(freeButtons()));
        break;
    case 2:
        topologic = new Topologica();
        topologic->setParameters(grafo, ui->cbOrigem->currentIndex());
        topologic->start();
        connect(topologic, SIGNAL(colorChanged()), SLOT(paint()));
        connect(topologic, SIGNAL(finished()), SLOT(freeButtons()));
        break;
    case 3:
        prim = new Prim();
        prim->setParameters(grafo, ui->cbOrigem->currentIndex());
        prim->start();
        connect(prim, SIGNAL(colorChanged()), SLOT(paint()));
        connect(prim, SIGNAL(finished()), SLOT(freeButtons()));
        break;
    case 4:
        dijkstra = new Dijkstra();
        dijkstra->setParameters(grafo, ui->cbOrigem->currentIndex());
        dijkstra->start();
        connect(dijkstra, SIGNAL(colorChanged()), SLOT(paint()));
        connect(dijkstra, SIGNAL(finished()), SLOT(freeButtons()));
        break;
    case 5:
        kruskal = new Kruskal();
        kruskal->setParameters(grafo, ui->cbOrigem->currentIndex());
        kruskal->start();
        connect(kruskal, SIGNAL(colorChanged()), SLOT(paint()));
        connect(kruskal, SIGNAL(finished()), SLOT(freeButtons()));
        break;
    case 6:
        fordFulkerson = new FordFulkerson();
        fordFulkerson->setParameters(grafo, ui->cbOrigem->currentIndex(), ui->cbFinal->currentIndex());
        fordFulkerson->start();
        isFordFulkerson = true;
        connect(fordFulkerson, SIGNAL(colorChanged()), SLOT(paint()));
        connect(fordFulkerson, SIGNAL(finished()), SLOT(freeButtons()));
        break;
    }
}

void MainWindow::showPath() {
    int selectedAlgorithm = this->ui->algorithmComboBox->currentIndex();

    switch (selectedAlgorithm) {
    case 0:
        this->ui->textEdit->setText(Path::getPath(grafo, this->ui->cbFinal->currentIndex()));
        break;
    case 1:
        this->ui->textEdit->setText(Path::getPath(grafo, this->ui->cbFinal->currentIndex()));
        break;
    case 2:
        this->ui->textEdit->setText(Path::topologicListToString(topologic->getList()));
        break;
    case 3:
        this->ui->textEdit->setText(Path::getPath(grafo, this->ui->cbFinal->currentIndex()));
        break;
    case 4:
        this->ui->textEdit->setText(Path::getPath(grafo, this->ui->cbFinal->currentIndex()));
        break;
    }
}

void MainWindow::freeButtons()
{
    this->ui->startButton->setDisabled(false);
    this->ui->pathButton->setDisabled(false);
}


void MainWindow::paint() {
    this->tmp = grafo;
    update();
}

MainWindow::~MainWindow() {
    if (grafo!=NULL)
        delete grafo;
    delete ui;
}
