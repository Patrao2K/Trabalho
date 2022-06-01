/*
* Project: TrabalhoFase2
* Purpose: Licenciatura de Engenharia Informática Médica
* Company: IPCA
* Created by: Joao
* Created on: 16/05/2022
* Email: a21210@alunos.ipca.pt
**/


#include "eda1.h"

maquina criar_maquina(int id, int tempo) {
    maquina m;
    m.id = id;
    m.tempo = tempo;
    return m;
}

/// <summary>
/// criar operações
/// </summary>
/// <param name="lista_maquinas"></param>
/// <param name="quantidade"></param>
/// <returns></returns>
lista* inicia_lista(maquina* lista_maquinas, int quantidade) {
    lista* ls = (lista*)malloc(sizeof(lista));
    for (int i = 0; i < quantidade; i++) {
        ls->lista_maquinas[i] = lista_maquinas[i];
    }

    ls->quantidade = quantidade;
    ls->prox = NULL;
    return ls;
}
/// <summary>
/// Função auxiliar
/// </summary>
/// <param name="ls"></param>
/// <param name="anterior"></param>
/// <param name="idx"></param>
void remover_no(lista** ls, lista* anterior, int idx) {
    if (*ls == NULL) {
        return;
    }

    lista* aux = *ls;

    if (idx == 0) {
        
        if (anterior == NULL) {
            
            if (aux->prox == NULL) {
                aux->quantidade = 0;
                return;
            }
            else {
                lista* temp = aux->prox;
                for (int i = 0; temp->quantidade; i++) {
                    aux->lista_maquinas[i] = temp->lista_maquinas[i];
                    aux->quantidade = temp->quantidade;
                }

                aux->prox = temp->prox;
                free(temp);
                return;
            }
        }

        
        if (aux->prox == NULL) {
            anterior->prox = NULL;
            free(aux);
        }
    }
    else {
        remover_no(&(*ls)->prox, *ls, idx - 1);
    }
}
/// <summary>
/// Função auxiliar
/// </summary>
/// <param name="ls"></param>
/// <param name="lista_maquinas"></param>
/// <param name="quantidade"></param>
void inserir(lista** ls, maquina* lista_maquinas, int quantidade) {
    if (*ls == NULL) {
        *ls = inicia_lista(lista_maquinas, quantidade);
        return;
    }
    if ((*ls)->quantidade == 0) {
        for (int i = 0; i < quantidade; i++) {
            (*ls)->lista_maquinas[i] = lista_maquinas[i];
        }
        (*ls)->quantidade = quantidade;
        return;
    }

    inserir(&(*ls)->prox, lista_maquinas, quantidade);
}

int tamanho_lista(lista* ls) {
    int tam = 0;
    if (ls != NULL) {
        tam += tamanho_lista(ls->prox) + 1;
    }

    return tam;
}
/// <summary>
/// Função auxiliar
/// </summary>
/// <param name="qtd"></param>
/// <returns></returns>
maquina* inserir_operacao_aux(int* qtd) {
    printf("Digite o numero de maquinas que podem executar essa operacao\n");
    scanf("%d", qtd);
    getchar();
    maquina* maq = (maquina*)malloc(sizeof(maquina) * (*qtd));
    for (int i = 0; i < *qtd; i++) {
        printf("Digite o id e o tempo da %d maquina\n", i + 1);
        scanf("%d %d", &maq[i].id, &maq[i].tempo);
        getchar();
    }
    return maq;
}

int existe_job() {
    int idx = 0;
    while (JOBS[idx] != NULL) {
        idx++;
    }
    return idx > 0;
}
/// <summary>
/// Função auxiliar
/// </summary>
/// <param name="i"></param>
/// <returns></returns>
int escolher_job(int i) {
    if (existe_job() == 0) {
        return -1;
    }

    int idx = 0;
    if (i == 1)
        printf("Escolha qual job que deseja remover na operacao\n\n");
    else {
        printf("Lista de Jobs\n\n");
    }
    while (JOBS[idx] != NULL) {
        printf("Job: %d\n", idx);
        idx++;
    }

    int indice_job; scanf("%d", &indice_job); getchar();
    if (indice_job > idx - 1 || indice_job < 0) {
        return -1;
    }

    return indice_job;
}
/// <summary>
/// Inserir operacao
/// </summary>
/// <returns></returns>
int inserir_operacao() {
    int indice_job = escolher_job(1);
    if (indice_job == -1) {
        return -1;
    }

    int qtd;
    maquina* aux = inserir_operacao_aux(&qtd);
    inserir(&JOBS[indice_job], aux, qtd);
    return 1;
}

