// (Questão 1 - 5 pontos) Faça um programa em C/C++ que crie um arquivo de texto 
// que funcionará como um dicionário contendo todas as strings com 4 caracteres 
// alfabéticos maiúsculos (de "AAAA" a "ZZZZ"). Cada letra do alfabeto (de A a Z)
// deverá ter sua parte do dicionário gerada por um processo ou thread individual,
// (o programa deverá receber um parâmetro na sua execução que determine se threads
// ou processos serão usados) que gerará todas as strings iniciadas por uma letra 
// (ex. processo/thread que gerará as strings começando com a letra 'C' gerará as 
// strings de "CAAA" a "CZZZ"). A thread principal do processo original deverá 
// aguardar a geração de todas as partes e gerar um arquivo de texto contendo o 
// dicionário inteiro. Comente no código as diferenças do uso de processos e 
// threads, do ponto de vista do consumo de recursos e do ponto de vista do uso
// das funções/API.
 
// Referências para manipulação de arquivos em C:
 
// https://www.inf.pucrs.br/~pinho/LaproI/Arquivos/Arquivos.htm (português)
// http://www.csc.villanova.edu/~mdamian/C/c-files.htm (inglês)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char alfabeto[26] = {'A', 'B', 'C','D', 'E', 'F','G', 'H', 'I','J', 'K', 'L','M', 'N', 'O', 'P', 'Q','R', 'S', 'T', 'U', 'V','W', 'X','Y', 'Z'};
void functionEscreve(char *Str){
   
    
}

int main(void){
    char Str[10000];
    char str1[2];
    char str2[2];
    char str3[2];
    char str4[2];
  
    FILE *arquivo;
    char result;
    arquivo = fopen("dicionario.txt", "wt");  // Cria um arquivo texto para gravação
    if (arquivo == NULL) // Se não conseguiu criar
{
   printf("Problemas na CRIACAO do arquivo\n");
   return -1;
}
 for(int i = 0; i< 1; i++){
        char c = alfabeto[0];
        strcpy (Str, &c);
        for(int j = 1; j < 26; j++){
            char b = alfabeto[j];
            for(int k = 1; k < 26; k++){
                char p = alfabeto[k];
                for(int l = 1; l < 26; l++){
                    char d = alfabeto[l];
                    strcat(Str, &p);
                    strcat(Str, &b);
                    strcat(Str, &d);
                    
                }
                
                
            }
            
            
        }
        printf("Str --> %s\n", Str);
        printf("%c\n", alfabeto[i]);
        
        fputs(Str, arquivo);
        
    }

 
    


result = fputs(Str, arquivo);
if (result == EOF)
    printf("Erro na Gravacao\n");

fclose(arquivo);
    return 0;
}