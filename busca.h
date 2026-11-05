#ifndef BUSCA_H
#define BUSCA_H

#include "tarefa.h"

int buscaSequencial(Tarefa v[], int n, int prazoBuscado, long& comparacoes);
int buscaBinaria(Tarefa v[], int n, int prazoBuscado, long& comparacoes);
void compararBuscas(Tarefa v[], int n, int prazoBuscado);

#endif