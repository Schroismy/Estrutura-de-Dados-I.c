#include <stdio.h>
#include <stdlib.h>

typedef struct ALUNOS {
  int MATRICULA;
  double G1, G2, Media;
  struct ALUNOS *prox;
} Aluno;

// Função para criar um novo nó de aluno
Aluno *criarAluno(int MATRICULA, double G1, double G2) {
  Aluno *novo = (Aluno *)malloc(sizeof(Aluno));
  novo->MATRICULA = MATRICULA;
  novo->G1 = G1;
  novo->G2 = G2;
  novo->Media = 0.0; // calcularemos depois
  novo->prox = NULL;
  return novo;
}

// Função para inserir no final da lista
void inserirAluno(Aluno **head, Aluno *novo) {
  if (*head == NULL) {
    *head = novo;
  } else {
    Aluno *atual = *head;
    while (atual->prox != NULL) {
      atual = atual->prox;
    }
    atual->prox = novo;
  }
}

// Função para calcular as médias
void calcularMedias(Aluno *head) {
  while (head != NULL) {
    head->Media = (head->G1 + head->G2) / 2.0;
    head = head->prox;
  }
}

// Função para encontrar o aluno com maior média
Aluno *alunoMaiorMedia(Aluno *head) {
  if (head == NULL)
    return NULL;
  Aluno *maior = head;
  while (head != NULL) {
    if (head->Media > maior->Media) {
      maior = head;
    }
    head = head->prox;
  }
  return maior;
}

// Função para ordenar a lista pela média (bubble sort adaptado para lista encadeada)
void ordenarPorMedia(Aluno **head) {
  if (*head == NULL || (*head)->prox == NULL)
    return;

  int trocado;
  Aluno *ptr1, *lptr = NULL;

  do {
    trocado = 0;
    ptr1 = *head;

    while (ptr1->prox != lptr) {
      if (ptr1->Media < ptr1->prox->Media) {
        // Trocar os dados dos nós (em vez de mexer nos ponteiros)
        int tempMat = ptr1->MATRICULA;
        double tempG1 = ptr1->G1, tempG2 = ptr1->G2, tempMedia = ptr1->Media;

        ptr1->MATRICULA = ptr1->prox->MATRICULA;
        ptr1->G1 = ptr1->prox->G1;
        ptr1->G2 = ptr1->prox->G2;
        ptr1->Media = ptr1->prox->Media;

        ptr1->prox->MATRICULA = tempMat;
        ptr1->prox->G1 = tempG1;
        ptr1->prox->G2 = tempG2;
        ptr1->prox->Media = tempMedia;

        trocado = 1;
      }
      ptr1 = ptr1->prox;
    }
    lptr = ptr1;
  } while (trocado);
}

// Imprimir todos os alunos que precisam fazer substitutiva (média < 6.0)
void imprimirSubstitutiva(Aluno *head) {
  printf("\nAlunos que precisam de substitutiva (media < 6.0):\n");
  while (head != NULL) {
    if (head->Media < 6.0) {
      printf("Matricula: %d | G1: %.2lf | G2: %.2lf | Media: %.2lf\n",
             head->MATRICULA, head->G1, head->G2, head->Media);
    }
    head = head->prox;
  }
}

// Imprimir todos os alunos
void imprimirTodos(Aluno *head) {
  printf("\nLista de alunos ordenada por media:\n");
  while (head != NULL) {
    printf("Matricula: %d | G1: %.2lf | G2: %.2lf | Media: %.2lf\n",
           head->MATRICULA, head->G1, head->G2, head->Media);
    head = head->prox;
  }
}

int main() {
  Aluno *lista = NULL;
  char opcao;
  int MATRICULA;
  double G1, G2;
  int primeiro = 1; // variável de controle para pular linha

  do {
    if (!primeiro) {
      printf("\n"); // pula linha depois do primeiro aluno
    }
    primeiro = 0;

    printf("Digite a matricula do aluno: ");
    scanf("%d", &MATRICULA);
    printf("Digite a nota da G1: ");
    scanf("%lf", &G1);
    printf("Digite a nota da G2: ");
    scanf("%lf", &G2);

    Aluno *novo = criarAluno(MATRICULA, G1, G2);
    inserirAluno(&lista, novo);
    printf("\n");
    printf("Deseja cadastrar outro aluno? (s/n): ");
    scanf(" %c", &opcao); // espaço antes do %c para ignorar newline
  } while (opcao == 's' || opcao == 'S');

  printf("\n");

  calcularMedias(lista);

  Aluno *melhor = alunoMaiorMedia(lista);
  if (melhor != NULL) {
    printf("\nAluno com maior media:\n");
    printf("Matricula: %d | G1: %.2lf | G2: %.2lf | Media: %.2lf\n",
           melhor->MATRICULA, melhor->G1, melhor->G2, melhor->Media);
  }

  ordenarPorMedia(&lista);

  imprimirTodos(lista);
  imprimirSubstitutiva(lista);

  return 0;
}

