#include "arvore.h"
#include "arvore.h"
#include <iostream>

// Busca uma tarefa pelo título na árvore 

// Parâmetros: raiz - raiz da sub-arvore, titulo - título procurado

// Retorno: o nó encontrado ou nullptr se não existir.

NoArvore* buscarNaArvore(NoArvore* raiz, const std::string& titulo) {
    if (raiz == nullptr || raiz->dado.titulo == titulo)
        return raiz;
    if (titulo < raiz->dado.titulo)
        return buscarNaArvore(raiz->esquerda, titulo);
    return buscarNaArvore(raiz->direita, titulo);
}

// Mostra as tarefas em ordem alfabética de título esquerda, nó e direita

// Parâmetros: raiz - raiz da sub-arvore a percorrer.

void percorrerEmOrdem(NoArvore* raiz) {
    if (raiz == nullptr)
        return;
    percorrerEmOrdem(raiz->esquerda);
    std::cout << raiz->dado.titulo << " | prazo: " << raiz->dado.prazo
              << " | prioridade: " << raiz->dado.prioridade << std::endl;
    percorrerEmOrdem(raiz->direita);
}

// Insere uma tarefa na árvore, ordenada por título 

// Parâmetros: raiz - raiz atual da sub-arvore

// Retorno: a raiz da sub-arvore depois da inserção.

NoArvore* inserirNaArvore(NoArvore* raiz, Tarefa t) {
    if (raiz == nullptr) {
        NoArvore* novo = new NoArvore;
        novo->dado = t;
        novo->esquerda = nullptr;
        novo->direita = nullptr;
        return novo;
    }
    if (t.titulo < raiz->dado.titulo)
        raiz->esquerda = inserirNaArvore(raiz->esquerda, t);
    else
        raiz->direita = inserirNaArvore(raiz->direita, t);
    return raiz;
}

// Libera todos os nós da árvore recursivo, de baixo para cima

// Parâmetros: raiz - referencia para o ponteiro da raiz, vira nullptr no fim

void liberarArvore(NoArvore*& raiz) {
    if (raiz == nullptr)
        return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    delete raiz;
    raiz = nullptr;
}