/// <summary>
/// criar job
/// </summary>
void criar_job() {
    int qtd;
    for (int i = 0; i < MAX_JOB; i++) {
        if (JOBS[i] == NULL) {
            JOBS[i] = (lista*)malloc(sizeof(lista));
            JOBS[i]->quantidade = 0;
            JOBS[i]->prox = NULL;
            return;
        }
    }
}

/// <summary>
/// Função para listar 
/// </summary>
/// <returns></returns>
int lista_operacoes_job() {
    int indice_job = escolher_job(0);
    if (indice_job == -1) {
        return -1;
    }

    system("cls");
    printf("Job %d\n\n", indice_job);

    lista* aux = JOBS[indice_job];

    int idx = 1;
    while (aux != NULL && aux->quantidade > 0) {
        printf("Operacao %d:\n", idx);
        for (int i = 0; i < aux->quantidade; i++) {
            printf("          Maquina: %d, Tempo: %d\n", aux->lista_maquinas[i].id, aux->lista_maquinas[i].tempo);
        }
        aux = aux->prox;
        idx++;
    }
}
/// <summary>
/// Remover operacao
/// </summary>
/// <returns></returns>
int remover_operacao() {
    int indice_job = escolher_job(1);
    if (indice_job == -1) {
        return -1;
    }

    system("cls");
    printf("Job %d\n\n", indice_job);

    int idx = 0;

    lista* aux = JOBS[indice_job];

    while (aux != NULL && aux->quantidade > 0) {
        printf("Operacao: %d\n", idx);
        idx++;
        aux = aux->prox;
    }

    if (idx == 0) {
        return -1;
    }

    printf("Escolha qual operacao voce deseja remover: ");
    int op; scanf("%d", &op); getchar();
    if (op < 0 || op > idx) {
        return -1;
    }

    remover_no(&JOBS[indice_job], NULL, op);
    return 1;
}
/// <summary>
/// Editar a operacao
/// </summary>
/// <returns></returns>
int alterar_operacao() {
    int indice_job = escolher_job(1);
    if (indice_job == -1) {
        return -1;
    }

    system("cls");
    printf("Job %d\n\n", indice_job);

    int idx = 0;

    lista* aux = JOBS[indice_job];
    while (aux != NULL && aux->quantidade > 0) {
        printf("Operacao: %d\n", idx);
        idx++;
        aux = aux->prox;
    }

    if (idx == 0) {
        return -1;
    }

    printf("Escolha qual operacao voce deseja alterar: ");
    int op; scanf("%d", &op); getchar();
    if (op < 0 || op > idx - 1) {
        return -1;
    }

    aux = JOBS[indice_job];
    while (op > 0) {
        aux = aux->prox;
        op--;
    }


    int qtd;
    maquina* maq = inserir_operacao_aux(&qtd);

    for (int i = 0; i < qtd; i++) {
        aux->lista_maquinas[i] = maq[i];
    }

    aux->quantidade = qtd;
    return 1;
}
/// <summary>
/// Tempo minimo funcao auxiliar
/// </summary>
/// <param name="indice_job"></param>
/// <param name="f"></param>
/// <returns></returns>
int listar_tempo_minimo_aux(int indice_job, int f) {
    lista* aux = JOBS[indice_job];

    int tempo_minimo = 0;

    if (f == 1) {
        system("cls");
        printf("Job %d\n\n", indice_job);
    }

    int idx = 0;

    while (aux != NULL) {
        int min = 1000000;
        int id;
        for (int i = 0; i < aux->quantidade; i++) {
            if (min > aux->lista_maquinas[i].tempo) {
                min = aux->lista_maquinas[i].tempo;
                id = aux->lista_maquinas[i].id;
            }
        }
        if (f == 1)
            printf("Operacao %d: Maquina: %d, Tempo: %d\n", idx, id, min);
        tempo_minimo += min;
        aux = aux->prox;
        idx++;
    }
    if (f == 1)
        printf("\nTempo minimo necessario para completar o Job %d eh: %d\n", indice_job, tempo_minimo);
    return tempo_minimo;
}
/// <summary>
/// tempo minimo 
/// </summary>
/// <returns></returns>
int listar_tempo_minimo() {
    int indice_job = escolher_job(1);
    if (indice_job == -1) {
        return -1;
    }

    return listar_tempo_minimo_aux(indice_job, 1);
}
/// <summary>
/// tempo maximo funcao auxiliar
/// </summary>
/// <param name="indice_job"></param>
/// <param name="f"></param>
/// <returns></returns>
int listar_tempo_maximo_aux(int indice_job, int f) {
    lista* aux = JOBS[indice_job];

    int tempo_maximo = 0;
    if (f == 1) {
        system("cls");
        printf("Job %d\n\n", indice_job);
    }

    int idx = 0;

    while (aux != NULL) {
        int max = -1;
        int id;
        for (int i = 0; i < aux->quantidade; i++) {
            if (max < aux->lista_maquinas[i].tempo) {
                max = aux->lista_maquinas[i].tempo;
                id = aux->lista_maquinas[i].id;
            }
        }
        if (f == 1)
            printf("Operacao %d: Maquina: %d, Tempo: %d\n", idx, id, max);
        tempo_maximo += max;
        aux = aux->prox;
        idx++;
    }

    if (f == 1)
        printf("\nTempo maximo necessario para completar o Job %d eh: %d\n", indice_job, tempo_maximo);
    return tempo_maximo;
}
/// <summary>
///  tempo maximo
/// </summary>
/// <returns></returns>
int listar_tempo_maximo() {
    int indice_job = escolher_job(1);
    if (indice_job == -1) {
        return -1;
    }

    return listar_tempo_maximo_aux(indice_job, 1);
}
/// <summary>
/// tempo medio
/// </summary>
/// <returns></returns>
int listar_tempo_medio() {
    int indice_job = escolher_job(1);
    if (indice_job == -1) {
        return -1;
    }

    system("cls");
    printf("Job %d\n\n", indice_job);

    int idx = 0;

    lista* aux = JOBS[indice_job];
    while (aux != NULL && aux->quantidade > 0) {
        printf("Operacao: %d\n", idx);
        idx++;
        aux = aux->prox;
    }

    if (idx == 0) {
        return -1;
    }

    printf("Escolha qual operacao: ");
    int op; scanf("%d", &op); getchar();
    if (op < 0 || op > idx) {
        return -1;
    }

    aux = JOBS[indice_job];

    while (op > 0) {
        aux = aux->prox;
        op--;
    }

    double tempo_medio = 0;

    for (int i = 0; i < aux->quantidade; i++) {
        tempo_medio += aux->lista_maquinas[i].tempo;
    }

    printf("Tempo medio para executar a operacao eh: %.2lf\n", tempo_medio / aux->quantidade);
    return 1;
}
/// <summary>
/// remover job
/// </summary>
/// <returns></returns>
int remover_job() {
    int indice_job = escolher_job(1);
    if (indice_job == -1) {
        return -1;
    }

    free(JOBS[indice_job]);

    for (int i = indice_job; JOBS[i] != NULL; i++) {
        JOBS[i] = JOBS[i + 1];
    }

    return 1;
}

