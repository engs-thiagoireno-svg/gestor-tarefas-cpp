#include "busca.h"
#include <iostream>

// Busca o prazo percorrendo o vetor do início ao fim 

// Parametros: v = vetor, n = tamanho, prazoBuscado, comparacoes saída

// Complexidade: O(n).

int buscaSequencial(Tarefa v[], int n, int prazoBuscado, long& comparacoes) {
    comparacoes = 0;
    for (int i = 0; i < n; i++) {
        comparacoes++;
        if (v[i].prazo == prazoBuscado)
            return i;
    }
    return -1;
}

// Busca o prazo dividindo o vetor ao meio

// O vetor precisa estar ordenado por prazo

// Parametros: v = vetor, n = tamanho, prazoBuscado, comparacoes saída

// Complexidade: O(log n).

int buscaBinaria(Tarefa v[], int n, int prazoBuscado, long& comparacoes) {
    int inicio = 0, fim = n - 1;
    comparacoes = 0;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        comparacoes++;
        if (v[meio].prazo == prazoBuscado)
            return meio;
        if (v[meio].prazo < prazoBuscado)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// Roda as duas buscas e mostra quantas comparações cada uma fez

// Parametros: v = vetor ordenado por prazo, n = tamanho, prazoBuscado

void compararBuscas(Tarefa v[], int n, int prazoBuscado) {
    long compSeq, compBin;
    int posSeq = buscaSequencial(v, n, prazoBuscado, compSeq);
    int posBin = buscaBinaria(v, n, prazoBuscado, compBin);
    std::cout << "Sequencial: posicao " << posSeq << ", "
              << compSeq << " comparacoes" << std::endl;
    std::cout << "Binaria:    posicao " << posBin << ", "
              << compBin << " comparacoes" << std::endl;
}