#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/signal.h>

#define QTD_THREADS 10

double var_global; // declara a variável global do tipo double

void *funcao_thread(void *param) // essa função receberá o valor inteiro
{
  time_t t;
  // int x = *(int*)param;
  long x = (long)param;
  // srand((unsigned)time(&t));
  // x = rand() % 10;
  int sono_aleatorio;

  if (x % 2 == 0)
  {
    for (int i = 0; i < 50; i++)
    {
      time_t t;
      var_global++;

      // srand((unsigned)time(&t));
      sono_aleatorio = (rand() % 5) + 1;
      printf("sou a thread i: %ld var global: %0.f vou dormir durante %d s\n", x, var_global, sono_aleatorio); 
      sleep(sono_aleatorio); // dorme no
    }
    // printa a thread, o var global, e os segundos que ela vai dormir
  }
  else
  {

    for (int z = 0; z < 30; z++)
    {
      var_global--; // faz o decremento 30x
      printf("sou a thread i: %ld var global: %0.f vou dormir durante 2s\n", x, var_global);  
      sleep(2);
    }
     // printa a thread, o var global, e os segundos que ela vai dormir
  }

  // free(param);
}

int main(int argc, char *argv[])
{
  /*
  int fork_return; // valor de retorno do fork
  int prowait;
  int origemwait;

  fork_return = fork();

  if (fork_return > 0)
  { // valor de retorno>0, o processo original acontece aqui

    printf("[O] sou o processo original e vou esperar\n");
    sleep(2);

    origemwait = waitpid(fork_return, &prowait, 0); // usamos a função waitpid para esperar pelo processo clonado, para então ativar esse processo

    printf("[O] meu pid eh igual a: %d\n", getpid());
    sleep(2);

    printf("[O] o valor que a variavel forkreturn esta agora eh: %d\n", fork_return); // printa o valor de retorno
    sleep(2);

    printf("[O] valor aleatorio que recebi do clone: %d\n", WEXITSTATUS(prowait)); // o valor aleatorio que o clone retornou
    sleep(2);

    printf("\no pid com %d tem como exit o valor %d\n", origemwait, WEXITSTATUS(prowait));
    sleep(2);
  }

  if (fork_return == 0)
  { // valor de retorno=0, o processo clonado vai acontecer aqui

    printf("[C] ola, sou o processo clone e meu pid eh: %d\n", getpid());
    sleep(4);

    printf("[C] o valor de forkreturn agora eh de: %d\n", fork_return);
    sleep(2);

    time_t t;

    srand((unsigned)time(&t)); // gera um valor aleatório

    int valor_random = rand() % 100; // recebe um int aleatório de 0 à 99

    printf("[C] O valor aleatorio eh: %d\n", valor_random);
    sleep(2);

    exit(valor_random); // encerra o processo clonado com o valor aleatório
  }

  */

  //============================================ THREADS ===================================================//

  pthread_t thread[QTD_THREADS]; // cria um espaço para 10 threads na função main

  long i;

  for (i = 0; i < QTD_THREADS; i++)
  {
    pthread_create(&thread[i], NULL, funcao_thread, (void *)i);
  }

  for (i = 0; i < QTD_THREADS; i++)
  {
    pthread_join(thread[i], NULL);
  }

  return 0;
}