/// <summary>
/// menu
/// </summary>
/// <returns></returns>
int menu() {
    system("cls");
    printf("1  - Inserir job\n");
    printf("2  - Remover job\n");
    printf("3  - Alterar job\n");
    printf("4  - Criar Job\n");
    printf("5  - Listar Job\n");
    printf("6  - Salvar\n");
    printf("7  - Carregar\n");
    printf("8  - Listar tempo minimo para completar o Job\n");
    printf("9  - Listar tempo maximo para completar o Job\n");
    printf("10 - Listar tempo medio para completar uma Operacao\n");
    printf("11 - Remover Job\n");
    printf("12 - Mostrar Process Plan dos Jobs\n");
    printf("13 - Sair\n");
    int n; scanf("%d", &n);
    getchar();

    if (n < 1 || n > 13) {
        return -1;
    }

    return n;
}

void print_chars(char ch, int count, int newline) {
    for (int i = 0; i < count; i++) {
        printf("%c", ch);
    }

    if (newline == 1) {
        printf("\n");
    }
}

/// <summary>
/// Proposta de escalonamento
/// </summary>
void mostrar_tabela() {
    char* str1 = "Process Plan";
    int len_str1 = strlen(str1);
    char* str2 = "Operation";
    int len_str2 = strlen(str2);

    system("cls");

    printf("%s", str1);
    print_chars(' ', 7, 0);
    printf("%s\n", str2);

    int idx = 0;
    char buf[10];
    while (JOBS[idx] != NULL) {
        printf("%d", idx);
        _itoa(idx, buf, 10);
        print_chars(' ', strlen(str1) - strlen(buf) + 7, 0);
        lista* aux = JOBS[idx];

        int tempo_min = 100000;
        int id;

        while (aux != NULL) {
            for (int i = 0; i < aux->quantidade; i++) {
                if (tempo_min > aux->lista_maquinas[i].tempo) {
                    tempo_min = aux->lista_maquinas[i].tempo;
                    id = aux->lista_maquinas[i].id;
                }
            }

            printf("[%d, %d]", id, tempo_min);
            if (aux->prox != NULL) {
                printf(" ---> ");
            }

            aux = aux->prox;
        }
        printf("\n");
        idx++;
    }
}
