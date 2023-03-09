#include <sys/wait.h> /* system call - wait */
#include <stdint.h> /* system call - wait */
#include <stdlib.h> /* system call - exit */
#include <unistd.h> /* system call - fork, exec, sleep*/
#include <signal.h> /*system call - signal*/
#include <stdio.h>
// Variaveis globais

int file1Open = 1; /* Arquivo hipotetico 1 */
int file2Open = 1; /* Arquivo hipotetico 2 */
int valor1 = 500;

 void trata_SIGINT (int signum){
  char c;
  printf("Verifiquei a solicitação de parada pelo comando ctrl+c, você realmente deseja encerrar o processo? Caso sim, digite 'x', se não, digite 'o':\n");
  scanf("%c", &c);
  if(c == 'x' || c  == 'X'){
   file1Open = 0;
   file2Open = 0;
   printf("Fechando arquivos file1Open e file2Open...\n");
   printf("O valor1 eh de: %d", valor1);
   exit(0);
    }
 }

 void trata_SIGTERM (int signum){
   file1Open = 0;
   file2Open = 0;
   printf("Fechando arquivos file1Open e file2Open...\n");
   printf("O valor1 eh de: %d", valor1);
   exit(0);
 }

int main()
{
 /* Definicao da funcao em C que ira tratar das interrupcoes */
 // SIGINT (ctrl+c)
signal (SIGINT, trata_SIGINT);
// SIGTERM (kill)
signal (SIGTERM, trata_SIGTERM);
  
pid_t pid;
pid = fork();
if (!pid)
{
printf( "Sou o FILHO. %d\n", getpid() );
return 0;
}
else if (pid)
{
printf( "Sou o PAI. %d\n", getpid() );
valor1 /= 20;
//wait(NULL);
while (1);
printf("O status do file1Open eh %d e o file2Open eh %d \n", file1Open,
file2Open);
printf(" O valor1 = %d\n",valor1);
return 0;
}
}
