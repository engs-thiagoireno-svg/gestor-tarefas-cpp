#ifndef ARVORE_H
#define ARVORE_H

#include <string>
#include "tarefa.h"

// Nó da árvore: guarda uma tarefa e aponta para os filhos.
struct NoArvore {
    Tarefa dado;
    NoArvore* esquerda;
    NoArvore* direita;
};

NoArvore* inserirNaArvore(NoArvore* raiz, Tarefa t);

#endif