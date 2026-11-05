#include "arvore.h"

// Insere uma tarefa na árvore, ordenada por título (recursivo).
// Parâmetros: raiz - raiz atual da (sub)árvore; t - tarefa a inserir.
// Retorno: a raiz da (sub)árvore depois da inserção.
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