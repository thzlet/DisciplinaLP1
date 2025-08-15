// cabeçalho com as declarações de tipo, estruturas e protótipos;

#ifndef FILA_H
#define FILA_H

typedef struct no { // cada elemento da fila eh um nó de lista encadeada
    int valor;         
    struct no* prox;
} No;

typedef struct {
    No* inicio; // ponteiro pro head
    No* fim; // ponteiro pro tail
} Fila;

Fila* cria_fila(); // inicializa uma fila vazia
int fila_vazia(Fila* f);
void enqueue(Fila* f, int valor); // novo elemento no final da fila
int dequeue(Fila* f, int* removido); // remove elemento do inicio da fila
void imprime_fila(Fila* f);
void libera_fila(Fila* f);

#endif
