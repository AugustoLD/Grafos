#ifndef LISTA_H
#define LISTA_H

#include "no.h"
#include "fila.h"

class Lista {
public:
    Lista () { header=footer=NULL; }

    bool isEmpty ( ) { return header==NULL; }

    // Insere no fim
    void append ( No *no ) {
        Element *h = new Element ( no );
        if (header==NULL)
            header = h;
        else
            footer->next = h;

        footer = h;
    }

    void insertBegin ( No *no ) {
        Element *h = new Element ( no );
        h->next = header;
        header = h;
        if (footer==NULL)
            footer = h;
    }

    QString toString () {
        Element *p=header;
        QString s="";
        while (p!=NULL) {
            s += p->no->nome + " - ";
            p = p->next;
        }
        return s;
    }

    // Remove o n� que tem menor peso
    void * removeLighter ( ) {
        if (header==NULL)
            return NULL;

        Element *ant=NULL, *atual, *antmenor=NULL, *menor;
        No *no=NULL;
        atual = header;
        menor = header;

        while (atual!=NULL) {
            if (atual->no->d < menor->no->d) {
                antmenor = ant;
                menor = atual;
            }
            ant = atual;
            atual = atual->next;
        }
        if (antmenor!=NULL)
            antmenor->next = menor->next;
        else
            header = menor->next;

        if (footer==menor)
            footer=antmenor;

        no = menor->no;
        delete menor;
        return no;
    }

    ~Lista() {
        for ( Element * h=header; h!=NULL; h=h->next) {
            header = header->next;
            delete h;
            h=header;
        }
    }

    void Clear() {
        for ( Element * h=header; h!=NULL; h=h->next) {
            header = header->next;
            delete h;
            h=header;
        }
        header = footer = NULL;
    }

private:
    Element *header, *footer;

};

#endif // LISTA_H
