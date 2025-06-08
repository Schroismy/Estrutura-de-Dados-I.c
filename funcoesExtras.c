#include "definicoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ARVORE *busca_valor(ARVORE *r, int valor) {
  if (r == NULL)
    return NULL;
  if (r->valor == valor)
    return r;
  if (valor < r->valor)
    return busca_valor(r->e, valor);
  else
    return busca_valor(r->d, valor);
}

ARVORE *busca_nome(ARVORE *r, char *nome) {
  if (r == NULL)
    return NULL;
  if (strcmp(r->nome, nome) == 0)
    return r;

  ARVORE *e = busca_nome(r->e, nome);
  if (e != NULL)
    return e;

  return busca_nome(r->d, nome);
}

void desaloca(ARVORE *r) {
  if (r == NULL)
    return;
  desaloca(r->e);
  desaloca(r->d);
  free(r);
}
double contabiliza(ARVORE *r) {
  if (r == NULL)
    return 0.0;
  return r->salario + contabiliza(r->e) + contabiliza(r->d);
}
