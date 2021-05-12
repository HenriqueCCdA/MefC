/*********************************************************************
 * Usado para complilacao no visual stdio 2008 por causa de warnings *
 * ------------------------------------------------------------------*
 *********************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
/*********************************************************************/
/**/
/*******************Defines*******************************************/
/**/
/* ... Depuracao de erros*/
#define NAMESRC "Geometria.c"/*nome desse arquivo fonte*/
/*-------------------------------------------------------------------*/
/*********************************************************************/
/**/

/******************************Includes*******************************/
/**/
/*--- Pradão do C*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*-------------------------------------------------------------------*/
/**/
/*--- Proprios*/
#include <Tipos_Wave.h>
#include <Extern_Wave.h>
/*-------------------------------------------------------------------*/
/*********************************************************************/
/**/
/*********************Prototipos das funcoes**************************/
/*...saida*/
void output    (long istep, int soft, int inst, int insr);
void open_file (long istep , int inst , int soft); /*src -> Files.c*/
void close_file(int inst , int soft );/*src -> Files.c */
/*...................................................................*/
/**/
/*...saida VTK*/
void out_vtk            ( long istep , int inst , int insr ); 
void write_coor_vtk     ( void );
void write_mesh_vtk     ( void );
void write_cell_type_vtk( int tp );
void write_mat_vtk      ( void );
void write_elem_vtk     ( long nelm );
void write_res_vtk      ( long t , int insr );
void head_vtk           ( char *st );
/*-------------------------------------------------------------------*/
/**/
/*... saida Gid */
void out_gid         ( long istep , int inst , int insr );
void write_coor_gid  ( void );
void write_mesh_gid  ( void );
void write_bar2_gid  ( long nelm);
void write_tria3_gid ( long nelm);
void write_quad4_gid ( long nelm);
void write_tetra4_gid( long nelm);
void write_hexa8_gid ( long nelm); 
void write_res_gid   ( long istep , int insr );
/*...................................................................*/
/*********************************************************************/
/**/
/********************Corpo da funcoes*********************************/
/**/
/*********************************************************************
 * output: Seleciona formato no qual a saida sera escrita.           *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * step -> passo de tempo                                            *
 * soft -> instrucao de formato                                      *
 *      1 -> GID                                                     *
 *      2 -> VTK                                                     *
 * inst -> instrucao                                                 *
 *      1 -> Geometira                                               *
 *      2 -> resultados                                              *
 * insr -> tiod de resultados                                        *
 *      1  -> escalar                                                *
 *      2  -> vetorial                                               *
 *      3  -> matricial                                              *
 *-------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 *********************************************************************/
void output( long istep, int soft, int inst, int insr)
{
/* === sotf escolhido*/
  switch( soft )
  {
/* ... saida Gid*/
    case 1:
      out_gid( istep , inst , insr );
      break;
/* ..................................................................*/
/**/
/* ... saida vtk*/
    case 2:
      out_vtk( istep , inst , insr );
      break;
/* ..................................................................*/
/**/
/* ... saida invalida*/
    default:
      printf("\nSotware escolhido invalido\n"
             "funcao(output(*,*,*)\nsrc = %s\n",NAMESRC);
      exit(0);
    break;
/* ..................................................................*/
  }
/*===================================================================*/
}
/**/
/*************************Saida Gid***********************************/
/**/
/*********************************************************************
 * out_gid:                                                          *
 * ------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * step -> passo no tempo                                            *
 * inst -> instrucao                                                 *
 *      1 -> Geometira                                               *
 *      2 -> resultados                                              *
 * insr -> tipo de resultados                                        *
 *      1  -> escalar                                                *
 *      2  -> vetorial                                               *
 *      3  -> matricial                                              *
 *-------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 *********************************************************************/
