// usando a TAD FILA
#include <stdio.h>
#include "TAD_FILA.h"

int main() {
    Fila* f = cria_fila();
    // testes
    enqueue(f, 10);
    enqueue(f, 20);
    enqueue(f, 30);
    imprime_fila(f);

    int removido;
    if (dequeue(f, &removido)) {
        printf("Removido: %d\n", removido);
    }
    imprime_fila(f);

    libera_fila(f);
    return 0;
}
