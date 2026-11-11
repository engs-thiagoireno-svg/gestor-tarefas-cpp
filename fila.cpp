#include "fila.h"
#include "lista.h"
#include <iostream>

// Deixa a fila vazia. Parâmetro: f - a fila.
void iniciarFila(Fila& f) {
    f.inicio = nullptr;
    f.fim = nullptr;
}

// Coloca uma tarefa no fim da fila.
// Parâmetros: f - a fila; t - tarefa a enfileirar.
void enfileirar(Fila& f, Tarefa t) {
    NoFila* novo = new NoFila;
    novo->dado = t;
    novo->proximo = nullptr;
    if (f.fim == nullptr)
        f.inicio = novo;
    else
        f.fim->proximo = novo;
    f.fim = novo;
}

// Tira a tarefa do início da fila (dequeue) e libera o nó.
// Parâmetros: f - a fila; removida - recebe a tarefa retirada.
// Retorno: true se retirou, false se a fila estava vazia.
bool desenfileirar(Fila& f, Tarefa& removida) {
    if (f.inicio == nullptr)
        return false;
    NoFila* antigo = f.inicio;
    removida = antigo->dado;
    f.inicio = antigo->proximo;
    if (f.inicio == nullptr)
        f.fim = nullptr;
    delete antigo;
    antigo = nullptr;
    return true;
}

// Informa se a fila está vazia. Parâmetro: f. Retorno: true se vazia.
bool filaVazia(const Fila& f) {
    return f.inicio == nullptr;
}

// Mostra as tarefas pendentes, da primeira à última. Parâmetro: f.
void mostrarFila(const Fila& f) {
    if (filaVazia(f))
        std::cout << "(nenhuma tarefa pendente)" << std::endl;
    int posicao = 1;
    for (NoFila* p = f.inicio; p != nullptr; p = p->proximo) {
        std::cout << posicao++ << "o: ";
        mostrarTarefa(p->dado);
    }
}

// Libera todos os nós da fila. Parâmetro: f.
void liberarFila(Fila& f) {
    Tarefa descartada;
    while (desenfileirar(f, descartada)) {
    }
}