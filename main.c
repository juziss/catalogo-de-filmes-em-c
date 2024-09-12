#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    FILE *filmesListagemBIN = abrirArquivoBIN("filmesListagemBIN.bin");
    FILE *filmesListagemCSV = abrirArquivoCSV("filmesListagemCSV.csv");

    if (filmesListagemBIN == NULL || filmesListagemCSV == NULL) {
        return 1;
    }

    int opcao;

    do {
        printf("================ MENU PRINCIPAL ================\n\n");
        printf("Seja bem vindo ao seu catálogo de filmes perso-\nnalizado ~luz, "
               "camera e acao!\n");
        printf("\n-> Escolha uma opcao:\n\n");
        printf("1. INCLUSAO\t 2. LISTAGEM\t 3. EXCLUSAO\n4. SELECAO\t 0. SAIR\n");
        scanf("%d", &opcao);
        printf("================================================\n");

        switch (opcao) {
            case 1:
                inclusao();
                opcoes();
                break;
            case 2:
                listagem2();
                break;
            case 3:
                exclusao();
                break;
            case 4:
                selecao();
                break;
            case 0:
                printf("Encerrando, ate loguinhoo...\n");
                break;
            default:
                printf("Oops, acho que você se enganou! Por favor, escolha novamente ^^\n\n");
                break;
        }
    } while (opcao != 0);

    fclose(filmesListagemBIN);
    fclose(filmesListagemCSV);

    return 0;
}