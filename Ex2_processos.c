#include <sys/wait.h> /* system call - wait */
#include <stdint.h> /* system call - wait */
#include <stdlib.h> /* system call - exit */
#include <unistd.h> /* system call - fork, exec, sleep */
#include <stdio.h>

int G[]={0,1,2,3,4};

int main()
{
    int p= fork ();
    
    if(p == 0){//filho
        printf("Filho:\n");
        for (int i = 0; i < 5; i++)
        {
            G[i]=G[i]-1;
            printf("%d ", G[i]);
        }  
        printf("\n");
    }
    else{//pai
        sleep(2);
        printf("Pai:\n");
        for (int i = 0; i < 5; i++)
        {
        printf("%d ", G[i]);
        }
         printf("\n");
    }
    
    return 0;
}
