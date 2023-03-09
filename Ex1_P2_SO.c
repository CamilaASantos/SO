    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    #define MAX 10;
    int RECURSO_MAXIMO = MAX;

    typedef struct lock_t {
      int flag;
    } lock_t;

    int CompareAndSwap(int *ptr, int expected, int new) {
      int actual = *ptr;
      if (actual == expected) {
    	*ptr = new;
      }
      return actual;
    }

    void init(lock_t *mutex) { mutex->flag = 0; }

    void lock(lock_t *mutex) {
      while (CompareAndSwap(&mutex->flag, 0, 1) == 1)
    	;
    }

    void unlock(lock_t *mutex) { mutex->flag = 0; }

    // Essa funcao aloca a quantidade de recursos desejada, se existir
    void *aloca_recurso(void *rec) {
        int recurso_desejado = (int *)rec;
      lock_t *MUTEX;
      init(MUTEX);
      lock(MUTEX);

    if (RECURSO_MAXIMO < recurso_desejado){
        printf("Recurso não alocado!\n Valor do recurso desejado: %d \nValor RECURSO_MAXIMO: %d\n", recurso_desejado, RECURSO_MAXIMO);
        unlock(MUTEX);
        return -1;
    } else {
        RECURSO_MAXIMO -= recurso_desejado;
        unlock(MUTEX);
        printf("Recurso alocado no valor de %d, o RECURSO_MAXIMO agora possui valor: %d\n", recurso_desejado,RECURSO_MAXIMO);
        return 0;
    }
    }

    // Essa funcao devolve uma certa quantidade de recursos alocados
    void *desaloca_recurso(void *rec) {
        int recurso_devolvido = (int *)rec;
      lock_t *MUTEX;
      init(MUTEX);
      lock(MUTEX);
    RECURSO_MAXIMO += recurso_devolvido;
    printf("Recurso devolvido, RECURSO_MÁXIMO atual: %d\n",RECURSO_MAXIMO);
      unlock(MUTEX);
    
    return 0;
    }

    int main(void) {
    int i = 0;
    int err;
    int recurso = rand() % 10 + 1;
    void *ptr=recurso;
    // Dois ponteiros de threads
    pthread_t tid[2];

    while (i < 2) {
        pthread_create(&(tid[i]), NULL, aloca_recurso(ptr), (void *)i);
        pthread_create(&(tid[i]), NULL, desaloca_recurso(ptr), (void *)i);
        i++;
    }
    
    // Junção das threads
    (void)pthread_join(tid[0], NULL);
    (void)pthread_join(tid[1], NULL);

    pthread_exit(NULL);

    return 0;
    }
