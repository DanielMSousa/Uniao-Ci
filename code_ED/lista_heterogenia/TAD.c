#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159


typedef struct retangulo Retangulo;
struct retangulo
{
    float base;
    float altura;
};

typedef struct triangulo Triangulo;
struct triangulo
{
    float l1;
    float l2;
    float l3;
};

typedef struct circulo Circulo;
struct circulo
{
    float cx;
    float cy;
    float raio;
};

typedef enum tipo Tipo;
enum tipo
{
    RETANGULO,
    TRIANGULO,
    CIRCULO
};

typedef struct  noh Noh;
struct noh
{
    Tipo info_type;
    Noh prox;
    void* info;
};

Noh* cria_noh(Tipo type, float* param){
    Noh* no = (Noh*)malloc(sizeof(Noh));
    if(!no)
        return 0;
    no->prox = NULL;
    no->info = NULL;
    no->info_type = type;

    if(type == RETANGULO){
        Retangulo* ret = (Retangulo*)malloc(sizeof(Retangulo));
        if(ret){
            ret->base = param[0];
            ret->altura = param[1];
            no->info = ret;
            return no;
        }
        free(no);
        return NULL;
    }

    if(type == TRIANGULO){
        Triangulo* tri = (Triangulo*) malloc(sizeof(Triangulo));
        if(tri){
            tri-> l1 = param[0];
            tri-> l2 = param[1];
            tri-> l3 = param[2];
            no->info = tri;
            return no;
        }
        free(no);
        return NULL;
    }
    if(type == TRIANGULO){
        Circulo* circ = (Circulo*) malloc(sizeof(Circulo));
        if(circ){
            circ->cx = param[0];
            circ->cy = param[1];
            circ->raio = param[2];
            no->info = circ;
            return no;
        }
        free(no);
        return NULL;
    }

}

float noh_calcula_area(Noh* no){
    if(!no){
        return -1;
    }
    switch (no->info_type)
    {
    case RETANGULO:
        /* code */
        break;
    
    default:
        break;
    }
}




