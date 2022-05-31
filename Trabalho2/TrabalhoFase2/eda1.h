/*
* Project: TrabalhoFase1
* Purpose: Licenciatura de Engenharia Informática Médica
* Company: IPCA
* Created by: Joao
* Created on: 29/04/2022
* Email: a21210@alunos.ipca.pt
**/

#include <stdlib.h>
#include <stdio.h>

#define MAX_MAQUINA 100
#define MAX_JOB     100

typedef struct maquina {
    int id;
    int tempo;
} maquina;

typedef struct lista {
    maquina lista_maquinas[MAX_MAQUINA];
    int quantidade;
    struct lista* prox;
} lista;

lista* JOBS[MAX_JOB];

maquina criar_maquina(int id, int tempo);

lista* inicia_lista(maquina* lista_maquinas, int quantidade);

void remover_no(lista** ls, lista* anterior, int idx);

void inserir(lista** ls, maquina* lista_maquinas, int quantidade);

int tamanho_lista(lista* ls);

maquina* inserir_operacao_aux(int* qtd);

int existe_job();

int escolher_job(int i);

int inserir_operacao();

void criar_job();

int lista_operacoes_job();

int remover_operacao();

int alterar_operacao();

int listar_tempo_minimo_aux(int indice_job, int f);

int listar_tempo_minimo();

int listar_tempo_maximo_aux(int indice_job, int f);

int listar_tempo_maximo();

int listar_tempo_medio();

int remover_job();

int menu();

void print_chars(char ch, int count, int newline);

void mostrar_tabela();

