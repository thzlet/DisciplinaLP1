#include "TAD_TreeGen.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int tree_empty(Node* root) { // // 1. verifica se a arvore ta vazia 
    return (root == NULL); // se estiver vazia, retorna 1
}

Node* tree_create_empty() { // 2. cria uma arvore vazia 
    return NULL; // arvore vazia = ponteiro nulo 
}

Node* tree_create_node(void* info, Node* lst, Node* rst) { // 3. cria um novo nó
    Node* new_node = (Node*)malloc(sizeof(Node)); // aloca memória pro nó
    if (!new_node) { // verifica se foi alocado
        printf("Error!\n");
        return NULL;
    }
    new_node->info = info; // ponteiro genérico para os dados do nó
    new_node->left = lst; // filho a esquerda
    new_node->right = rst; /// filho a direita
    return new_node;
}

Node* tree_insert_node(Node* root, Node* new_node, int (compare)(void*, void*)) { // 4. insere o novo nó
    if (root == NULL) // se a arvore estiver vazia, o nó vira raiz
        return new_node;

    if (compare(new_node->info, root->info) < 0) // verificando se vai para a esquerda ou direita
        root->left = tree_insert_node(root->left, new_node, compare);
    else
        root->right = tree_insert_node(root->right, new_node, compare);

    return root;
}
// 5. libera memória 
void tree_free(Node* root) { // liberando recursivamente os nós
    if (root != NULL) {
        tree_free(root->left);
        tree_free(root->right);
        free(root->info); 
        free(root);
    }
}
/* 
// o que??
void tree_map(Node* root, void (operation)(void*)) { // 6...
    if (root != NULL) {
        tree_map(root->left, operation);
        operation(root->info);
        tree_map(root->right, operation);
    }
}
*/
Node* tree_copy_node(Node* original) { // 7. copia o nó
    if (original == NULL) return NULL; // nó original 
    Node* copy = (Node*)malloc(sizeof(Node)); // aloca memória pro novo node
    if (copy == NULL) return NULL; // verifica a alocação
    copy->info = original->info; // shallow copy
    copy->left = NULL; // inicializa os filhos como null
    copy->right = NULL;
    return copy;
}

Listagen* tree_filter_as_list(Node* root, int (condition)(void*), void* (copy_info)(void*)) { //8. cria uma lista encadeada de elementos que satisfazem uma condição
    if (root == NULL) return NULL; // nada para filtrar

    Listagen* lista = NULL; // inicializa a lista generica

    if (condition(root->info)) { // verifica se o nó atual atende a condição
        Listagen* novo = (Listagen*)malloc(sizeof(Listagen)); // aloca elemento na lista
        novo->info = copy_info(root->info); // copia os dados
        novo->prox = lista; // insere na lista
        lista = novo;
    }
    // filtra recursivamente as subarvores
    Listagen* left = tree_filter_as_list(root->left, condition, copy_info);
    Listagen* right = tree_filter_as_list(root->right, condition, copy_info);

    // percorre a lista a esquerda e add elementos do nó no final 
    Listagen* p = left;
    while (p && p->prox != NULL) p = p->prox;
    if (p) p->prox = lista;
    else left = lista;

    // percorre a lista resultante e add os elementos na sub a direita
    p = left;
    while (p && p->prox != NULL) p = p->prox;
    if (p) p->prox = right;
    else left = right;

    // lista encadeada não necessariamente ordenada
    return left;
}

Node* tree_filter(Node* root, int (condition)(void*), void* (copy_info)(void*), int (compare)(void*, void*)) {
    if (root == NULL) return NULL;
    Node* new_root = NULL;

    if (condition(root->info)) {
        void* copy = copy_info(root->info);
        Node* new_node = tree_create_node(copy, NULL, NULL); // novo nó como cópia
        new_root = tree_insert_node(new_root, new_node, compare);
    }

    Node* left = tree_filter(root->left, condition, copy_info, compare);
    Node* right = tree_filter(root->right, condition, copy_info, compare);

    if (left) new_root = tree_insert_node(new_root, left, compare);
    if (right) new_root = tree_insert_node(new_root, right, compare);

    // o resultado eh uma arvore
    return new_root;
}

int tree_get_height(Node* node) { // altura de uma arvore a partir de um nó
    if (node == NULL) return 0; // altura 0
    int left_h = tree_get_height(node->left); 
    int right_h = tree_get_height(node->right);
    return (left_h > right_h ? left_h : right_h) + 1; // +1 conta o nó atual
}

