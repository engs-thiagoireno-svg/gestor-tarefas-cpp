#include "ordenacao.h"

// Ordena o vetor pelo prazo Insertion Sort Parametros: v = vetor, n = tamanho

// Retorno: nenhum altera o próprio vetor

// Complexidade: O(n²) no pior caso, O(n) no melhor

void insertionSortPorPrazo(Tarefa v[], int n) {
    for (int i = 1; i < n; i++) {
        Tarefa atual = v[i];
        int j = i - 1;
        while (j >= 0 && v[j].prazo > atual.prazo) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = atual;
    }
}