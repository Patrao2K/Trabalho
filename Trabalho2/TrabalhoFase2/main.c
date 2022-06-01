/*
* Project: TrabalhoFase2
* Purpose: Licenciatura de Engenharia Informática Médica
* Company: IPCA
* Created by: Joao
* Created on: 16/05/2022
* Email: a21210@alunos.ipca.pt
**/


#include "eda1.h"

/// <summary>
/// Programa principal 
/// </summary>
/// <returns></returns>
int main() {
    while (1) {
        switch (menu()) {
        case 1: {
            int ret = inserir_operacao();
            if (ret == -1) {
                printf("Nao foi possivel inserir um novo job\n");
            }
            getchar();
            break;
        }

        case 2: {
            int ret = remover_operacao();
            if (ret == -1) {
                printf("Nao foi possivel remover o job\n");
            }
            else {
                printf("O job foi removido com sucesso\n");
            }
            getchar();
            break;
        }

        case 3: {
            int ret = alterar_operacao();
            if (ret == -1) {
                printf("Nao foi possivel alterar o job\n");
            }
            else {
                printf("Job alterado com sucesso\n");
            }

            getchar();
            break;
        }

        case 4: {
            criar_job();
            printf("Job criado com sucesso\n");
            getchar();
            break;
        }

        case 5: {
            int ret = lista_operacoes_job();
            if (ret == -1) {
                printf("Nao foi possivel listar as operacoes\n");
            }
            getchar();
            break;
        }

        /// <summary>
        /// Faz a gravação
        /// </summary>
        /// <returns></returns>
        case 6: {
            char buf[50];
            printf("Digite o nome do arquivo que voce deseja salvar os jobs: ");
            scanf("%s", buf);
            FILE* fp = fopen(buf, "w");

            if (fp == NULL) {
                printf("Nao foi possivel salvar o arquivo\n");
                getchar();
                break;
            }

            int idx = 0;

            while (JOBS[idx] != NULL) {
                lista* aux = JOBS[idx];

                int tam = tamanho_lista(JOBS[idx]);

                
                fprintf(fp, "%d\n", tam);

                for (int i = 0; i < tam; i++) {
                    fprintf(fp, "%d\n", aux->quantidade);
                    for (int i = 0; i < aux->quantidade; i++) {
                        fprintf(fp, "%d %d\n", aux->lista_maquinas[i].id, aux->lista_maquinas[i].tempo);
                    }
                    aux = aux->prox;
                }

                idx++;
            }

            printf("Jobs salvos com sucesso\n");
            fclose(fp);
            getchar();
            break;
        }
        /// <summary>
        /// Carrega os ficheiros
        /// </summary>
        /// <returns></returns>
        case 7: {
            char buf[50];
            printf("Digite o nome do arquivo que voce deseja carregar os dados: ");
            scanf("%s", buf);
            getchar();
            FILE* fp = fopen(buf, "r");

            if (fp == NULL) {
                printf("Nao foi possivel abrir o arquivo\n");
                getchar();
                break;
            }

            int jobs_qtd;
            int idx = 0;

            while (fscanf(fp, "%d", &jobs_qtd) != EOF) {
                JOBS[idx] = (lista*)malloc(sizeof(lista));
                JOBS[idx]->quantidade = 0;
                JOBS[idx]->prox = NULL;
                lista* aux = JOBS[idx];
                for (int i = 0; i < jobs_qtd; i++) {
                    int op_qtd; fscanf(fp, "%d", &op_qtd);
                    aux->quantidade = op_qtd;
                    for (int j = 0; j < op_qtd; j++) {
                        maquina maq;
                        fscanf(fp, "%d %d", &maq.id, &maq.tempo);
                        aux->lista_maquinas[j] = maq;
                    }

                    if (i + 1 >= jobs_qtd) continue;

                    aux->prox = (lista*)malloc(sizeof(lista));
                    aux->prox->quantidade = 0;
                    aux->prox->prox = NULL;
                    aux = aux->prox;
                }

                idx++;
            }

            fclose(fp);
            printf("Arquivo carregado com sucesso\n");
            getchar();
            break;
        }

        case 8: {
            int ret = listar_tempo_minimo();
            if (ret == -1) {
                printf("Nao foi possivel listar o tempo do respectivo Job\n");
            }
            getchar();
            break;
        }

        case 9: {
            int ret = listar_tempo_maximo();
            if (ret == -1) {
                printf("Nao foi possivel listar o tempo do respectivo Job\n");
            }
            getchar();
            break;
        }

        case 10: {
            int ret = listar_tempo_medio();
            if (ret == -1) {
                printf("Nao foi possivel calcular o tempo medio do Job\n");
            }
            getchar();
            break;
        }

        case 11: {
            int ret = remover_job();
            if (ret == -1) {
                printf("Nao foi possivel remover o Job\n");
            }
            else {
                printf("Job removido com sucesso\n");
            }
            getchar();
            break;
        }

        case 12: {
            mostrar_tabela();
            getchar();
            break;
        }

        case 13: {
            return 0;
        }

        default:
            break;
        }
    }

    return 0;
}