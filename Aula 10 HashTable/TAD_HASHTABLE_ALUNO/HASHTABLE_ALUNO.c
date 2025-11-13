#include "HASHTABLE_ALUNO.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 1. calcula o hash de uma chave primária
static int hash(int mat){ // static deixa a função visivel apenas dentro desse arquivo
    return mat%N; // calcula o indice da tabela com divisao modular 
}

// 2. busca um aluno por matrícula e retorna o ponteiro para a estrutura, caso exista.
Aluno* hsh_busca(Aluno** tab, int mat){

    Aluno* p = tab[hash(mat)]; // acessa o bucket 

    while(p != NULL){
        if(p->mat == mat)
            break;
        p = p->prox;
    }
    
    return p;
}

// 3. insere um aluno na tabela de dispersão (usando encadeamento)
Aluno* hsh_insere(Aluno** tab, int mat, char* nome, char* tel, char* email){
    int id_hash = hash(mat);

    Aluno* p= tab[id_hash];
    Aluno* ant = NULL;

    while(p != NULL){
        if(p->mat == mat)
            break;
        p = p->prox;
    }

   
    if(p){  
        strcpy(p->nome, nome);
        strcpy(p->tel, tel);
        strcpy(p->email, email);
        return p;
    }
    else  
    {
        Aluno* novo = (Aluno*)malloc(sizeof(Aluno)); // se o aluno não existe
        
        if(!novo){
            printf("Não temos memória para adicionar um aluno...\n");
            return NULL;
        }

        // preenche os dados do aluno novo
        novo->mat = mat;
        strcpy(novo->nome, nome);
        strcpy(novo->tel, tel);
        strcpy(novo->email, email);
        novo->prox = NULL;

        if(ant){ 
            ant->prox = novo; // aluno novo colocado depois de ant
        }
        else{ 
            tab[id_hash] = novo; // se nao existe, a cabeca aponta pra novo
        }
        return novo;
    }
}

// 4. remover aluno pela matrícula
int hsh_remove(Aluno** tab, int mat){
    Aluno* p = tab[hash(mat)]; // pega o head do bucket
    Aluno* ant = NULL;

    while(p!= NULL){
        if(p->mat == mat)
            break;
        
        ant = p;
        p = p->prox;
    }

    if(!p)
        return 0;

    if(ant)
        ant->prox = p->prox;
    else
        // tab[hash(mat)] = NULL;
    
    free(p);
    return 1;
}

// 5. atualizar dados de um aluno
int hsh_atualiza(Aluno** tab, int mat, char* nome, char* tel, char* email){
    int id_hash = hash(mat);

    Aluno* p= tab[id_hash];
    Aluno* ant = NULL;

    while(p != NULL){
        if(p->mat == mat)
            break;
        p = p->prox;
    }

    if(p){ 
        strcpy(p->nome, nome);
        strcpy(p->tel, tel);
        strcpy(p->email, email);
        return p;
    }
    else  
    {
        return NULL;
    }
}

// 6. listar todos os alunos
void hsh_lista_todos(Aluno** tab){

    Aluno* p = NULL;

    printf("\nLISTA DE ALUNOS\n");
    for(int i =0; i< N; i++){
        if(tab[i]){
            p = tab[i];
            while(p){
                printf("\nMatrícula: %5d ###\n", p->mat);
                printf("Aluno: %s\n", p->nome);
                printf("Tel: %s\n", p->tel);
                printf("E-mail: %s\n", p->email);

                p = p->prox;
            }
        }
    }
}

// 7. contar número de alunos na tabela
int hsh_conta_alunos(Aluno** tab){
    int qtd_alunos = 0; // count
    Aluno* p = NULL;
    for(int i = 0; i < N; i++){
        p = tab[i];
        while(p != NULL){
            qtd_alunos++;
            p = p->prox;
        }
    }

    return qtd_alunos;
}

// 8. busca parcial de aluno por nome
Aluno* hsh_busca_por_nome(Aluno** tab, char* nome){
    Aluno* p = NULL;

    for(int i = 0; i < N; i++){
        p = tab[i];
        while(p != NULL){
            if(strstr(p->nome, nome) != NULL){  
                return p; // encontrou
            }
            p = p->prox;
        }
    }

    return NULL; 
}

// 9. limpar/liberar toda a tabela
void hsh_limpa_tabela(Aluno** tab){
    Aluno* p;
    Aluno* aux;

    for(int i = 0; i < N; i++){
        p = tab[i]; 
        while(p != NULL){
            aux = p->prox;
            free(p);
            p = aux;
        }
        tab[i] = NULL;
    }
}


// 10. calcular fator de carga da tabela
float hsh_fator_carga(Aluno** tab){
    int qtd = hsh_conta_alunos(tab);
    return (float)qtd / N; // razao entre numero de chaves e numero de posicoes
}

// 11. verificar se tabela está vazia
int hsh_vazia(Aluno** tab){
    for(int i = 0; i < N; i++){
        if(tab[i] != NULL){
            return 0; 
        }
    }
    return 1;
}

// 12. exportar dados para arquivo
int hsh_exporta_arquivo(Aluno** tab, char* filename, char* (*escrever_linha_csv)(void*)){
    FILE* f = fopen(filename, "w"); // abre arquivo em modo de escrita
    if(!f) return 0;

    Aluno* p; // itera sobre as listas dentro dos buckets 

    for(int i = 0; i < N; i++){
        p = tab[i];
        while(p != NULL){
            char* linha = escrever_linha_csv((void*)p); // converte aluno p pra void
            fprintf(f, "%s\n", linha);
            free(linha);   
            p = p->prox; // continua o loop 
        }
    }

    fclose(f);
    return 1; // deu bom 
}

// 13. importar dados de arquivo
int hsh_importa_arquivo(Aluno** tab, char* filename, void* (*ler_linha_csv)(char*)){
    // importa os dados de alunos de um csv e insere na tabela hash em memória
    FILE* f = fopen(filename, "r"); // abrindo no modo leitura
    if(!f) return 0;

    char buffer[256]; // criando um vetor buffer // temporario pra armazenar as linhas do arquivo 

    while(fgets(buffer, 256, f)){ // leitura linha a linha até EOF
        buffer[strcspn(buffer, "\n")] = '\0'; //strcspn encontra \n e substitui por \0

        Aluno* temp = (Aluno*)ler_linha_csv(buffer); // lendo os campos separados por virgula
        if(temp){ // se temp != NULL, a linha foi lida
            hsh_insere(tab, temp->mat, temp->nome, temp->tel, temp->email);
            free(temp); 
        }
    }

    fclose(f);
    return 1;
}
