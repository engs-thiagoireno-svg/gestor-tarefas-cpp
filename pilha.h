#ifndef PILHA_H
#define PILHA_H
#include "tarefa.h"

// Tipos de ação que podem ser desfeitos.
enum TipoAcao { ACAO_ADICIONAR, ACAO_REMOVER };

// Uma ação feita pelo usuário: o tipo e a tarefa envolvida.
struct Acao {
    TipoAcao tipo;
    Tarefa tarefa;
};

// Nó da pilha: guarda uma ação e aponta para o elemento de baixo.
struct NoPilha {
    Acao dado;
    NoPilha* abaixo;
};

void empilhar(NoPilha*& topo, Acao a);
bool desempilhar(NoPilha*& topo, Acao& removida);
bool pilhaVazia(NoPilha* topo);
void liberarPilha(NoPilha*& topo);

#endif