#ifndef TAREFA_H
#define TAREFA_H

#include <string>

// Representa uma tarefa do gestor.
struct Tarefa {
    int id;              // identificador único
    std::string titulo;  // nome da tarefa
    int prazo;           // data no formato AAAAMMDD (ex: 20261130)
    int prioridade;      // 1 = alta, 2 = média, 3 = baixa
};

#endif