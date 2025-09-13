// questão 1 (a)
char* voltar_pagina(Pilha* undo, Pilha* redo) { // verificando se o undo está vazio
    if (pilha_vazia(undo)) { // se a pilha estiver vazia o elemento do topo eh nulo
        return NULL;
    }

    char* atual = (char*) pilha_desempilhar(undo);  // passo 1: desempilha o UNDO ; remove e retorna o elemento no topo de undo
    pilha_empilhar(redo, atual); // página atual em REDO ; resultado armazenado em atual

    if (!pilha_vazia(undo)) {  // colocando a pág atual no topo do undo
        return (char*) pilha_topo(undo);
    }

    return NULL;
}

// questão 1 (b) 

char* avancar_pagina(Pilha* undo, Pilha* redo) {
    if(pilha_vazia(redo)) { 
        return NULL;
    } 

    char* proxima = (char*) pilha_desempilhar(redo); 

    pilha_empilhar(undo, proxima);

    return proxima;
}

// questao 2

Listagen* lstgen_filtra(Listagen* l, int(criterio)(void)) {
    Listagen* nova = lstgen_cria(); // lista vazia
    Listagen* p;

    for(p - l; p != NULL; p = p -> prox) {
        if(criterio(p->info)) {
            nova = lstgen_insere(nova, p->info)
        }
        
    }

    return nova;
}