// definição das funções declaradas em FILA.h

#include <stdio.h>
#include <stdlib.h>
#include "TAD_FILA.h"

Fila* cria_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
    }
    return f;
}

int fila_vazia(Fila* f) {
    return (f->inicio == NULL);
}

void enqueue(Fila* f, int valor) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    novo->valor = valor;
    novo->prox = NULL;

    if (fila_vazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

int dequeue(Fila* f, int* removido) {
    if (fila_vazia(f)) {
        return 0; 
    }
    No* temp = f->inicio;
    *removido = temp->valor;
    f->inicio = temp->prox;
    if (f->inicio == NULL) {
        f->fim = NULL; 
    }
    free(temp);
    return 1; 
}

// Imprime fila
void imprime_fila(Fila* f) {
    No* atual = f->inicio;
    printf("Fila: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}


void libera_fila(Fila* f) {
    int x;
    while (dequeue(f, &x));
    free(f);
}
