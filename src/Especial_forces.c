#define Pi 3.142857
/******************************Includes*******************************/
/*--- Pradão do C*/
#include <stdio.h>
#include <math.h>
/*-------------------------------------------------------------------*/
/**/
/*--- Proprios*/
#include <Tipos_Wave.h>
#include <Extern_Wave.h>
/*-------------------------------------------------------------------*/
/**/
/*********************************************************************/
/**/
/**********************************************************************
 * impulsuve: Forca implusiva concetrada (geofisica)                  *
 *--------------------------------------------------------------------*
 *Parametros de entrada:                                              *
 *--------------------------------------------------------------------*
 * i     -> passo da resolucao do tempo (ij*dt=tempo real)            *
 * dt    -> tamanho do passo no tempo                                 *
 * fcorte-> frequencia da forca de corte                              *
 *--------------------------------------------------------------------*
 *Parametros auxiliares:                                              *
 *--------------------------------------------------------------------*
 * t      -> valor real do tempo                                      *
 * fc     ->                                                          *
 * td     ->                                                          *
 * aux    ->                                                          *
 *--------------------------------------------------------------------*
 *Parametros de saida:                                                *
 *--------------------------------------------------------------------*
 * f      -> valor da forca no noh                                    * 
**********************************************************************/
double impulsive(long i){
/*===*/
   double f,fc,td,t,aux;
/*===================================================================*/
/**/
/*=== Tempo real*/
     t = dt * i;
/*===================================================================*/
/**/
/*===*/
    fc = fcorte / ( 3* sqrt ( Pi ) );
    td = t- ( sqrt ( Pi ) ) / ( 3 * fc );
   aux = Pi * fc * td;
     f = ( 1 - 2 * Pi * (aux) * (aux) ) *exp ( -Pi * (aux) * (aux) );
/**/
/*...Confirindo se aforça é calculada certa*/  
  /*printf("%lf\n",f);*/
/*...................................................................*/
/*===================================================================*/
/**/
/*===*/
  return f;
/*===================================================================*/
}
/*********************************************************************/
