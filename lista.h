#ifndef LISTA_H
#define LISTA_H
#include "tarefa.h"
 
// Nó da lista encadeada principal: guarda uma tarefa e aponta para o próximo.
struct NoLista {
    Tarefa dado;
    NoLista* proximo;
};
 
void inserirNaLista(NoLista*& inicio, Tarefa t);
bool removerDaLista(NoLista*& inicio, int id);
bool buscarPorId(NoLista* inicio, int id, Tarefa& encontrada);
void mostrarTarefa(const Tarefa& t);
void percorrerLista(NoLista* inicio);
void liberarLista(NoLista*& inicio);
int copiarListaParaVetor(NoLista* inicio, Tarefa v[], int max);
 
#endif
 