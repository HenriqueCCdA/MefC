/******************************Includes*******************************/
/**/
/*--- Proprios*/
#include <Tipos_Wave.h>
#include <Extern_Wave.h>
/*-------------------------------------------------------------------*/
/**/
/*********************************************************************/
/**/
/*********************Prototipos das funcoes**************************/
double impulsive(long ij);
/*********************************************************************/
/**/
/**********************************************************************
 * apply_forces:                                                      *
 * -------------------------------------------------------------------*
 * Parametros de Entrada:                                             *
 * -------------------------------------------------------------------*
 *  i -> variavel auxiliar                                            *
 *  j -> variavel auxiliar                                            *
 *  k -> variavel auxiliar                                            *
 * ij -> passo da resolucao do tempo (ij*dt=tempo real)               *
 * no -> numero do no do elemento                                     *
 * ii -> informacao se temos deslocmentos prescrito ou nao            *
 *         = -1  deslocamaneto prescrito                              *
 *         > -1  sem deslocamento  prescrito                          *
 * type -> tipo da forca                                              *
 *           0 - normal                                               *
 *           1 - implusiva (geo fisica)                               *
 * b[MAXNODES] -> vetor da forcas                                     *
 * numel  -> numero de elementos                                      *
 * nen    -> numero de nos por elemento                               *
 * -------------------------------------------------------------------*
 * Parametros de Saida:                                               *
 * -------------------------------------------------------------------*
 * b[MAXNODES]-> atualizado                                           *
 * -------------------------------------------------------------------*
 *********************************************************************/
void apply_forces (long ij)
{
/*===*/
   long i,j,no,k,ii;
   short type;
/*===================================================================*/
/**/
/*=== laco nos elementos*/
   for(i = 0; i < numel; i++){
/*+++ loca interno no elmento*/
     for(j = 0; j < nen; j++){
       no = elmt[i].node[j];
/*=== graus de librsdade*/
       for (k = 0; k < ndf; k++){
       ii = node[no-1].eqn[k];
/*+++ Forcas e fuxos*/
         if (node[no-1].eqn[k] > -1){
           type=node[no-1].fonte_type;
/*=== Tipo da forca*/
           switch(type){
/*... Forcas precristas constantes*/
           case 0:
             b[ii] = node[no-1].fp[k];
             break;
/*...................................................................*/
/**/
/*... Forcas do problema de geoacustica*/
           case 1:
             b[ii] = impulsive(ij);
             break;
/*...................................................................*/
           }
/*===================================================================*/
         }   
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
       }
/*===================================================================*/
     }
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   }
/*===================================================================*/
}
/*********************************************************************/
