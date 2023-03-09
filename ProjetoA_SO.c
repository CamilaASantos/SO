#include <sys/wait.h> /* system call - wait */
#include <stdint.h> /* system call - wait */
#include <stdlib.h> /* system call - exit */
#include <unistd.h> /* system call - fork, exec, sleep
#include <signal.h> /*system call - signal*/
#include <stdio.h>
// Variaveis globais

int file1Open = true; /* Arquivo hipotetico 1 */
int file2Open = true; /* Arquivo hipotetico 2 */
int valor1 = 500;

 void trata_SIGINT (int signum){
  raise(SIGINT);// Chama a função default do SIGINT
 }

 void trata_SIGTERM (int signum){
  raise(SIGINT);
 }

int main()
{
 /* Definicao da funcao em C que ira tratar das interrupcoes */
 // SIGINT (ctrl+c)
sighandler_t signal (SIGINT, trata_SIGINT);
// SIGTERM (kill)
sighandler_t signal (SIGTERM, trata_SIGTERM);
  
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
wait(NULL);
while (1);
printf("O status do file1Open eh %d e o file2Open eh %d \n", file1Open,
file2Open);
printf(" O valor1 = %d\n",valor1);
return 0;
}
}
