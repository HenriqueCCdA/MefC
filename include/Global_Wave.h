//******************************Includes******************************/
/**/
/*--- Prad�o do C*/
#include<stdio.h>
/*********************************************************************/
/**/
/*********************Vari�veis da Malha*******************************
 *nnode - numero de nois da malha                                     *
 *numel - numero de elementos da malha                                *
 *nen   - numero de nois por elemento                                 *
 *con   - tipo de conven��o usado para gerar a malha                  *
 *       con->1 para malha com conven��o de numera��o de nois normal  *
 *       con->2 para malha com conven��o diferente(gid)               *
 **********************************************************************/
long nnode , numel , nen ;
int con ;
/*********************************************************************/
/**/
/**********************Vari�veis do problema f�sico(malha)************
 *ndm     - numero de dimens�es                                      *
 *ndf     - numero de graus de liberdade(max 6)                      *
 *numat   - numero de materias                                       *
 *fcorte  - frequencia de corte( caso de for�a impulsiva)            *
 *********************************************************************/

long ndm , ndf , numat ;
double fcorte ;
/*********************************************************************/
/**/
/*********************Vari�veis do problema numerico******************
*s[][]   - matriz rigidez                                            *
*p[]     - for�as nodais por elemento                                *
*xl[][]  - coordenadas x,y e z dos nois por elementos                *
*u[]     - deslocamentos nodais                                      *
*v[]     - velocidades nodais                                        *
*a[]     - acelera��o nodais                                         *
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
/********************Vari�veis de arquivos****************************
 *arqsaida - nome do arquivo de saida                                *
 *fileout1   - nome do arquivo de saida                              *
 *********************************************************************/
char arqsaida[NAMEFILE];
FILE *fileout1;
/*********************************************************************/
