
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Estrutura para os dados de um aluno
typedef struct {
 int matricula;
 float g1;
 float g2;
 float media;
} Aluno;
// Estrutura da pilha
typedef struct {
 Aluno *alunos;
 int topo;
 int capacidade;
} Pilha;
// Função para verificar se a pilha está vazia
int empty(Pilha *p) { return (p->topo == -1); }
// Função para empilhar um aluno
void push(Pilha *p, Aluno a) {
 if (p->topo == p->capacidade - 1) {
 
printf("Pilha cheia! Não é possível empilhar mais alunos.\n");
 
return;
 }
 p->alunos[++(p->topo)] = a;
}
// Função para desempilhar um aluno
Aluno pop(Pilha *p) {
 Aluno vazio = {0, 0, 0, 0};
 if (empty(p)) {
 
printf("Pilha vazia! Não é possível desempilhar.\n");
 
return vazio;
 }
 return p->alunos[(p->topo)--];
}
// Função para buscar um aluno pela matrícula (modo LIFO)
void buscarPorMatricula(Pilha *p, int matricula) {
 int encontrado = 0;
 for (int i = p->topo; i >= 0; i--) {
 
if (p->alunos[i].matricula == matricula) {
 
printf("\nAluno encontrado:\n");
 
printf("Matrícula: %d\n", p->alunos[i].matricula);
 
printf("G1: %.2f\n", p->alunos[i].g1);
 
printf("G2: %.2f\n", p->alunos[i].g2);
 
printf("Média: %.2f\n", p->alunos[i].media);
 
encontrado = 1;
 
break;
 
}
 }
 if (!encontrado) {
 
printf("Aluno com matrícula %d não encontrado.\n", matricula);
 }
}
int main() {
 Pilha pilha;
 int limite;
 printf("Informe o limite da pilha (quantidade máxima de alunos): ");
 scanf("%d", &limite);
 pilha.capacidade = limite;
 pilha.topo = -1;
 pilha.alunos = (Aluno *)malloc(limite * sizeof(Aluno));
 if (pilha.alunos == NULL) {
 
printf("Erro ao alocar memória para a pilha.\n");
 
return 1;
 }

 int opcao;
 do {
 
printf("\nMenu:\n");
 
printf("1 → Empilhar aluno\n");
 
printf("2 → Desempilhar aluno\n");
 
printf("3 → Buscar aluno por matrícula\n");
 
printf("4 → Sair\n");
 
printf("\nEscolha uma opção: ");
 
scanf("%d", &opcao);
 
if (opcao == 1) {
 
Aluno a;
 
printf("Informe a matrícula: ");
 
scanf("%d", &a.matricula);
 
printf("Informe a nota da G1: ");
 
scanf("%f", &a.g1);
 
printf("Informe a nota da G2: ");
 
scanf("%f", &a.g2);
 
a.media = (a.g1 + a.g2) / 2;
 
push(&pilha, a);
 
} else if (opcao == 2) {
 
Aluno removido = pop(&pilha);
 
if (removido.matricula != 0) {
 
printf("Aluno desempilhado:\n");
 
printf("Matrícula: %d, G1: %.2f, G2: %.2f, Média: %.2f\n",
 
removido.matricula, removido.g1, removido.g2, removido.media);
 
}
 
} else if (opcao == 3) {
 
int mat;
 
printf("Informe a matrícula a ser buscada: ");
 
scanf("%d", &mat);
 
buscarPorMatricula(&pilha, mat);
 
}
 } while (opcao != 4);
 free(pilha.alunos);
 return 0;
