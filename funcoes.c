#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

FILE *abrirArquivoCSV(const char *filmesListagemCSV) {
  FILE *arquivo = fopen(filmesListagemCSV, "a+");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo CSV.\n");
    return NULL;
  }
  return arquivo;
}

FILE *abrirArquivoBIN(const char *filmesListagemBIN) {
  FILE *arquivo = fopen(filmesListagemBIN, "ab");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo binário.\n");
    return NULL;
  }
  return arquivo;
}

int realizarEscolha() {
    int escolha;

    printf("O que deseja fazer agora?\n\n");
    printf("1. Quero voltar ao menu.\n");
    printf("2. Sair.\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            printf("\n");
            break;
        case 2:
            printf("\nEncerrando o programa, até logo!\n");
            exit(0);
            break;
        default:
            printf("\nOops, acho que você se enganou! Volte ao Menu e\ntente novamente.\n\n");
            break;
    }

    return escolha;
}

void inclusao() {
  FILE* arquivobin = fopen("filmesListagemBIN.bin", "ab");
  FILE* arquivocsv = fopen("filmesListagemCSV.csv", "a");

  if (arquivobin == NULL || arquivocsv == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
  }

  Filmes filmes;

  printf("\nVamos incluir um filmezinho:\n\n");

  printf("Qual o Título do filme? ");
  scanf(" %[^\n]", filmes.titulo);

  printf("Me diga o diretor: ");
  scanf(" %[^\n]", filmes.diretor);

  printf("Digite o gênero: ");
  scanf(" %[^\n]", filmes.genero);

  printf("Qual o idioma original do filme? ");
  scanf(" %[^\n]", filmes.idiomaOriginal);

  printf("Em que ano foi lançado? ");
  scanf("%d", &filmes.anoLancamento);

  if (filmes.anoLancamento > 2023 || filmes.anoLancamento < 1895) {
    printf("\nAno inválido, volte ao menu e tente novamente!\n\n");
    exit(1);
  }

  printf("Por fim, avalie o filme com uma nota de 0 a 10: ");
  scanf("%f", &filmes.nota);

  if (filmes.nota > 10 || filmes.nota < 0) {
    printf("\nNota inválida, volte ao menu e tente novamente!\n\n");
    exit(1);
  }

  if (filmes.nota <= 6) {
    printf("\n ~ Realmente esse filme eh bem ruinzinho...\n");
  } else {
    printf("\n ~ %s eh um clássico!\n", filmes.titulo);
  }

  // Escrever no arquivo CSV
  fprintf(arquivocsv, "%s,%s,%s,%s,%d,%.2f;\n", filmes.titulo,
          filmes.diretor, filmes.genero, filmes.idiomaOriginal,
          filmes.anoLancamento, filmes.nota);

  // Escrever no arquivo binário
  fwrite(&filmes, sizeof(Filmes), 1, arquivobin);

  fclose(arquivobin);
  fclose(arquivocsv);

  printf("\nTodos os dados foram salvos com sucesso!\n\n");
}

void opcoes(FILE *filmesListagemBIN, FILE *filmesListagemCSV) {
  
  int escolha;
  printf("O que deseja fazer agora?\n\n");
  printf("1. Incluir mais um filme!\n");
  printf("2. Quero voltar ao menu.\n");
  printf("3. Sair.\n");
  scanf("%d", &escolha);

  switch (escolha) {
  case 1: {
    printf("Inclua mais um filme: \n\n");
    inclusao(filmesListagemBIN, filmesListagemCSV);
    break;
  }
  case 2:
    printf("\n");
    break;
  case 3:
    printf("\nEncerrando o programa, até loguinho!\n");
    exit(0);
    break;
  default:
    printf("\nOops, acho que você se enganou! Volte ao Menu e\ntente "
           "novamente.\n\n");
    break;
  }
}

