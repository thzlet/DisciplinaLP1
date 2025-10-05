   #include "TAD_TREE.h"
    #include <stdlib.h>

    Arv* arv_criavazia(void){
        return NULL;
    }

    Arv* arv_cria(char c, Arv* e, Arv* d){
        Arv* novo_no = (Arv*)malloc(sizeof(Arv));
        if(!novo_no){
            printf("Não temos memória para criar um nó...\n");
            return NULL;
        }

        novo_no->info = c;
        novo_no->sae = e;
        novo_no->sad = d;

        return novo_no;
    }

    Arv* arv_libera(Arv* a){
        if(!arv_vazia(a)){
            arv_libera(a->sae);
            arv_libera(a->sad);
            free(a);
        }
        return NULL;
    }

    int arv_vazia(Arv* a){
        return a == NULL;
    }

    int arv_pertence(Arv* a, char c){
        if(arv_vazia(a)){
            return 0;
        }
        else{
            return arv_pertence(a->sae, c)||arv_pertence(a->sad, c)|| a->info == c;
        }
    }
    
    void arv_imprime(Arv* a){
        if(!arv_vazia(a)){
            printf("info: %c\n", a->info);
            arv_imprime(a->sae);
            arv_imprime(a->sad);
        }
    }