//******************************Includes******************************/
/**/
/*--- Pradão do C*/
#include<stdio.h>
/*********************************************************************/
/**/
/*********************Variáveis da Malha*******************************
 *nnode - numero de nois da malha                                     *
 *numel - numero de elementos da malha                                *
 *nen   - numero de nois por elemento                                 *
 *con   - tipo de convenção usado para gerar a malha                  *
 *       con->1 para malha com convenção de numeração de nois normal  *
 *       con->2 para malha com convenção diferente(gid)               *
 **********************************************************************/
long nnode , numel , nen ;
int con ;
/*********************************************************************/
/**/
/**********************Variáveis do problema físico(malha)************
 *ndm     - numero de dimensões                                      *
 *ndf     - numero de graus de liberdade(max 6)                      *
 *numat   - numero de materias                                       *
 *fcorte  - frequencia de corte( caso de força impulsiva)            *
 *********************************************************************/

long ndm , ndf , numat ;
double fcorte ;
/*********************************************************************/
/**/
/*********************Variáveis do problema numerico******************
*s[][]   - matriz rigidez                                            *
*p[]     - forças nodais por elemento                                *
*xl[][]  - coordenadas x,y e z dos nois por elementos                *
*u[]     - deslocamentos nodais                                      *
*v[]     - velocidades nodais                                        *
*a[]     - aceleração nodais                                         *
*b[]     -                                                           *
*ad      - matriz diagonal (solver)                                  *
*aumax   - tamanho maximo utilizado na matriz au                     *
*au      - matriz inferior.... (solver)                              *
*al      - matriz superior.....(solver)                              *
*flu     - grandeza du/dx nodais                                     *
*ld[]    - ..........                                                *
*jc      - ...........                                               *
*step    -                                                           *
*ln[]    -                                                           *
*dt      -                                                           *
**********************************************************************/

double s[8][8] , p[8] , xl[3][8] , u[8] , v[8] , a[8] , b[MAXNODES] 
      , ad[MAXSIST] , au[MAXSIST] , al[MAXSIST] , x[MAXNODES] 
      , r[MAXNODES] , z[MAXNODES] , dt;
long ld[10] , jc , step , jd[MAXNODES] , aumax;
ELEMENT elmt[MAXELEMENTS];
MATERIAL mate[MAXMAT];
ELEMENT_TYPE eltype[MAXELTYPE];
NODE node[MAXNODES];
/*********************************************************************/
/**/
/********************Variáveis de arquivos****************************
 *arqsaida - nome do arquivo de saida                                *
 *fileout1   - nome do arquivo de saida                              *
 *********************************************************************/
char arqsaida[NAMEFILE];
FILE *fileout1;
/*********************************************************************/
