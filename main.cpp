#include <iostream>
#include <limits>
#include <string>
#include "tarefa.h"
#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "arvore.h"
#include "ordenacao.h"
#include "busca.h"

using namespace std;

const int MAX_TAREFAS = 100;

// Reúne todas as estruturas do sistema para passar entre as funções.
struct Sistema {
    NoLista* lista;
    NoArvore* arvore;
    Fila fila;
    NoPilha* pilha;
    int proximoId;
};

// Lê um inteiro do teclado, repetindo até o valor ser válido.
// Parâmetro: mensagem - texto exibido. Retorno: o número digitado.
int lerInteiro(const string& mensagem) {
    int valor;
    cout << mensagem;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Valor invalido. " << mensagem;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

// Lê uma linha de texto. Parâmetro: mensagem. Retorno: o texto digitado.
string lerTexto(const string& mensagem) {
    string texto;
    cout << mensagem;
    getline(cin, texto);
    return texto;
}

// Lê os dados de uma nova tarefa. Parâmetro: id - id da tarefa.
// Retorno: a tarefa preenchida.
Tarefa lerTarefa(int id) {
    Tarefa t;
    t.id = id;
    t.titulo = lerTexto("Titulo: ");
    t.prazo = lerInteiro("Prazo (AAAAMMDD): ");
    do {
        t.prioridade = lerInteiro("Prioridade (1=alta, 2=media, 3=baixa): ");
    } while (t.prioridade < 1 || t.prioridade > 3);
    return t;
}

// Refaz a árvore e a fila a partir da lista (a árvore não tem remoção).
// Parâmetro: s - sistema (por referência).
void reconstruirIndices(Sistema& s) {
    liberarArvore(s.arvore);
    liberarFila(s.fila);
    for (NoLista* p = s.lista; p != nullptr; p = p->proximo) {
        s.arvore = inserirNaArvore(s.arvore, p->dado);
        enfileirar(s.fila, p->dado);
    }
}

// Opção 1: cadastra tarefa e registra a ação na pilha. Parâmetro: s.
void opcaoAdicionar(Sistema& s) {
    Tarefa t = lerTarefa(s.proximoId++);
    inserirNaLista(s.lista, t);
    Acao acao = {ACAO_ADICIONAR, t};
    empilhar(s.pilha, acao);
    reconstruirIndices(s);
    cout << "Tarefa adicionada (id " << t.id << ")." << endl;
}

// Remove da lista a tarefa de um id e registra na pilha. Parâmetro: s, id.
// Retorno: true se removeu.
bool removerRegistrando(Sistema& s, int id) {
    Tarefa t;
    if (!buscarPorId(s.lista, id, t))
        return false;
    removerDaLista(s.lista, id);
    Acao acao = {ACAO_REMOVER, t};
    empilhar(s.pilha, acao);
    reconstruirIndices(s);
    return true;
}

// Opção 2: pede um id e remove a tarefa. Parâmetro: s.
void opcaoRemover(Sistema& s) {
    int id = lerInteiro("Id da tarefa a remover: ");
    if (removerRegistrando(s, id))
        cout << "Tarefa removida." << endl;
    else
        cout << "Id nao encontrado." << endl;
}

// Opção 4: desfaz a última ação (LIFO). Parâmetro: s.
void opcaoDesfazer(Sistema& s) {
    Acao acao;
    if (!desempilhar(s.pilha, acao)) {
        cout << "Nada para desfazer." << endl;
        return;
    }
    if (acao.tipo == ACAO_ADICIONAR)
        removerDaLista(s.lista, acao.tarefa.id);
    else
        inserirNaLista(s.lista, acao.tarefa);
    reconstruirIndices(s);
    cout << "Ultima acao desfeita." << endl;
}

// Opção 6: busca uma tarefa pelo título usando a árvore. Parâmetro: s.
void opcaoBuscarTitulo(Sistema& s) {
    string titulo = lerTexto("Titulo procurado: ");
    NoArvore* achada = buscarNaArvore(s.arvore, titulo);
    if (achada != nullptr)
        mostrarTarefa(achada->dado);
    else
        cout << "Tarefa nao encontrada." << endl;
}

// Opção 7: ordena por prazo (Insertion Sort) e lista. Parâmetro: s.
void opcaoOrdenarPorPrazo(Sistema& s) {
    Tarefa v[MAX_TAREFAS];
    int n = copiarListaParaVetor(s.lista, v, MAX_TAREFAS);
    insertionSortPorPrazo(v, n);
    for (int i = 0; i < n; i++)
        mostrarTarefa(v[i]);
    if (n == 0)
        cout << "(nenhuma tarefa cadastrada)" << endl;
}

// Opção 8: compara busca sequencial e binária pelo prazo. Parâmetro: s.
void opcaoCompararBuscas(Sistema& s) {
    Tarefa v[MAX_TAREFAS];
    int n = copiarListaParaVetor(s.lista, v, MAX_TAREFAS);
    insertionSortPorPrazo(v, n);
    int prazo = lerInteiro("Prazo procurado (AAAAMMDD): ");
    compararBuscas(v, n, prazo);
}

// Opção 9: conclui a próxima tarefa da fila (FIFO). Parâmetro: s.
void opcaoConcluirProxima(Sistema& s) {
    Tarefa proxima;
    if (!desenfileirar(s.fila, proxima)) {
        cout << "Nenhuma tarefa pendente." << endl;
        return;
    }
    removerRegistrando(s, proxima.id);
    cout << "Concluida: " << proxima.titulo << endl;
}

// Mostra o menu principal.
void exibirMenu() {
    cout << "\n===== GESTOR DE TAREFAS =====" << endl;
    cout << "1. Adicionar tarefa\n2. Remover tarefa\n3. Listar tarefas\n"
         << "4. Desfazer ultima acao\n5. Ver fila de pendentes\n"
         << "6. Buscar por titulo (arvore)\n7. Ordenar por prazo e listar\n"
         << "8. Comparar buscas (sequencial x binaria)\n"
         << "9. Concluir proxima pendente\n0. Sair" << endl;
}

// Executa a opção escolhida. Parâmetros: opcao - número do menu; s.
void executarOpcao(int opcao, Sistema& s) {
    switch (opcao) {
        case 1: opcaoAdicionar(s); break;
        case 2: opcaoRemover(s); break;
        case 3: percorrerLista(s.lista); break;
        case 4: opcaoDesfazer(s); break;
        case 5: mostrarFila(s.fila); break;
        case 6: opcaoBuscarTitulo(s); break;
        case 7: opcaoOrdenarPorPrazo(s); break;
        case 8: opcaoCompararBuscas(s); break;
        case 9: opcaoConcluirProxima(s); break;
        case 0: break;
        default: cout << "Opcao invalida." << endl;
    }
}

// Libera todas as estruturas (delete) antes de encerrar. Parâmetro: s.
void liberarTudo(Sistema& s) {
    liberarLista(s.lista);
    liberarArvore(s.arvore);
    liberarFila(s.fila);
    liberarPilha(s.pilha);
}

int main() {
    Sistema s;
    s.lista = nullptr;
    s.arvore = nullptr;
    s.pilha = nullptr;
    s.proximoId = 1;
    iniciarFila(s.fila);
    int opcao;
    do {
        exibirMenu();
        opcao = lerInteiro("Escolha: ");
        executarOpcao(opcao, s);
    } while (opcao != 0);
    liberarTudo(s);
    cout << "Ate logo!" << endl;
    return 0;
}