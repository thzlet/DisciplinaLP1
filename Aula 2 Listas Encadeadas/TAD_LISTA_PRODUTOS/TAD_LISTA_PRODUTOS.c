#include "TAD_LISTA_PRODUTOS.h"
#include <stdlib.h> //malloc, free, exit..

Lista* lst_cria(void){ // retorna o ponteiro pro tipo lista
    return NULL; // não há nó
}

Lista* lst_novo_elemento(void){ // criando nó e retornando um ponteiro pra ele
    Lista* novo_elemento = (Lista*)malloc(sizeof(Lista));  // alocação dinamica
    
    if(novo_elemento == NULL){ // verificando se foi alocado
        printf("Não temos memória suficiente...");
        exit(1);
    }

    novo_elemento->prox = NULL; // inicializa o ponteiro prox para NULL;

    printf("## Cadastro de Produto ##\n");
    printf("id: ");
    scanf("%d%*c", &novo_elemento->id);
    printf("Descrição: ");
    scanf(" %80[^\n]", novo_elemento->descricao);
    printf("Estoque: ");
    scanf(" %f%*c", &novo_elemento->estoque);
    printf("Unidade: ");
    scanf(" %30[^\n]%*c", novo_elemento->unidade);
    printf("Preço: ");
    scanf(" %f%*c", &novo_elemento->preco);

    return novo_elemento; // nó recem alocado 

}

Lista* lst_insere(Lista* cabeca_da_lista, Lista* novo_elemento){
    novo_elemento->prox = cabeca_da_lista; // o prox do novo nó aponta para a cabeça antiga
    return novo_elemento; 
}

Lista* lst_retira_id(Lista* cabeca_da_lista, int id){
    Lista* ant = NULL; // nó anterior ao atual
    Lista* p = cabeca_da_lista; // percorre a lista a partir da cabeça

    while(p != NULL && p->id != id){ 
        ant = p; // guarda o anterior 
        p = p->prox; // avança para o proximo nó
    }

    if (p != NULL){

        if(ant == NULL){
            cabeca_da_lista = p->prox; // remove a cabeça
            free(p);
        }
        else{
            ant->prox = p->prox; // liga o anterior ao próximo do atual
            free(p);
        }
    }

    return cabeca_da_lista;
}

Lista* lst_busca_id(Lista* cabeca_da_lista, int id){
    Lista* p = cabeca_da_lista;

    while(p != NULL && p->id != id)
        p = p->prox;

    return p;

}

void lst_imprime(Lista* cabeca_da_lista){
    Lista* elemento;

    printf("\n### LISTA DE PRODUTOS ###\n");

    for(elemento = cabeca_da_lista; elemento != NULL; elemento = elemento->prox){
        printf("## Produto [%d] ##\n", elemento->id);
        printf("Descrição: %s\n", elemento->descricao);
        printf("Estoque: %.2f\n", elemento->estoque);
        printf("Unidade: %s\n", elemento->unidade);
        printf("Preço: %.2f\n-----------\n", elemento->preco);
    }
}

void lst_libera(Lista* cabeca_da_lista){
    Lista* p = cabeca_da_lista;
    Lista* aux;
       
    while(p != NULL){
        aux = p;
        p = p->prox;
        free(aux);
    }

}