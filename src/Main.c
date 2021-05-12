/*********************************************************************
 * mef_wave: Programa de elementos finitos em lingunguem C para      *
 * resolucao da equacao da onda.                                     *
 *********************************************************************/
/**/
/******************************Includes*******************************/
/**/
/*--- Pradão do C*/
#include <stdio.h>
#include <stdlib.h>
/*-------------------------------------------------------------------*/
/**/
/*--- Proprios*/
#include <Tipos_Wave.h>
#include <Global_Wave.h>
/*-------------------------------------------------------------------*/
/*********************************************************************/
/**/
/*********************Prototipos das funcoes**************************/
void read_file   ( void );
void numeq       ( long * );
void profil      ( long [] , long , long *);
void apply_forces( long i ); 
void predict     ( void );
void pform       ( long jd[] );
void correct     ( double x[] );
void solver_c    ( long n     , long   ia[] , long   ja[] , double ad[] 
                 , double a[] , double  b[] , double x[]  , double  z[]
                 , double r[] , double tol  , long   maxit           );
int re_execucao1 ( void );
void output      (long istep, int soft, int inst,int insr);
/*********************************************************************/
/**/
/*********************************************************************/
int main(){
/*####*/
  long neq, nad, maxit,*dum,i;
  double tol;
/*###################################################################*/
/**/
/*###*/  
  tol = 1.0e-011;
  maxit = 1000;
  dum = jd;
/*###################################################################*/
/**/
/*###*/  
  do{
/*... Dados de entrada*/
    read_file();
/*...................................................................*/
/**/
/*... escrevendo geometria*/   
/*output(istep,soft,inst,insr)
soft - 1 gid 2 vtk
inst - 1 geometria 2 resultados
insr - 1 escalar   2 vetorial 
*/
   output( 0 , 2 , 1 , 1 );
/*...................................................................*/
/**/
/*... configuracao inicial do problema*/   
   output( 0 , 2 , 2 , 1 );
/*...................................................................*/
/**/
/*... Numeq (numera as equacoes)*/   
   numeq( &neq );
/*...................................................................*/
/**/
/*... Profil*/   
   profil( jd , neq , &nad );
/*...................................................................*/
/**/   
/*... laco no tempo*/
   for (i = 0; i < step; i++){
     printf ( "step = %ld \n" ,  i);  
/*... monta o vetor b com as forca pescritas*/
     apply_forces( i ); 
/*...................................................................*/
/**/
/*... Predict*/     
     predict();
/*...................................................................*/
/**/
/*... Pform*/     
     pform( jd );
/*...................................................................*/
/**/
/*... Solver_c*/
     solver_c( neq , dum , jd , ad , au , b , x , z , r , tol , maxit);
/*....................................................................*/     
/**/
/*... output*/     
     output( i + 1 , 2 , 2 , 1 );
/*....................................................................*/
/**/
/*... Correct*/     
     correct( x );
/*...................................................................*/
   }
/*...................................................................*/   
   }while(re_execucao1());
/*###################################################################*/
return 0;
}
/*********************************************************************/
 /*  dt <= L/c 
 L= comprimento do elemento
 c= velocidade da onda no meio)
  */