void out_gid( long istep, int inst, int insr)
{
/*===*/  
  switch(inst) {
/*### geometria*/
    case 1:
/*... abrindo arquivo*/
/*open_file( istep , inst , soft )
  inst  - 1 geometria
  soft  - 1 gid*/ 
      open_file( 0 , 1 , 1 );
/*...................................................................*/
/**/
/*... escrevendo a malha*/
      write_mesh_gid();
/*...................................................................*/
/**/
/*... fechando o arquivo*/
/*close_file( istep , inst , soft )
  inst  - 1 geometria
  soft  - 1 gid*/ 

      close_file( 1 , 1 );
/*...................................................................*/
      break;
/*###################################################################*/
/**/
/*### resultados*/
    case 2:
/* ... abrindo arquivo*/
/*open_file( istep , inst , soft )
  inst  - 2 resultados
  soft  - 1 gid*/
      if( istep == 0)   
        open_file( 0 , 2 , 1 );
/* ..................................................................*/
/**/
/* ... escrevendo os resultados*/
      write_res_gid( istep , insr );
/* ..................................................................*/
/**/
/* ... fecahndo arquivo*/
/*close_file( istep , inst , soft )
  inst  - 2 resultados
  soft  - 1 gid*/
      if( istep == (step) )  
        close_file( 2 , 1);
/*...................................................................*/
     break;
/*###################################################################*/
/**/
/*###*/ 
    default:
      printf("\nInstrucao invalida\nfuncao out_gid(*,*,*)\n"
              "arquivo %s\n",NAMESRC);
      exit(0);
    break;     
/*###################################################################*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * write_coor_gid: escreve as coordenadas no formato do gid          *
 * ------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 * ------------------------------------------------------------------*
 *  ndm -> numero de dimensoes    (Global.h)                         *
 *  node[nnode].x -> coordenada x (Global.h)                         *
 *  node[nnode].y -> coordenada y (Global.h)                         *
 *  node[nnode].z -> coordenada z (Global.h)                         *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_coor_gid(void){
/*===*/ 
  long i;
/*===================================================================*/
/**/
/*=== saida para usuario(debug)*/
  if(FLAG_DEBUG == 1)
    fprintf(stderr,"\n***************************************\n"
                   "Escrevendo coordenadas formato Gid.");
/*===================================================================*/
/**/
/*### escrevendo no arquivo*/
  fprintf(fileout1,"Coordinates\n");
/*=== escrevendo coordenadas*/  
  for(i=0;i<nnode;i++){
/* ... 1 e 2 dimensoes*/
      if(ndm == 1 || ndm ==2) 
        fprintf(fileout1," %ld %E %E %E\n",i+1,node [i].x
                       ,node[i].y,0.0);
/*...................................................................*/
/**/
/* ...3 dimesoes*/
      else if( ndm == 3)
        fprintf(fileout1," %ld %E %E %E\n",i+1,node [i].x
                       ,node[i].y,node[i].z);
/*...................................................................*/
/**/
/*...*/
      else{
        printf("\nnumero dimensoes invalida\n"
               "funcao (write_coor_gid*))\n"
               "src = %s\n",NAMESRC);
      exit(0);
      } 
/*...................................................................*/
  }
/*===================================================================*/
/**/
/*===*/
  fprintf(fileout1,"End coordinates\n");
/*===================================================================*/
/*=== saida para usuario(debug)*/
 if(FLAG_DEBUG == 1)
    fprintf(stderr,"\n***************************************\n"
                   "Coordenadas escritas.\n");
/*===================================================================*/
/**/
/*###################################################################*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * write_mesh_gid:                                                   *
 * ------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 * ------------------------------------------------------------------*
 * numel -> numero de elementos                                      *
 * elmt[numel].type -> tipo do elemento (definidos em Tipos.h)       *
 *            1 - barra de 2 nos                                     *
 *            2 - triangulo de 3 nos                                 *
 *            3 - quadrilatero de 4 nos                              *
 *            4 - tetraedros de 5 nos                                *
 *            5 - hexaedros de 6 nos                                 *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 * OBS:                                                              *
 * ------------------------------------------------------------------*
 * So funciona para um tipo de elemento por vez. Porem o funcao      *
 * foi deixada com as caracteristicas a baixo para facilitar         *
 * a implemetacao de um algoritmo de leitura e escrita q trabalhe    *
 * com malhas de tipos diferente de elementos simultaneamente        *
 *********************************************************************/
 void write_mesh_gid(){
/*===*/
  int i;     
  short type;
/*===================================================================*/
/**/ 
/*===*/
 type = elmt[0].type;
/*###*/
    switch(type) {
/*... barras*/
      case 1:
/*+++ saida para usuario(debug)**/
        if (FLAG_DEBUG == 1 )
          fprintf(stderr,"\n***************************************\n"
                  "Escrevendo elementos barras no formato Gid.\n");
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++Cabecalho*/
        fprintf(fileout1,"MESH \" \" dimension   %ld "
        " ElemType Linear Nnode   %ld\n",3,nen);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++ coordenada*/
        write_coor_gid();
/*+++*/
        fprintf(fileout1,"Elements\n");
        for(i=0;i<numel;i++)
          write_bar2_gid(i);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++ final da malha*/
        fprintf(fileout1,"End elements\n");
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        break;
/*...................................................................*/
/**/
/*... triangulos*/
      case 2:
/*+++ saida para usuario(debug)**/
        if( FLAG_DEBUG == 1 )
          fprintf(stderr,"\n***************************************\n"
                         "Escrevendo elemento triangular formato"
                 " Gid\n");
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++Cabecalho*/
        fprintf(fileout1,"MESH \" \" dimension   %ld "
        " ElemType Triangle Nnode   %ld\n",3,nen);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++ coordenada*/
        write_coor_gid();
/*+++*/
        fprintf(fileout1,"Elements\n");
        for(i=0;i<numel;i++)
          write_tria3_gid(i);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++ final da malha*/
        fprintf(fileout1,"End elements\n");
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        break;
/*...................................................................*/
/*... quadrilateros*/
      case 3:
/*+++ saida para usuario(debug)**/
        if( FLAG_DEBUG == 1 )
          fprintf(stderr,"\n***************************************\n"
                         "Escrevendo elemento quadrilatero"
                         " formato Gid\n");
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++Cabecalho*/
        fprintf(fileout1,"MESH \" \" dimension   %ld "
        " ElemType Quadrilateral Nnode   %ld\n",3,nen);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++ coordenada*/
        write_coor_gid();
/*+++*/
        fprintf(fileout1,"Elements\n");
        for(i=0;i<numel;i++)
          write_quad4_gid(i);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++ final da malha*/
        fprintf(fileout1,"End elements\n");
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        break;
/*...................................................................*/
/**/
/*... tetraedras*/
      case 4:
/*+++ saida para usuario(debug)**/
        if( FLAG_DEBUG == 1 )
          fprintf(stderr,"\n***************************************\n"
                         "Escrevendo elemento tetraedrico"
                         " formato Gid\n");
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++Cabecalho*/
        fprintf(fileout1,"MESH \" \" dimension   %ld "
        " ElemType Tetrahedra Nnode   %ld\n",3,nen);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++ coordenada*/
        write_coor_gid();
/*+++*/
        fprintf(fileout1,"Elements\n");
        for(i=0;i<numel;i++)
          write_tetra4_gid(i);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++ final da malha*/
        fprintf(fileout1,"End elements\n");
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        break;
/*...................................................................*/
/*... hexaedros */
      case 5:
/*+++ saida para usuario(debug)**/
        if( FLAG_DEBUG == 1 )
          fprintf(stderr,"\n***************************************\n"
                         "Escrevendo elemento hexaedrico"
                         " formato Gid\n");
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++Cabecalho*/
        fprintf(fileout1,"MESH \" \" dimension   %ld "
        " ElemType Hexahedra Nnode   %ld\n",3,nen);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++ coordenada*/
        write_coor_gid();
/*+++*/
        fprintf(fileout1,"Elements\n");
        for(i=0;i<numel;i++)
          write_hexa8_gid(i);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++ final da malha*/
        fprintf(fileout1,"End elements\n");
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        break;
/*...................................................................*/
/**/
/*...*/
      default: 
        printf("\nTipo de elemento invalido\n"
               "funcao write_mesh_gid(*,*,*)\n""arquivo fonte %s\n"
              ,NAMESRC);
        exit(0); 
        break;
/*...................................................................*/
     }
/*###################################################################*/
/*===================================================================*/
} 
/*********************************************************************/
/**/
/*********************************************************************
 * mesh_bar2_gid : Elemento barra com 2 nos                            *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * nelem -> numero do elemento                                       *
 * elmt[numel].node[2]-> numero do no do elemento(Tipos.h e Global.h)*
 * elmt[numel].mate   -> numero do material do elmento               *
 *                      (Tipos.h Global.h)                           *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_bar2_gid(long nelm){
/*===*/
 long k;
/*===================================================================*/
/**/
/*=== saida para usuario(debug)*/
 if(FLAG_DEBUG == 1)
    fprintf(stderr,"elmet = %ld no1 = %ld no2 = %ld\n",nelm+1
                  ,elmt[nelm].node[0],elmt[nelm].node[1]);
/*===================================================================*/
/**/

/*=== Escrevendo a malha no arquivo*/
/*... numero do elemento*/
 fprintf(fileout1," %ld ", nelm+1);
/*...................................................................*/
/**/
/*... nos do elemento*/
 for(k=0;k<nen;k++)
   fprintf(fileout1,"  %ld  ",elmt[nelm].node[k] );
/*...................................................................*/
/**/
/*... material*/
 fprintf(fileout1," %ld \n", elmt[nelm].mate);
/*...................................................................*/
/**/
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * mesh_tria3_gid:Elemento trinagular com 3 nos                      *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * ndm   -> numero de dimensoes                                      *
 * nelem -> numero do elemento                                       *
 * elmt[numel].node[2]-> numero do no do elemento(Tipos.h e Global.h)*
 * elmt[numel].mate   -> numero do material do elmento               *
 *                      (Tipos.h Global.h)                           *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/

void write_tria3_gid(long nelm){
/*===*/
  long k;
/*===================================================================*/
/**/
/*=== saida para usuario(debug)*/
  if(FLAG_DEBUG == 1){
    fprintf(stderr,"elmet = %ld no1 = %ld no2 = %ld no3 = %ld \n"
                  ,nelm+1,elmt[nelm].node[0],elmt[nelm].node[1]
                  ,elmt[nelm].node[2]);
  }
/*===================================================================*/
/**/

/*=== Escrevendo a malha no arquivo*/
/**/
/*... numero do elemento*/
  fprintf(fileout1," %ld ", nelm+1);
/*...................................................................*/
/**/
/*...nos do elemento */
  for(k=0;k<nen;k++)
    fprintf(fileout1,"  %ld  ",elmt[nelm].node[k] );
/*...................................................................*/
/**/
/*...material do elemento*/
  fprintf(fileout1," %ld \n", elmt[nelm].mate); 
/*...................................................................*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * mesh_quad4_gid:Elemento quadrilateo com 4 nos                     *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * ndm   -> numero de dimensoes                                      *
 * nelem -> numero do elemento                                       *
 * elmt[numel].node[2]-> numero do no do elemento(Tipos.h e Global.h)*
 * elmt[numel].mate   -> numero do material do elmento               *
 *                      (Tipos.h Global.h)                           *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_quad4_gid(long nelm){
/*===*/
  long k;
/*===================================================================*/
/**/
/*=== saida para usuario(debug)*/
  if(FLAG_DEBUG == 1){
    fprintf(stderr,"elmet = %ld no1 = %ld no2 = %ld no3 = %ld"
                   "no4= %ld\n"
                  ,nelm+1,elmt[nelm].node[0],elmt[nelm].node[1]
                  ,elmt[nelm].node[2],elmt[nelm].node[3]);
  }
/*===================================================================*/
/**/

/*=== Escrevendo a malha no arquivo*/
/**/
/*... numero do elemento*/
  fprintf(fileout1," %ld ", nelm+1);
/*...................................................................*/
/**/
/*...nos do elemento */
  for(k=0;k<nen;k++)
    fprintf(fileout1,"  %ld  ",elmt[nelm].node[k] );
/*...................................................................*/
/**/
/*...material do elemento*/
  fprintf(fileout1," %ld \n", elmt[nelm].mate); 
/*...................................................................*/
}
/*********************************************************************
 * mesh_tetra4_gid:Elemento tetraedrico com 4 nos                    *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * ndm   -> numero de dimensoes                                      *
 * nelem -> numero do elemento                                       *
 * elmt[numel].node[2]-> numero do no do elemento(Tipos.h e Global.h)*
 * elmt[numel].mate   -> numero do material do elmento               *
 *                      (Tipos.h Global.h)                           *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_tetra4_gid(long nelm){
/*===*/
  long k;
/*===================================================================*/
/**/
/*=== saida para usuario(debug)*/
  if(FLAG_DEBUG == 1){
    fprintf(stderr,"elmet = %ld no1 = %ld no2 = %ld no3 = %ld"
                   "no4= %ld\n"
                  ,nelm+1,elmt[nelm].node[0],elmt[nelm].node[1]
                  ,elmt[nelm].node[2],elmt[nelm].node[3]);
  }
/*===================================================================*/
/**/

/*=== Escrevendo a malha no arquivo*/
/*... numero do elemento*/
  fprintf(fileout1," %ld ", nelm+1);
/*...................................................................*/
/**/
/*...nos do elemento */
  for(k=0;k<nen;k++)
    fprintf(fileout1,"  %ld  ",elmt[nelm].node[k] );
/*...................................................................*/
/**/
/*...material do elemento*/
  fprintf(fileout1," %ld \n", elmt[nelm].mate); 
/*...................................................................*/
/**/
}
/*********************************************************************/
/**/
/*********************************************************************
 * mesh_hexa8_gid:Elemento hexaedrico com 8 nos                      *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * ndm   -> numero de dimensoes                                      *
 * nelem -> numero do elemento                                       *
 * elmt[numel].node[2]-> numero do no do elemento(Tipos.h e Global.h)*
 * elmt[numel].mate   -> numero do material do elmento               *
 *                      (Tipos.h Global.h)                           *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_hexa8_gid(long nelm){
/*===*/
  long k;
/*===================================================================*/
/**/
/*=== saida para usuario(debug)*/
  if(FLAG_DEBUG == 1){
    fprintf(stderr,"elmet = %ld no1 = %ld no2 = %ld no3 = %ld "
                   "no4= %ld no5 = %ld no6 = %ld  no7 = %ld "
                   "no8 = %ld\n"
                  ,nelm+1,elmt[nelm].node[0],elmt[nelm].node[1]
                  ,elmt[nelm].node[2],elmt[nelm].node[3]
                  ,elmt[nelm].node[4],elmt[nelm].node[5]
                  ,elmt[nelm].node[6],elmt[nelm].node[7]);
  }
/*===================================================================*/
/**/

/*=== Escrevendo a malha no arquivo*/
/*... numero do elemento*/
  fprintf(fileout1," %ld ", nelm+1);
/*...................................................................*/
/**/
/*...nos do elemento */
  for(k=0;k<nen;k++)
    fprintf(fileout1,"  %ld  ",elmt[nelm].node[k] );
/*...................................................................*/
/**/
/*...material do elemento*/
  fprintf(fileout1," %ld \n", elmt[nelm].mate); 
/*...................................................................*/
/**/
}
/*********************************************************************/
/**/
/*********************************************************************
 * write_res_gid:                                                    *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * ndf   -> numero de gruas de leberdade(Global.h)                   *
 * nnode -> numero de nos (Global.h)                                 *
 * istep -> passo no tempo                                           *
 * insr -> tipo de resultados                                        *
 *      1  -> escalar                                                *
 *      2  -> vetorial                                               *
 *      3  -> matricial                                              *
 * node[nnode].u[k]-> resultados (Tipos.h e Global.h)                *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_res_gid( long istep , int insr ){
/*===*/    
  int i,k;
