/* Funcoes usadas neste código */

/* uma função para ler uma string não vazia de um arquivo.
 * Vantagens sobre o fgets: não armazena o ENTER no final e
 * não le string vazia (com 0 cars). Se não conseguiu ler uma
 * string, retorna ZERO. Se conseguiu retorna o tamanho dela
 * */
#include "definicoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lestringARQ(char s[], int max, FILE *onde) {
  int i = 0;
  char letra;
  static int l = 0;
  static FILE *estou = NULL;

  /* Se passar NULL como 'arquivo' retorna a quantidade de linhas
   * que já foram lidas
   * */
  if (onde == NULL)
    return (l);

  /* Resetar o contator de linhas quando receber um outro arquivo */
  if (onde != estou) {
    l = 0;
    estou = onde;
  }
  for (i = 0; i < (max - 1); i++) {
    letra = fgetc(onde);
    if (feof(onde)) {
      s[i] = 0;
      return (i);
    }
    if ((letra == '\n') && (i == 0)) {
      i = i - 1;
      l++;
      continue;
    }

    if (letra == '\n') {
      l++;
      break;
    }

    s[i] = letra;
  }
  s[i] = 0;
  return (i);
}

int pre(ARVORE *r) {
  if (r == NULL)
    return (0);
  imprimeNO(r);
  pre(r->e);
  pre(r->d);
}

int em(ARVORE *r) {
  if (r == NULL)
    return (0);
  em(r->e);
  imprimeNO(r);
  em(r->d);
}

int pos(ARVORE *r) {
  if (r == NULL)
    return (0);
  pos(r->e);
  pos(r->d);
  imprimeNO(r);
}

// Função para imprimir os dados de um único no, se existir
int imprimeNO(ARVORE *r) {
  if (r) {
    return (printf("%d %5.2lf %s\n", r->valor, r->salario, r->nome));
  }
  return (0); // erro. r é NULL
}

/* Função que le, do arquivo, dados de um nó e retorna o nó lido,
 * sem colocar na árvore. Só leitura de arquivo. Retorna NULL se
 * não pode ler um dado (arquivo chegou ao final ou está mal formado)
 */
ARVORE *ledados(FILE *arq) {
  ARVORE *no;
  char l, linha[MAXLINHA + 1];
  int t;

  do {
    t = lestringARQ(linha, MAXLINHA, arq);
  } while (linha[0] == '#');
  /* O teste '#' é só para permitir que o arquivo tenha comentários.
   * Se uma linha do arquivo começar com # ela será ignorada */

  if (feof(arq)) {
    return (NULL);
  }
  no = malloc(sizeof(ARVORE));
  if (no == NULL) {
    fprintf(stderr, "ERRO ao tentar criar um nó para o dado\n");
    return (NULL);
  }
  if (sscanf(linha, "%d", &no->valor) == 0) {
    /* O arquivo tem algo inesperado. Era para ter valor
     * mas tem outra coisa
     */
    fprintf(stderr, "ERRO na linha %d do arquivo\n",
            lestringARQ(linha, 0, NULL));
    fprintf(stderr, "Esperava um numero, mas tinha \"%s\"\n", linha);
    free(no); // desaloca, pois não será usado
    return (NULL);
  }

  do {
    t = lestringARQ(linha, MAXLINHA, arq);
  } while (linha[0] == '#');

  if (feof(arq)) {
    fprintf(
        stderr,
        "ERRO no arquivo. Chegou ao fim, mas faltou um salario na linha %d\n",
        lestringARQ(linha, 0, NULL) + 1);
    free(no);
    return (NULL);
  }
  if (sscanf(linha, "%lf", &no->salario) == 0) {
    /* nao poder ler salario, já tendo lido valor, é um erro
     * pois indica que o arquivo está mal formado (não tem todos
     * os dados de um nó.
     */
    fprintf(stderr, "ERRO na linha %d do arquivo\n",
            lestringARQ(linha, 0, NULL));
    fprintf(stderr, "Esperava um numero, mas tinha \"%s\"\n", linha);
    free(no);
    return (NULL);
  }

  do {
    t = lestringARQ(linha, MAXLINHA, arq);
  } while (linha[0] == '#');

  if ((t == 0) || (feof(arq))) {
    fprintf(stderr, "ERRO ao ler nome. Arquivo não tem todos os dados.\n");
    fprintf(stderr, "Devia ter um nome na linha %d\n",
            lestringARQ(linha, 0, NULL) + 1);
    free(no);
    return (NULL);
  }

  strncpy(no->nome, linha, MAXSTR);

  if (t > MAXSTR) {
    fprintf(
        stderr,
        "ERRO arquivo. A linha %d tem um nome maior que %d cars suportado\n",
        lestringARQ(linha, 0, NULL), MAXSTR);
    fprintf(stderr, "Ignorado cars do nome que passam de %d cars\n", MAXSTR);
    printf("Tam = %lu\n", strlen(no->nome));
  }

  no->e = NULL;
  no->d = NULL;

  return (no);
}

/* Função para inserir um nó na árvore de busca, ordenada pelo
 * valor. Valor é a chave. Retorna o pai do no inserido ou
 * NULL se não pode inserir.
 * */
ARVORE *insere(ARVORE *no, ARVORE *r) {
  if (r == NULL) {
    return (NULL);
  }
  if (no == NULL) {
    return (NULL);
  }
  if (no->valor == r->valor) {
    fprintf(stderr, "ERRO. Chave %d já existe na árvore.\n", no->valor);
    fprintf(stderr, "Não posso inserir se já existe\n");
    return (NULL);
  }
  if (no->valor < r->valor) {
    /* deve ser inserido à esquerda */
    if (r->e) {
      /* se tem nós à esquerda, desce até um folha */
      return (insere(no, r->e));
    }
    /* Se devia inserir à esquerda e não tem esquerda, então o nó a ser
     * inserido será justamente filho da esquerda e o r será seu pai
     * */
    r->e = no;
    return (r);
  }
  /* Já testou se menor. Se chegou aqui é porque deve descer á direita */
  if (r->d) {
    /* Se tem subárvore á direita, desce nela */
    return (insere(no, r->d));
  }
  /* Se não tem direita (falhou no if anterior) então o nó a ser
   * inserido é filho direito de r
   */
  r->d = no;
  return (r);
}
