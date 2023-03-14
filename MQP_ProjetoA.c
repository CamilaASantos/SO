
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROC 4

// Estrutura de um processo
typedef struct processo processo;
struct processo{
    char nome[50];
    int CPUB;
    int prioridade;
};

// Estrutura para representar uma fila 
typedef struct queue queue;
struct queue{
    processo *procs;
    int tamanho,qtde_procs,inicio,fim;
};

//cria fila
queue *criar_queue(){
    queue *q = malloc(sizeof(queue));
    q->procs =malloc(sizeof(processo) * MAX_PROC);
    q->tamanho=MAX_PROC;
    q->inicio=0;
    q->fim=0;
    q->qtde_procs=0;
    return q;
}
int queue_vazia(queue *q){
    if (q->fim == q->inicio) return 1;
    return 0;
}
// Insere um processo no final da fila
int enqueue(queue *q, processo p) {
    int novo_fim = (q->fim + 1) % q->tamanho;

    //fila cheia
    if (novo_fim == q->inicio) return 0;

    q->procs[q->fim]=p;
    q->fim=novo_fim;
    q->qtde_procs++;
    return 1;
}

// Remove um processo do início da fila
// int dequeue(queue *q, processo *p) {
//     //fila vazia
//     if (q->inicio == q->fim) return 0;    
    
//     *p = q->procs[q->inicio];
//     printf("Rodando processo: %s - CPU burst: %d - Prioridade: %d\n", p->nome, p->CPUB,p->prioridade);
//     for(int i=p->CPUB; i > 0;i--){
//         printf("Processando.... CPU Burst: %d\n",i);
//     }
//     q->inicio = (q->inicio + 1 ) % q->tamanho;
//     q->qtde_procs--;
//     return 1;
// }


int dequeue(queue *q) {
    //fila vazia
    if (q->inicio == q->fim) return 0;    
    
    processo p = q->procs[q->inicio];
    printf("Rodando processo: %s - CPU burst: %d - Prioridade: %d\n", p.nome, p.CPUB,p.prioridade);
    for(int i=p.CPUB; i > 0;i--){
        printf("Processando....\n");
    }
    q->inicio = (q->inicio + 1 ) % q->tamanho;
    q->qtde_procs--;
    printf("Processo finalizado!\n");
    return 1;
}

//Ordena os processos na fila por CPU burst
void sjf(queue *q) {
    processo temp;
    for (int i = 0; i < q->qtde_procs; i++) {
        for(int j = 0; j < q->qtde_procs;j++){
           if(q->procs[j].CPUB>q->procs[i].CPUB){
                temp=q->procs[j];
                q->procs[j]=q->procs[i];
                q->procs[i]=temp;
           }
        }
    }
}

void mostra_queues(queue *q, int prio) {
    printf("\n");
    printf("Queue %d: \n", prio);
    printf("Nome    Burst time    Prioridade\n");   
    if (!queue_vazia(q)) {
        for (int i = 0; i < q->qtde_procs; i++) {
            printf("%s         %d         %d\n", q->procs[i].nome, q->procs[i].CPUB, q->procs[i].prioridade);
        }
    } 
    else {
        printf("Queue vazia!\n");
    }
    

    printf("\n");
}


// Libera fila 
void liberar_queue(queue *q) {
    free(q->procs);
    free(q);    
}

int main() {
    queue *q0=criar_queue();
    queue *q1=criar_queue();
    queue *q2=criar_queue();
    queue *q3=criar_queue();

    int qtde_proc_total=0;

    printf("Por favor, insira a quantidade de processos a serem inseridos:\n");
    scanf("%d",&qtde_proc_total);

    while (qtde_proc_total>(MAX_PROC - 1) * 4){
        printf("Quantidade de processos ultrapassa a quantidade máxima aceita, por favor insira até %d processos",(MAX_PROC - 1) * 4);
        scanf("%d",&qtde_proc_total);
    }
    processo p;
    
    int e=-1;
    for(int i = 0; i < qtde_proc_total; i++){
        int pr,cburst;
        e=-1;
        printf("Insira o nome do processo %d:\n",i);
        scanf("%s",p.nome);
        printf("Insira o CPU Burst do processo %d:\n",i);
        scanf("%d", &cburst);
        printf("Insira a prioridade do processo %d (valores aceitos 0 a 3):\n",i);
        scanf("%d", &pr);
        while(pr != 0 && pr!= 1 && pr != 2 && pr != 3){
            printf("Por favor insira uma prioridade valida! (0 a 3):");
            scanf("%d", &pr);
        }
        p.CPUB=cburst;
        p.prioridade=pr;
        if(pr == 0) {
            e = enqueue(q0,p);
        }
        else if(pr == 1) {
            e = enqueue(q1,p);
        }
        else if(pr == 2) {
            e = enqueue(q2,p);
        }
        else if(pr == 3) {
            e = enqueue(q3,p);
        }
        printf("E %s |Incluido(1) %d :\n",p.nome, e);
    }
    sjf(q0);
    sjf(q1);
    sjf(q2);
    sjf(q3);

    mostra_queues(q0,0);
    mostra_queues(q1,1);
    mostra_queues(q2,2);
    mostra_queues(q3,3);

    int process_atual=-1;

    while (!queue_vazia(q0) || !queue_vazia(q1) || !queue_vazia(q2) || !queue_vazia(q3)) {
        if (!queue_vazia(q0)) {
            process_atual = dequeue(q0);
        } 
        else if (!queue_vazia(q1)) {
            process_atual = dequeue(q1);
        }
        else if (!queue_vazia(q2)) {
            process_atual = dequeue(q2);
        }
        else if(!queue_vazia(q3)) {
            process_atual = dequeue(q3);
        }
   }

    liberar_queue(q0);
    liberar_queue(q1);
    liberar_queue(q2);
    liberar_queue(q3);

    return 0;
}
