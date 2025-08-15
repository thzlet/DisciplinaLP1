// cabeçalho com as declarações de tipo, estruturas e protótipos;

#ifndef FILA_H
#define FILA_H

typedef struct no {
    int valor;         
    struct no* prox;
} No;

typedef struct {
    No* inicio;
    No* fim;
} Fila;

Fila* cria_fila();
int fila_vazia(Fila* f);
void enqueue(Fila* f, int valor);
int dequeue(Fila* f, int* removido);
void imprime_fila(Fila* f);
void libera_fila(Fila* f);

#endif
