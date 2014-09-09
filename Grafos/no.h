#ifndef NO_H
#define NO_H

#include <QString>
#include <QDebug>

#include "aresta.h"

#define INFINITO 1000

class No {
public:
    QString nome;        /// Nome do no
    No *pai;             /// Ponteiro para o pai do no
    int d;               /// T1 - Marcador de entrada
    int f;               /// T2 - Marcador de saida
    bool visitando;
    Qt::GlobalColor  cor; /// Cor de apresentacao do no
    No *next;            /// Endereco do proximo
    ListaArestas *adjs;  /// Lista de adjacencias

    QString nosConectados;

    int x, y;            /// Coordenadas para exibi��o na tela

    No ( QString nome, int x, int y ) {
        this->nome = nome;
        this->nosConectados = nome;
        this->x    = x;
        this->y    = y;
        this->pai  = NULL;
        this->d    = INFINITO;
        this->f    = INFINITO;
        this->cor  = Qt::white;
        this->next = NULL;
        this->visitando = false;
        this->adjs = new ListaArestas();
    }

    void addAdj ( Aresta *aresta ) {
        this->adjs->insert ( aresta );
    }

    No * clone () {
        return new No(nome, x, y );
    }

};

class ListaNos {
private:
        No *header, *footer;

public:
    ListaNos () { header=footer=NULL; }

    // Insere no fim
    void append ( No *no ) {
        if (header==NULL)
            header = no;
        else
            footer->next = no;

        footer = no;
    }

    No* getNos ( ) {
        return header;
    }

    No* find ( QString nome  ){
        for (No *h = header; h!=NULL; h=h->next ) {
            if (h->nome.toUpper()==nome.toUpper())
                return h;
        }
        qDebug() << "N� [" + nome + "] n�o encontrado!" << endl;
        return NULL;
    }

    ~ListaNos() {
        for ( No * h=header; h!=NULL; h=h->next) {
            header = header->next;
            delete h;
            h=header;
        }
    }

};

#endif // NO_H
