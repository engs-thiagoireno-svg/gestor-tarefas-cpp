#include "pilha.h"

// Coloca uma ação no topo da pilha (push, LIFO).
// Parâmetros: topo - topo da pilha (por referência). a - ação a guardar.
void empilhar(NoPilha*& topo, Acao a) {
    NoPilha* novo = new NoPilha;
    novo->dado = a;
    novo->abaixo = topo;
    topo = novo;
}

// Tira a ação do topo da pilha (pop) e libera o nó.
// Parâmetros: topo - topo da pilha. removida - recebe a ação retirada.
// Retorno: true se retirou, false se a pilha estava vazia.
bool desempilhar(NoPilha*& topo, Acao& removida) {
    if (topo == nullptr)
        return false;
    NoPilha* antigo = topo;
    removida = antigo->dado;
    topo = antigo->abaixo;
    delete antigo;
    antigo = nullptr;
    return true;
}

// Informa se a pilha está vazia. Parâmetro: topo. Retorno: true se vazia.
bool pilhaVazia(NoPilha* topo) {
    return topo == nullptr;
}

// Libera todos os nós da pilha. Parâmetro: topo.
void liberarPilha(NoPilha*& topo) {
    Acao descartada;
    while (desempilhar(topo, descartada)) {
    }
}