/*===================================================================*/
/**/
/*=== Cabecalho*/
  if( istep == 0 )
    fprintf(fileout1,"GID post results file 1.0\n");
/*===================================================================*/
/**/
/*=== Tipo de grandeza*/
  switch(insr){
/*... escalar*/
  case 1:
    fprintf(fileout1,"Result \" Amplitudes\" \" \"      %ld  "
            "Scalar onNodes\nValues\n",istep+1);
    for(i=0;i<nnode;i++)
      for(k=0;k<ndf;k++)
        fprintf(fileout1," %ld %E\n",i+1,node[i].u[k]);
    fprintf(fileout1,"End values\n");
    break;
/*...................................................................*/
/**/
/*... vetorial*/
  case 2:
    fprintf(fileout1,"Result \" Amplitudes\" \" \"      %ld  "
            "vetorial onNodes\nValues\n",istep+1);
    for(i=0;i<nnode;i++)
      for(k=0;k<ndf;k++)
        fprintf(fileout1," %ld %E\n",i+1,node[i].u[k]);
    fprintf(fileout1,"End values\n");
    break;
/*...................................................................*/
/**/
/*... matricial*/
  case 3:
    printf("\nNao implementado");
    break;
/*...................................................................*/
/**/
/*...*/
  default:
    printf("\nTipo de resultado invalido\n"
           "funcao (write_res_gid(*))\n""src = %s\n",NAMESRC);
    exit(0); 
    break;
/*...................................................................*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************Saida vtk***************************************/
/**/
/*********************************************************************
 * out_vtk:                                                          *
 * ------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * step -> passo no tempo                                            *
 * inst -> instrucao                                                 *
 *      1 -> Geometira                                               *
 *      2 -> resultados                                              *
 * insr -> tipo de resultados                                        *
 *      1  -> escalar                                                *
 *      2  -> vetorial                                               *
 *      3  -> matricial                                              *
 *-------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 *********************************************************************/
void out_vtk( long istep , int inst , int insr)
{
/*===*/
  switch(inst) {
/*### geometria*/
  case 1:
/*... abrindo arquivo*/
/*open_file( istep , inst , soft )
  inst  - 1 geometria
  soft  - 2 vtk*/ 
    open_file( 0 , 1 , 2 );
/*...................................................................*/
/**/
/*... cabecalho*/
    head_vtk("Malha de elementos finitos");
/*...................................................................*/
/**/
/*... coordenadas*/
    write_coor_vtk();
/*...................................................................*/
/**/
/*... escrevendo a malha*/
    write_mesh_vtk();
/*...................................................................*/
/**/
/*... escrevendo os materias*/
    write_mat_vtk ();
/*...................................................................*/
/**/
/*... escrevendo resticoes*/
    
/*... fechando o arquivo*/
/*close_file( istep , inst , soft )
  inst  - 1 geometria
  soft  - 2 vtk*/ 
    close_file( 1 , 2 );
/*...................................................................*/
    break;
/*###################################################################*/
  case 2:
/* ... abrindo arquivo*/
/*open_file( istep , inst , soft )
  inst  - 2 resultados
  soft  - 2 vtk*/
    open_file( istep , 2 , 2 );
/* ..................................................................*/
/**/
/*... cabecalho*/
    head_vtk("Resultados do programa mef_wave");
/*...................................................................*/
/**/
/*... coordenadas*/
    write_coor_vtk();
/*...................................................................*/
/**/
/*... escrevendo a malha*/
    write_mesh_vtk();
/*...................................................................*/
/**/

/* ... escrevendo os resultados*/
    write_res_vtk( istep , insr );
/* ..................................................................*/
/**/
/* ... fecahndo arquivo*/
/*close_file( istep , inst , soft )
  inst  - 2 resultados
  soft  - 2 vtk*/
    close_file( 2 , 2 );
/*...................................................................*/
    break;
/*###################################################################*/ 
/*###*/ 
  default:
      printf("\nInstrucao invalida\nfuncao out_vtk(*,*,*)\n"
              "arquivo %s\n",NAMESRC);
      exit(0);
    break;     
/*###################################################################*/
  }
/*===================================================================*/
}
/*********************************************************************
 * wirte_coor_vtk:                                                   *
 * ------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * ndm   -> numero de dimensoes                                      *
 * nnode -> numero de nos                                            *
 * node[nnode].x -> coordena x                                       *
 * node[nnode].y -> coordena y                                       *
 * node[nnode].z -> coordena z                                       * 
 *-------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_coor_vtk( void ){
/*===*/    
  long i;
/*===================================================================*/
/**/
/*=== saida para usuario(debug)*/
  if ( FLAG_DEBUG == 1 ) 
    fprintf(stderr,"\n***************************************\n"
                   "Ecrevendo coordenadas no arquivo vtk. ");
/*===================================================================*/
/**/
/*=== escrevendo as coordenadas no arquivo vtk*/ 
  fprintf(fileout1,"POINTS %d double\n",nnode);
/*---*/
  switch ( ndm ) {
/*... 1 dimensao */
    case 1:
      for( i=0 ; i < nnode ; i++ )
        fprintf( fileout1 , "%lf %lf %lf\n" , node[i].x , 0.0 , 0.0 );
      break;
/*...................................................................*/
/**/
/*... 2 dimensoes*/
    case 2:
      for( i=0 ; i < nnode ; i++ )
        fprintf( fileout1 , "%lf %lf %lf\n" , node[i].x , node[i].y 
                          , 0.0 );
      break;
/*...................................................................*/
/**/
/*... 3 dimensoes*/
    case 3:
      for( i = 0 ; i < nnode ; i++ )
        fprintf( fileout1 , "%lf %lf %lf\n" , node[i].x , node[i].y 
                          , node[i].z );
      break;
/*...................................................................*/
/**/
/*...*/
    default:
      printf("\nnumero de dimensoes invalido\n"
             "\nfuncao write_coor_vtk(*,*,*)\n"
              "arquivo %s\n",NAMESRC);
      exit(0);
    break;
/*...................................................................*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * write_mesh_vtk:                                                   *
 * ------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 * ------------------------------------------------------------------*
 * numel -> numero de elementos                                      *
 * elmt[numel].type -> tipo do elemento (definidos em Tipos.h)       *
 *            1 - barra de 2 nos                                     *
 *            2 - triangulo de 3 nos                                 *
 *            3 - quadrilatero de 4 nos                              *
 *            4 - tetraedros de 5 nos                                *
 *            5 - hexaedros de 6 nos                                 *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 * OBS:                                                              *
 * ------------------------------------------------------------------*
 * So funciona para um tipo de elemento por vez. Porem o funcao      *
 * foi deixada com as caracteristicas a baixo para facilitar         *
 * a implemetacao de um algoritmo de leitura e escrita q trabalhe    *
 * com malhas de tipos diferente de elementos simultaneamente        *
*********************************************************************/
void write_mesh_vtk(void)
{
/*===*/
  long i;
  int type;
/*===================================================================*/
/**/
/*===*/
  type = elmt[0].type;
/*###*/
  switch ( type ) {
/*=== Barras*/
    case 1:
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Ecrevendo malha de barras formato vtk. ");
/*-------------------------------------------------------------------*/
/**/
/*--- malha*/
      fprintf( fileout1 , "\nCELLS %d %d\n" , numel , numel*3 );
      for( i = 0; i < numel ; i++ ) 
        write_elem_vtk( i );
/*-------------------------------------------------------------------*/
/**/
/*--- tipo do elemento*/
      fprintf( fileout1 , "\nCELL_TYPES %d\n" , numel );
      for( i = 0; i < numel ; i++ ) 
          write_cell_type_vtk( 3 );
/*-------------------------------------------------------------------*/
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Malha escrita. ");
/*-------------------------------------------------------------------*/

      break;
/*===================================================================*/
/**/
/*=== Triangulo*/
    case 2:
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Ecrevendo malha de triangulos formato vtk. ");
/*-------------------------------------------------------------------*/
/**/
/*--- malha*/
      fprintf( fileout1 , "\nCELLS %d %d\n" , numel , numel*4 );
      for( i = 0; i < numel ; i++ ) 
        write_elem_vtk( i );
/*-------------------------------------------------------------------*/
/**/
/*--- tipo do elemento*/
      fprintf( fileout1 , "\nCELL_TYPES %d\n" , numel );
      for( i = 0; i < numel ; i++ ) 
        write_cell_type_vtk( 5 );
/*-------------------------------------------------------------------*/
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Malha de triangulos escrita. ");
/*-------------------------------------------------------------------*/
      break;
/*===================================================================*/
/**/
 /*=== Quadrilatero*/
    case 3:
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Ecrevendo malha de quadrilaterosformato vtk.");
/*-------------------------------------------------------------------*/
/**/
/*--- malha*/
      fprintf( fileout1 , "\nCELLS %d %d\n" , numel , numel*5 );
      for( i = 0; i < numel ; i++ ) 
        write_elem_vtk( i );
/*-------------------------------------------------------------------*/
/**/
/*--- tipo do elemento*/
      fprintf( fileout1 , "\nCELL_TYPES %d\n" , numel );
      for( i = 0; i < numel ; i++ ) 
        write_cell_type_vtk( 9 );
/*-------------------------------------------------------------------*/
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Malha de quadrilateros escrita. ");
/*-------------------------------------------------------------------*/
      break;
/*===================================================================*/
/**/
/*=== Tetraedors*/
    case 4:
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Ecrevendo malha de tetraedros formato vtk. ");
/*-------------------------------------------------------------------*/
/**/
/*--- malha*/
      fprintf( fileout1 , "\nCELLS %d %d\n" , numel , numel*5 );
      for( i = 0; i < numel ; i++ ) 
        write_elem_vtk( i );
/*-------------------------------------------------------------------*/
/**/
/*--- tipo do elemento*/
      fprintf( fileout1 , "\nCELL_TYPES %d\n" , numel );
      for( i = 0; i < numel ; i++ ) 
        write_cell_type_vtk( 10 );
/*-------------------------------------------------------------------*/
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Malha de tetraedros escrita. ");
/*-------------------------------------------------------------------*/
      break;
/*===================================================================*/
/**/
/*=== Thexaedros*/
    case 5:
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Ecrevendo malha de hexaedros ormato vtk. ");
/*-------------------------------------------------------------------*/
/**/
/*--- malha*/
      fprintf( fileout1 , "\nCELLS %d %d\n" , numel , numel*9 );
      for( i = 0; i < numel ; i++ )
        write_elem_vtk( i );
/*-------------------------------------------------------------------*/
/**/
/*--- tipo do elemento*/
      fprintf( fileout1 , "\nCELL_TYPES %d\n" , numel );
      for( i = 0; i < numel ; i++ )
        write_cell_type_vtk( 12 );
/*-------------------------------------------------------------------*/
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 )
        fprintf(stderr,"\n***************************************\n"
                       "Malha de hexaedros escrita. ");
/*-------------------------------------------------------------------*/
      break;
/*===================================================================*/
/**/
/*===*/
    default:
      printf("\nelemento invalido\n"
             "\nfuncao write_mesh_vtk(*,*,*)\n"
              "arquivo %s\n",NAMESRC);
      exit(0);
      break;
/*===================================================================*/
  }
/*###################################################################*/
/**/
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * mesh_bar2_vtk : Elemento barra com 2 nos                          *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * nelem -> numero do elemento                                       *
 * elmt[numel].node[2]-> numero do no do elemento(Tipos.h e Global.h)*
 * elmt[numel].mate   -> numero do material do elmento               *
 *                      (Tipos.h Global.h)                           *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_elem_vtk  ( long nelm  )
{
/*===*/
  long k;
/*===================================================================*/
/**/
/*===*/
  fprintf( fileout1 ," %d ",nen);
  for ( k = 0 ; k < nen ;  k++ )
    fprintf( fileout1 ," %d ", elmt[nelm].node[k] - 1 );
  fprintf( fileout1 ,"\n");
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * mesh_cell_types_vtk :                                             *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * nelem -> numero do elemento                                       *
 * elmt[numel].mate   -> numero do material do elmento               *
 *                      (Tipos.h Global.h)                           *
 * tp    -> tipo do elmento no vtk                                   *
 *       3  -> barra                                                 *
 *       5  -> triangulo                                             *
 *       9  -> quadrilatero                                          *
 *       10 -> tetraedro                                             *
 *       12 -> hexaedro                                              *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_cell_type_vtk( int tp )
{
/*===*/
  fprintf( fileout1 , "%d \n" , tp );
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * mesh_mat_vtk :                                                    *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * numel -> numero de elementos                                      *
 * elmt[numel].mate   -> numero do material do elmento               *
 *                      (Tipos.h Global.h)                           *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_mat_vtk   ( void )
{
/*===*/
  short nmate;
  long i;
/*===================================================================*/
/**/
/*=== materiais*/
  fprintf( fileout1 , "\nCELL_DATA %d \n" , numel );
  fprintf( fileout1 , "SCALARS mesh_materials int 1\n" );
  fprintf( fileout1 , "LOOKUP_TABLE default\n" );
    for( i = 0 ; i < numel ; i++ )
      fprintf( fileout1 , "%d\n" , elmt[i].mate );
/*===================================================================*/
/**/
/*=== propriendas dos materias*/
  fprintf( fileout1 , "SCALARS materials_prop double 1\n" );
  fprintf( fileout1 , "LOOKUP_TABLE default\n" );
    for( i = 0 ; i < numel ; i++ ){
      nmate = elmt[i].mate;
      if ( nmate == 1 )
        fprintf( fileout1 , "%lf\n" , mate[0].prop[0] );
      else if ( nmate == 2 )
        fprintf( fileout1 , "%lf\n" , mate[1].prop[0] );
      else if ( nmate == 3 )
        fprintf( fileout1 , "%lf\n" , mate[2].prop[0] );
    }
/*===================================================================*/
/**/
/*=== tipo da forca*/
  fprintf( fileout1 , "POINT_DATA %ld\n" , nnode );
  fprintf( fileout1 , "SCALARS tipo_forca int 1\n" );
  fprintf( fileout1 , "LOOKUP_TABLE default\n" );
    for( i = 0 ; i < nnode ; i++ )
      fprintf( fileout1 , "%d \n" , node[i].fonte_type );
/*===================================================================*/
/**/
/*=== restricoes*/
  fprintf( fileout1 , "VECTORS amplitudes_pres int \n" );

    for( i = 0 ; i < nnode ; i++ )
      fprintf( fileout1 , "%ld %ld %ld\n" , node[i].eqn[0] 
                        , node[i].eqn[1] , node[i].eqn[2]);
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * write_res_vtk:                                                    *
 *-------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * ndf   -> numero de gruas de leberdade(Global.h)                   *
 * nnode -> numero de nos (Global.h)                                 *
 * istep -> passo no tempo                                           *
 * insr -> tipo de resultados                                        *
 *      1  -> escalar                                                *
 *      2  -> vetorial                                               *
 *      3  -> matricial                                              *
 * node[nnode].u[k]-> resultados (Tipos.h e Global.h)                *
 * ------------------------------------------------------------------*
 * Parametro de saida:                                               *
 * ------------------------------------------------------------------*
 * ------------------------------------------------------------------*
 *********************************************************************/
void write_res_vtk ( long istep , int insr )
{
/*###*/
long i;
/*###################################################################*/
/**/
/*###*/
  switch( insr ) {
/*=== Escalar*/
     case 1:
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Ecrevendo os resultados formato vtk. ");
/*-------------------------------------------------------------------*/
/**/
/*... escrevendo no arquivo*/
       fprintf( fileout1  , "\nPOINT_DATA %d \n",nnode );
       fprintf( fileout1 , "SCALARS deslocamento double \n" );
       fprintf( fileout1 , "LOOKUP_TABLE default\n" );
       for( i=0 ; i < nnode ; i++ )
         fprintf( fileout1 , "%lf\n" , node[i].u[0] );
       break;
/*...................................................................*/
/**/
/*--- saida para usuario(debug)*/
      if ( FLAG_DEBUG == 1 ) 
        fprintf(stderr,"\n***************************************\n"
                       "Resultados escritos.");
/*-------------------------------------------------------------------*/
/*===================================================================*/
/**/
/*=== Vetorial*/
     case 2: 
       printf("\nResultado vetorias não Implementado"
              "\nfuncao write_res_vtk(*,*,*)\n"
              "arquivo %s\n",NAMESRC);
       exit(0);
       break;
/*===================================================================*/
/*=== Matricial*/
     case 3: 
       printf("\nResultado matricial não Implementado"
              "\nfuncao write_res_vtk(*,*,*)\n"
              "arquivo %s\n",NAMESRC);
       exit(0);
       break;
/*===================================================================*/
/**/
/*===*/
     default:
       printf("\ncodigo invalido.\n"
             "\nfuncao write_res_vtk(*,*,*).\n"
              "arquivo %s\n",NAMESRC);
       exit(0);
       break;
/*===================================================================*/
  }
/*###################################################################*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * head_vtk: Cabeçalho do arquivo vtk.                               *
 * ------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 *-------------------------------------------------------------------*
 * st -> imformação no cabeçalho do arquivo vtk                      *
 *-------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 *********************************************************************/
void head_vtk (char* st)
{
/*=== saida para usuario(debug)*/
  if ( FLAG_DEBUG == 1 ) 
    fprintf(stderr,"\n***************************************\n"
                   "Ecrevendo o cabecalho do arquivo vtk. ");
/*===================================================================*/ 
/**/
/*=== Ecrevendo cabeçalho do arquivo vtk*/ 
  fprintf(fileout1,"# vtk DataFile Version 3.0\n");
  fprintf(fileout1,"%s\n",st); 
  fprintf(fileout1,"ASCII\n");
  fprintf(fileout1,"DATASET UNSTRUCTURED_GRID\n");
/*===================================================================*/
}
