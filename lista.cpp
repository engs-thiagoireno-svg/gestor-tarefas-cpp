#include "lista.h"
#include <iostream>

// Insere uma tarefa no fim da lista (cria o nó com new).
// Retorno: nenhum.
void inserirNaLista(NoLista*& inicio, Tarefa t) {
    NoLista* novo = new NoLista;
    novo->dado = t;
    novo->proximo = nullptr;
    if (inicio == nullptr) {
        inicio = novo;
        return;
    }
    NoLista* atual = inicio;
    while (atual->proximo != nullptr)
        atual = atual->proximo;
    atual->proximo = novo;
}

// Remove da lista a tarefa com o id informado e libera o nó (delete).
// Retorno: true se removeu, false se o id não existe.
bool removerDaLista(NoLista*& inicio, int id) {
    NoLista* anterior = nullptr;
    NoLista* atual = inicio;
    while (atual != nullptr && atual->dado.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == nullptr)
        return false;
    if (anterior == nullptr)
        inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;
    delete atual;
    atual = nullptr;
    return true;
}

// Procura uma tarefa pelo id e copia para 'encontrada'.
// Retorno: true se achou, false caso contrário.
bool buscarPorId(NoLista* inicio, int id, Tarefa& encontrada) {
    for (NoLista* p = inicio; p != nullptr; p = p->proximo) {
        if (p->dado.id == id) {
            encontrada = p->dado;
            return true;
        }
    }
    return false;
}

// Mostra uma tarefa em uma linha.
void mostrarTarefa(const Tarefa& t) {
    std::cout << "[" << t.id << "] " << t.titulo << " | prazo: " << t.prazo
              << " | prioridade: " << t.prioridade << std::endl;
}

// Mostra todas as tarefas da lista.
void percorrerLista(NoLista* inicio) {
    if (inicio == nullptr)
        std::cout << "(nenhuma tarefa cadastrada)" << std::endl;
    for (NoLista* p = inicio; p != nullptr; p = p->proximo)
        mostrarTarefa(p->dado);
}

// Dá delete em todos os nós da lista.
void liberarLista(NoLista*& inicio) {
    while (inicio != nullptr) {
        NoLista* removido = inicio;
        inicio = inicio->proximo;
        delete removido;
        removido = nullptr;
    }
}

// Copia as tarefas da lista para um vetor.
// Retorno: quantidade de tarefas copiadas.
int copiarListaParaVetor(NoLista* inicio, Tarefa v[], int max) {
    int n = 0;
    for (NoLista* p = inicio; p != nullptr && n < max; p = p->proximo)
        v[n++] = p->dado;
    return n;
}