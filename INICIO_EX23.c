//César Schroeder- Fez tudo.


#include "definicoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef GABARITO
#include "resp.c"
#endif

int main(int argc, char *argv[]) {
  ARVORE *r = NULL;  // Raiz da árvore
  ARVORE *no = NULL; // Nó temporário
  ARVORE *resp = NULL;
  double totsal = 0;

  int total = 0;
  FILE *arq;
  int valor;
  char nome[MAXSTR + 1];

  if (argc < 2) {
    fprintf(stderr,
            "ERRO. Você precisa fornecer o nome do arquivo com os dados\n");
    fprintf(stderr, "Sintaxe: %s arquivo.txt\n", argv[0]);
    return 1;
  }

  arq = fopen(argv[1], "r");
  if (arq == NULL) {
    fprintf(stderr, "ERRO. Não pude abrir o arquivo \"%s\" para leitura\n",
            argv[1]);
    return 2;
  }

  while (!feof(arq)) {
    no = ledados(arq);
    if (no == NULL) {
      break;
    }
    if (r == NULL) {
      r = no;
      total = 1;
      continue;
    }
    if (insere(no, r) == NULL) {
      free(no);
    } else {
      total++;
    }
  }
  fclose(arq);

  printf("\n==================================\n");
  printf("Lido %d nos do arquivo \"%s\"", total, argv[1]);
  printf("\n==================================\n\n");

  printf("Depuração: percurso pre-ordem\n");
  pre(r);
  printf("\n\n");

  printf("Depuração: percurso em em-ordem\n");
  em(r);
  printf("\n\n");

  printf("Depuração: percurso em pós-ordem\n");
  pos(r);
  printf("\n\n");

  // Busca por valor
  printf("Digite um valor a ser buscado:\n");
  scanf("%d", &valor);
  resp = busca_valor(r, valor);

  if (resp == NULL) {
    printf("%d não encontrado na árvore\n", valor);
  } else {
    printf("Achei %d\n", valor);
    printf("%d %7.2lf\n", resp->valor, resp->salario);
  }

  // Limpa buffer e busca por nome
  printf("Digite um nome a ser encontrado:\n");
  while (getchar() != '\n')
    ;
  lestringARQ(nome, MAXSTR, stdin);

  resp = busca_nome(r, nome);
  if (resp == NULL) {
    printf("%s não encontrado na árvore\n", nome);
  } else {
    printf("Achei: %s\n", resp->nome);
  }

  // Contabiliza salários
  double contabiliza(ARVORE * r); // Prototype for contabiliza
  totsal = contabiliza(r);
  printf("Total de salarios = R$ %7.2lf\n", totsal);

  // Desaloca memória da árvore
  void desaloca(ARVORE * r); // Prototype for desaloca
  desaloca(r);
}
