#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>

typedef struct {
    char titulo[30], diretor[30], genero[30], idiomaOriginal[30];
    int anoLancamento;
    float nota;
} Filmes;

FILE *abrirArquivoCSV(const char *filmesListagemCSV);
FILE *abrirArquivoBIN(const char *filmesListagemBIN);
int realizarEscolha();
void inclusao();
void opcoes();
void listagem2();
void exclusao();
void selecao();

#endif