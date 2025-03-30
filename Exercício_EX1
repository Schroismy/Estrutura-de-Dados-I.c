#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura para os alunos
typedef struct {
  int Matricula;
  double G1, G2, MEDIA;
} aluno;

// Função para comparar médias (usada para ordenar)
int comparaMEDIA(const void *a, const void *b) {
  aluno *alunoA = (aluno *)a;
    aluno *alunoB = (aluno *)b;
  if (alunoA->MEDIA < alunoB->MEDIA)
    return -1;
  else if (alunoA->MEDIA > alunoB->MEDIA)
    return 1;
  return 0;
}

int main() {
  int n, i, maiorMEDIAIndex = 0;

  // Perguntar quantos alunos serão cadastrados
  printf("Quantos alunos você quer cadastrar? ");
  scanf("%d", &n);
  printf("\n");

  // Alocar vetor de alunos
    aluno *alunos = (aluno *)malloc(n * sizeof(aluno));
  if (alunos == NULL) {
    printf("Erro de memória!\n");
    return 1;
  }

  // Ler dados dos alunos
  for (i = 0; i < n; i++) {
    printf("Digite matricula do aluno %d: ", i + 1);
    scanf("%d", &alunos[i].Matricula);
    printf("Digite nota da G1 do aluno %d: ", i + 1);
    scanf("%lf", &alunos[i].G1);
    printf("Digite nota da G2 do aluno %d: ", i + 1);
    scanf("%lf", &alunos[i].G2);
    printf("\n");
    alunos[i].MEDIA = (alunos[i].G1 + alunos[i].G2) / 2.0;
    // Verifica se este aluno tem a maior média
    if (alunos[i].MEDIA > alunos[maiorMEDIAIndex].MEDIA) {
      maiorMEDIAIndex = i;
    }
  }

  // Imprimir aluno com maior média
  printf("Aluno que tem a matricula %d tem maior media (%.2lf)\n",
         alunos[maiorMEDIAIndex].Matricula, alunos[maiorMEDIAIndex].MEDIA);

  // Ordenar alunos pela média
  qsort(alunos, n, sizeof(aluno), comparaMEDIA);

  // Imprimir depuração
  printf("===== %d ALUNOS Depuracao =====\n", n);
  for (i = 0; i < n; i++) {
    printf("Matrícula: %d. Nota: %.2lf\n", alunos[i].Matricula,
           alunos[i].MEDIA);
  }

  // Liberar memória
  free(alunos);

  return 0;
}
