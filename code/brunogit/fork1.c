#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
int a, pid_original, c, d;
a = 500;
printf("o valor de a eh %d\n", a);
printf("o primeiro print\n\n");
pid_original = getpid();
  
printf("o valor do pid do pai eh: %d\n", pid_original);
sleep(7);
  
a = fork();
if( a < 0){

  printf("deu erro!!!");
}
  
if (a !=0){
  printf("o valor do a eh: %d\n", a);
sleep (10);
}
if(a == 0) {
  c = getpid();

printf("se aparecer quer dizer q continua vivo\n");
printf("o meu pid eh %d\n", c);
while(1);
}

  return 0;
}