void listagem2() {
  FILE *arquivo = fopen("filmesListagemBIN.bin", "rb");
  Filmes filmes;

  while (fread(&filmes, sizeof(Filmes), 1, arquivo) == 1) {
    // Exibir os dados do registro lido
    printf("Título: %s\n", filmes.titulo);
    printf("Diretor: %s\n", filmes.diretor);
    printf("Gênero: %s\n", filmes.genero);
    printf("Idioma: %s\n", filmes.idiomaOriginal);
    printf("Ano de Lançamento: %d\n", filmes.anoLancamento);
    printf("Nota: %.2f\n", filmes.nota);
    printf("\n");
  }
  
  fclose(arquivo);
  realizarEscolha();
}

void exclusao() {
    FILE* arquivobin = fopen("filmesListagemBIN.bin", "w");
    FILE* arquivocsv = fopen("filmesListagemCSV.csv", "w");
    char resposta;

    printf("\nDeseja apagar todos os dados registrados? (S/N): ");
    scanf(" %c", &resposta);

    if (resposta == 'S' || resposta == 's') {
        char confirmacao;

        printf("Tem certeza de que deseja apagar todos os dados?\nEssa acao nao pode ser desfeita! (S/N): ");
        scanf(" %c", &confirmacao);

        if (confirmacao == 'S' || confirmacao == 's') {
            // Removendo o arquivo CSV
            if (remove("filmesListagemCSV.csv") == 0) {
                printf("Arquivo CSV removido com sucesso.\n");
            } else {
                printf("Erro ao remover o arquivo CSV.\n");
                exit(1);
            }

            // Removendo o arquivo binário
            if (remove("filmesListagemBIN.bin") == 0) {
                printf("Arquivo binário removido com sucesso.\n");
            } else {
                printf("Erro ao remover o arquivo binário.\n");
                exit(1);
            }

            printf("Todos os dados foram removidos com sucesso!\n");
        } else {
            printf("Exclusao cancelada. Os dados nao foram apagados.\n");
        }
    } else {
        printf("Operacao cancelada. Os dados nao foram apagados.\n");
    }

    fclose(arquivobin);
    fclose(arquivocsv);
}

void selecao() {
    FILE* arquivo = fopen("filmesListagemBIN.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int opcao;
    printf("\nSelecione o(s) filme(s) pela categoria:\n");
    printf("1. Incluir item\n");
    printf("2. Diretor do filme\n");
    scanf("%d", &opcao);

    char busca[30];
    printf("\nDigite o valor para busca: ");
    scanf(" %[^\n]", busca);

    printf("\nResultados da busca:\n");

    Filmes filmes;
    int encontrado = 0;

    switch (opcao) {
        case 1: // Título do filme
            while (fread(&filmes, sizeof(Filmes), 1, arquivo) == 1) {
                if (strcmp(busca, filmes.titulo) == 0) {
                    printf("Título: %s\n", filmes.titulo);
                    printf("Diretor: %s\n", filmes.diretor);
                    printf("Gênero: %s\n", filmes.genero);
                    printf("Idioma Original: %s\n", filmes.idiomaOriginal);
                    printf("Ano de Lançamento: %d\n", filmes.anoLancamento);
                    printf("Nota: %.2f\n\n", filmes.nota);
                    encontrado = 1;
                }
            }
            break;

        case 2: // Diretor do filme
            printf("Filmes do Diretor %s:\n", busca);
            while (fread(&filmes, sizeof(Filmes), 1, arquivo) == 1) {
                if (strcmp(busca, filmes.diretor) == 0) {
                    printf("Título: %s\n", filmes.titulo);
                    printf("Diretor: %s\n", filmes.diretor);
                    printf("Gênero: %s\n", filmes.genero);
                    printf("Idioma Original: %s\n", filmes.idiomaOriginal);
                    printf("Ano de Lançamento: %d\n", filmes.anoLancamento);
                    printf("Nota: %.2f\n\n", filmes.nota);
                    encontrado = 1;
                }
            }
            break;

        default:
            printf("Opção inválida.\n");
            break;
    }

    if (!encontrado) {
        printf("Nenhum resultado encontrado.\n");
    }

    // Fechando o arquivo
    fclose(arquivo);
}