#ifndef FILA_H
#define FILA_H
#include "tarefa.h"

// Nó da fila: guarda uma tarefa e aponta para o próximo da fila.
struct NoFila {
    Tarefa dado;
    NoFila* proximo;
};

// Fila com ponteiros para o início (sai) e o fim (entra).
struct Fila {
    NoFila* inicio;
    NoFila* fim;
};

void iniciarFila(Fila& f);
void enfileirar(Fila& f, Tarefa t);
bool desenfileirar(Fila& f, Tarefa& removida);
bool filaVazia(const Fila& f);
void mostrarFila(const Fila& f);
void liberarFila(Fila& f);

#endif