Node* rotate_right(Node* root) {
    if (root == NULL || root->left == NULL) // impossivel rotacionar
        return root;

    Node* new_root = root->left; // novo topo 
    root->left = new_root->right; // filho esquerdo do nó atual
    new_root->right = root; // nó atual eh filho direito do new_root
    return new_root;
}

Node* rotate_left(Node* root) {
    if (root == NULL || root->right == NULL)
        return root;

    Node* new_root = root->right; // mesma coisa 
    root->right = new_root->left;
    new_root->left = root;
    return new_root;
}
/* 
desbalanceamento de árvore em C ocorre quando uma árvore
de busca binária perde seu equilíbrio estrutural
*/
Node* tree_insert_balanced(Node* root, Node* new_node, int (compare)(void*, void*)) {
    if (root == NULL) // se a arv ta vazia, o nó vira raiz
        return new_node;

    if (compare(new_node->info, root->info) < 0) // insere recursivameente 
        root->left = tree_insert_balanced(root->left, new_node, compare);
    else
        root->right = tree_insert_balanced(root->right, new_node, compare);

    int balance = tree_get_height(root->left) - tree_get_height(root->right);

    if (balance > 1 && compare(new_node->info, root->left->info) < 0)
        return rotate_right(root); 

    if (balance > 1 && compare(new_node->info, root->left->info) > 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && compare(new_node->info, root->right->info) > 0)
        return rotate_left(root);

    if (balance < -1 && compare(new_node->info, root->right->info) < 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

Node* tree_search(Node* root, int (condition)(void*)) {
    if (root == NULL) return NULL;

    if (condition(root->info)) // atende a condicao?
        return root;

    Node* found = tree_search(root->left, condition);
    if (found != NULL) return found; // found eh a variavel flag

    return tree_search(root->right, condition);
}

void write_inorder(Node *new_node, FILE *fp, char* (*create_line)(void*)) {
    if (new_node == NULL) return;

    write_inorder(new_node->left, fp, create_line); // percorre a esquerda

    char* line = create_line(new_node->info); // converte o info em string
    if (line != NULL) {
        fprintf(fp, "%s\n", line);
        free(line); // libera a memoria temporaria
    }

    write_inorder(new_node->right, fp, create_line);
}

// salva a arvore no arquivo
void tree_to_file(Node* root, char* file_name, char* (create_line)(void*)) {
    FILE* fp = fopen(file_name, "w"); // abre o arquivo pra escrita
    if (!fp) {
        printf("Error!\n");
        return;
    }

    write_inorder(root, fp, create_line); // percorre a arvore e fecha o arquivo
    fclose(fp);
}

// carrega a arvore do arquivo
Node* tree_load_from_file(char* file_name, void* (read_line)(char*), int (compare)(void*, void*)) {
    FILE* fp = fopen(file_name, "r"); // abre pra leitura
    if (!fp) {
        printf("Error!\n");
        return NULL;
    }

    Node* root = NULL;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        void* data = read_line(buffer);
        Node* new_node = tree_create_node(data, NULL, NULL);
        root = tree_insert_node(root, new_node, compare);
    }

    fclose(fp);
    return root;
}

// exclusão em arvore, um monstro terrivel
Node* tree_delete_balanced(Node* root, Node* node_to_delete, int (compare)(void*, void*)) {
    if (!root || !node_to_delete) return root; // retorna como tá

    int cmp = compare(node_to_delete->info, root->info); 
    if (cmp < 0) {
        root->lst = tree_delete_balanced(root->lst, node_to_delete, compare);
    } else if (cmp > 0) {
        root->rst = tree_delete_balanced(root->rst, node_to_delete, compare);
    } else {     
        if (!root->lst || !root->rst) {
            Node* temp = root->lst ? root->lst : root->rst;
            free(root->info);
            free(root);
            return temp;
        }

        Node* succ = root->rst; // succ = sucessor-in-order
        while (succ->lst) succ = succ->lst;

        void* temp_info = root->info;
        root->info = succ->info;
        succ->info = temp_info;

        root->rst = tree_delete_balanced(root->rst, succ, compare);
    }

    int balance = tree_get_height(root->lst) - tree_get_height(root->rst);

    if (balance > 1) {
        if (tree_get_height(root->lst->lst) >= tree_get_height(root->lst->rst))
            return rotate_right(root);          
        else {
            root->lst = rotate_left(root->lst); 
            return rotate_right(root);
        }
    }

    if (balance < -1) {
        if (tree_get_height(root->rst->rst) >= tree_get_height(root->rst->lst))
            return rotate_left(root);           
        else {
            root->rst = rotate_right(root->rst);
            return rotate_left(root);
        }
    }

    return root;
}