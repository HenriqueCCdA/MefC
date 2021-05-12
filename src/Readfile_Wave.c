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
#define NAMESRC "Readfile_Wave.c"/*nome desse arquivo fonte*/
/*-------------------------------------------------------------------*/
/*********************************************************************/
/**/

/******************************Includes*******************************/
/**/
/*--- Pradão do C*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*-------------------------------------------------------------------*/
/**/
/*--- Proprios*/
#include <Tipos_Wave.h>
#include <Extern_Wave.h>
/*-------------------------------------------------------------------*/
/*********************************************************************/
/**/
/*********************Prototipos das funcoes**************************/
/*...leitura de arquivo*/
char ReadLine(char line[],FILE *fp);
void ClearLine(char line[]);
int  KeyStart(char line[], int *j);
int  KeyEnd(char line[],int Start, int *j);
void GetKeyword(int Start,int End,char line[],char keyword[]);
/*...................................................................*/
/**/
/*... leitura de dados*/
void read_forces ( FILE *fp , long num );
void read_boun   ( FILE *fp , long num ) ;
void read_mate   ( FILE *fp );
void read_coord  ( FILE *fp );
void read_bar2   ( FILE *fp );
void read_tria3  ( FILE *fp );
void read_quad4  ( FILE *fp );
void read_tetra4 ( FILE *fp );
void read_hexa8  ( FILE *fp );
void read_veloc  ( FILE *fp , long num );
void read_initial( FILE *fp , long num );
void read_tforces( FILE *fp , long num );
/*...................................................................*/
/**/
/*...execucao do prgrama*/
void re_execucao2(void);
/*...................................................................*/
/**/
/*********************************************************************/
/**/
/************************ Defines*************************************/
/**/
/*...leitura de arquivo*/
#define LINE_SIZE 80
#define NUMMACRO  22
#define WORD_SIZE 15
/*...................................................................*/
/*********************************************************************/
/**/
/*********************************************************************
 * read_file: funcao usada para ler dados de entrada atraves de um   *
 * arquivo testo                                                     *
 *********************************************************************/
void read_file()    {
/*===*/
  FILE *fp;
  long num ;
  char nomearq[81] , line[ LINE_SIZE + 1 ] ,keyword[ LINE_SIZE + 1 ];
  int i , j, Start, End, k ;
  char macro[NUMMACRO][WORD_SIZE]={ "coor"  ,"bar2"  ,"tria3"
                                   ,"quad4" ,"tetra4","hexa8"
                                   ,"mate"  ,"nnode" ,"numel"
                                   ,"ndm"   ,"ndf"   ,"nen"
                                   ,"numat" ,"end"   ,"forces"
                                   ,"boun"  ,"dt"    ,"initial"
                                   ,"veloc" ,"step"  ,"con"
                                   ,"tforces"                  };

/*===================================================================*/
/**/
/*===Pega o nome do arquivo de entrada*/
  fp = NULL;
  printf("Entre o nome do arquivo: ");
    while ((fp = fopen(gets(nomearq),"r")) == NULL){   
     printf ("Arquivo nao existente !\n");
     re_execucao2();   
     printf("Entre o nome do arquivo: "); 
    }
/*###################################################################*/
/**/
/*### Peaga o nome do arquivo de saida*/
  printf("Entre o nome de arquivo  saida : ");
  gets(arqsaida);
/*###################################################################*/
/**/
/*### Lendo o arquivo de entrada*/
  while(ReadLine(line,fp)!=EOF)   {
    j = 0;
/**/
/*+++ Lendo a linha*/    
    while(j < LINE_SIZE) {
      Start = KeyStart(line,&j);
/*    Fim da palavra chave:*/
      End = KeyEnd(line,Start,&j);
/*    Palavra chave:*/
      GetKeyword(Start,End,line,keyword);
      j++;
 
/*... Compara palavra chave com as macros pre-definidas:*/
      for (i=0; i<NUMMACRO; i++) {
        k = strcmp(macro[i],keyword);
        if (k == 0)
          break;
       }
/*...................................................................*/
/**/
/*===Executa acao correspondente:*/
      switch(i) {
/*... macro "coor":*/
      case 0:
        read_coord(fp);
        break;
/*...................................................................*/
/**/
/*... macro "bar2":*/
      case 1:
        read_bar2(fp);
        break;
/*...................................................................*/
/**/
/*... macro "tria3"*/
      case 2:
        read_tria3(fp);
        break;
/*...................................................................*/
/**/
/*... macro "quad4":*/
      case 3:
        read_quad4(fp);
        break;
/*...................................................................*/
/**/
/*... macro "tetra 4":*/
      case 4:
        read_tetra4(fp);
        break;
/*...................................................................*/
/**/
/*... macro "hexa8:"*/
      case 5:
        read_hexa8(fp);
        break;
/*....................................................................*/
/**/
/*... macro "mate":*/
      case 6:
        read_mate(fp);
        break;
/*....................................................................*/
/**/
/*... macro "nnode"*/
      case 7: /*macro "nnode":*/
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        nnode = atol(keyword);
/*---Testa se ha espaco sufuciente para os nos*/
        if( nnode > MAXNODES ){
          printf("Numero Maximos de nos superado.\n");  
          exit(0);
        }
/*-------------------------------------------------------------------*/
        break;
/*...................................................................*/
/**/
/*... macro "numel":*/
      case 8:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        numel = (atol(keyword));
/*---Testa se ha espaco sufuciente para os elementos*/
        if( nnode > MAXELEMENTS ){
          printf("Numero Maximos de elementos superado.\n");  
          exit(0);
        }
/*-------------------------------------------------------------------*/
        break;
/*...................................................................*/
/**/
/*... macro "ndm":*/
      case 9:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        ndm = (atol(keyword));
        break;
/*...................................................................*/
/**/
/*... macro ndf:*/
      case 10:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        ndf = (atol(keyword));
        break;
/*...................................................................*/
/**/
/*... macro "nen"*/
      case 11:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        nen =(atol(keyword));
        break;
/*...................................................................*/
/**/
/*... macro "numat"*/
      case 12:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        numat = (atol(keyword));
        break;
/*...................................................................*/
/**/
/*... macro "end"*/
      case 13:
        break;
/*...................................................................*/
/**/
/*... marco "forces":*/
      case 14:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        num = (atol(keyword));
        read_forces( fp , num);
        break;
/*....................................................................*/
/**/
/*... macro "boun":*/
      case 15:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        num = (atol(keyword));
        read_boun( fp , num );
        break;
/*...................................................................*/
/**/
/*... macro "dt":*/
      case 16: /*macro "dt":*/
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        dt = (atof(keyword));
        break;
/*...................................................................*/
/**/
/*... macro "initial":*/
      case 17:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        num = (atol(keyword));
        read_initial( fp , num );
        break;
/*...................................................................*/
/**/
/*... macro "veloc":*/
      case 18:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        num = (atol(keyword));
        read_veloc( fp , num );
        break;
/*...................................................................*/
/**/
/*... macro "step":*/
      case 19:
        Start = KeyStart(line,&j);
/*Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        step = atol(keyword);
        break;
/*...................................................................*/
/**/
/*... macro "con":*/
/*********************************************************************/
/* con-> 1 para malha com convenção de numeração de nois normal      */
/* con-> 2 para malha com convenção diferente(gid)                   */
/*********************************************************************/
      case 20:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        con = atol(keyword);
        break;
/*...................................................................*/
/**/
/*... macro "tforces":*/
      case 21:
        Start = KeyStart(line,&j);
/*            Fim da palavra chave:*/
        End = KeyEnd(line,Start,&j);
/*            Palavra chave:*/
        GetKeyword(Start,End,line,keyword);
        j = j + 1;
        num = (atol(keyword));
        read_tforces( fp , num );
        break;
/*...................................................................*/
      }
/*...................................................................*/
    }
/*===================================================================*/
  }
/*###################################################################*/
/**/
/* ===================================
 for (i=0; i<numel; i++)
  for(j=0; j<MAXNODEL; j++)
   elmt[i].node[j]--;
   ====================================*/

/* supondo que na primeira linha esteja o numero de nos
  , o numero de elementos, a dimensao do problema, 
   o grau de liberdade e o numero maximo de nos por elemento*/

/*fscanf(fp, "%ld %ld %ld %ld %ld %ld\n",&nnode,&numel
        ,&ndm,&ndf,&nen,&numat);
    read_mate(fp);
    read_coord(fp);
    read_element(fp);*/
/**/
/*===Fechando o arquivo de entrada*/
fclose(fp);
/*===================================================================*/
/**/
}
/*********************************************************************/
/**/
/*********************************************************************
 * read_coord: le as coordenadas de cada no.                         *
 * ------------------------------------------------------------------*
 * Parametros de entrada:                                            *
 * ------------------------------------------------------------------*
 * fp              ->arquivo de saida                                *
 * nnode           -> numero de nos                                  *
 * ndm             -> numero de dimensoes                            *
 * node[MAXNODES].x-> coordenadas x                                  *
 * node[MAXNODES].y-> coordenadas y                                  *
 * node[MAXNODES].z-> coordenadas z                                  *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * node[nnode].x ,node[nnode].y,node[nnode].z -> atualizados         *
 * ------------------------------------------------------------------*
 *********************************************************************/
void read_coord(FILE *fp) {
/*=== */
  long i, j;
/*===================================================================*/
/**/
/*===*/
  for(i = 0; i < nnode; i++) {
/*+++ Le o numero do no*/    
    if (fscanf(fp, "%d" ,&j) == 0) {
      printf("Erro na leitura do numero do no = %ld !\n",j);
      exit(0);
    }
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**/
/*+++*/
    switch(ndm) {
/*... caso unidimensional*/
      case 1:
        if (fscanf(fp, "%lf\n", &node[j-1].x)==0) {
          printf("Erro na leitura das coordendadas do no %ld = !\n",j);
          exit(0);
        }
        break;
/*...................................................................*/
/**/
/*... caso bidimensional*/
      case 2:
        if (fscanf(fp, "%lf %lf\n", &node[j-1].x,&node[j-1].y)==0) {
          printf("Erro na leitura das coordenadas do no %ld = !\n",j);
          exit(0);
        }
        break;
/*...................................................................*/
/**/
/*...caso tridimensional*/
      case 3:
        if (fscanf(fp, "%lf %lf %lf\n", &node[j-1].x,&node[j-1].y
                                      ,&node[j-1].z)==0) {
          printf("Erro na leitura das coordenadas do no %ld = !\n",j);
          exit(0);
        }
        break;
/*...................................................................*/
/**/
/*...*/
      default:
        printf("Erro na leitura das coordenadas"
               "-dimensao do problema incorreta\n");
        exit(0);
/*...................................................................*/
    }
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 *read_bar2: Le os nos e o material de uma barra com dois nos        *
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * nnumel           -> numero de elementos                           *
 * nen              -> numero de nos                                 *
 * elmt[MAXELEMENTS].node[MAXNODEL] -> nos do elemento               *
 * elmt[MAXELEMENTS].mate -> material do elemento                    *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * elmt[numel].node[nen] -> nos do atualizado                        *
 * elmt[numel].mate-> material do atualizad o                        *
 * ------------------------------------------------------------------*
 *  OBS:                                                             * 
 *  TBAR2 definido em Tipos.h                                        * 
 *********************************************************************/
void read_bar2(FILE *fp)   {
/*===*/
  long i,j,k;
/*===================================================================*/
/**/
/*===*/
  for (i = 0; i < numel; i++)   {
/*... le numero do elemento*/
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura no numero do elemento posterior ao"
             " elemento  %ld !\n",j);
      exit(0);
    }
/*...................................................................*/
/**/
   for (k = 0; k < nen; k++) 
/*... nos*/
      if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   { 
        printf("Erro na leitura dos nos do elemento = %ld"
               ", no = %ld!\n",j,k+1);
        exit(0);
       }
/*...................................................................*/
/**/
/*-------------------------------------------------------------------*/
/**/
/*... material*/      
    if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   { 
      printf("Erro na leitura do material do elemento = %ld !\n",j);
      exit(0);
    }
/*...................................................................*/
/**/
/*... tipo de elemneto */
     elmt[j-1].type = TBAR2;
/*...................................................................*/
/**/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 *read_tria3: Le os nos e o material de um tirangulo com 3 nos       *
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * nnumel           -> numero de elementos                           *
 * nen              -> numero de nos                                 *
 * elmt[MAXELEMENTS].node[MAXNODEL] -> nos do elemento               *
 * elmt[MAXELEMENTS].mate -> material do elemento                    *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * elmt[numel].node[nen] -> nos do atualizado                        *
 * elmt[numel].mate-> material do atualizad o                        *
 * ------------------------------------------------------------------*
 *  OBS:                                                             *
 *  -----------------------------------------------------------------*
 *  TBAR2 definido em Tipos.h                                        *
 *  -----------------------------------------------------------------*
 *********************************************************************/
void read_tria3(FILE *fp)   {
/*===*/
   long i,j,k;
/*===================================================================*/
/**/
/*===*/
  for (i = 0; i < numel; i++)   {
/*... le o numero do elemento*/    
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura no numero do elemento posterior ao"
             " elemento  %ld !\n",j);
      exit(0);
    }
/*...................................................................*/
/**/
/*... le os nos do elemento*/
   for (k = 0; k < nen; k++) 
     if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   { 
       printf("Erro na leitura dos nos do elemento = %ld"
               ", no = %ld!\n",j,k+1);
       exit(0);
     }
/*...................................................................*/
/**/
/*... le os materias*/
     if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   { 
       printf("Erro na leitura do material do elemento = %ld !\n",j);
       exit(0);
      }
/*...................................................................*/
/**/
/*...*/
     elmt[j-1].type = TTRIA3;
/*...................................................................*/
    }
/*===================================================================*/
}
/*********************************************************************
 *read_quad4:le os nos e o material de um quadrilatero com 3 nos     *
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * nnumel           -> numero de elementos                           *
 * nen              -> numero de nos                                 *
 * elmt[MAXELEMENTS].node[MAXNODEL] -> nos do elemento               *
 * elmt[MAXELEMENTS].mate -> material do elemento                    *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * elmt[numel].node[nen] -> nos do atualizado                        *
 * elmt[numel].mate-> material do atualizad o                        *
 * ------------------------------------------------------------------*
 *  OBS:                                                             *
 *  -----------------------------------------------------------------* 
 *  TQUAD4 definido em Tipos.h                                       *
 *  -----------------------------------------------------------------* 
 *********************************************************************/
void read_quad4(FILE *fp)   {
/*===*/
  long i,j,k;
/*===================================================================*/
/**/
/*===*/
  for (i = 0; i < numel; i++)   {
/*... Le o numero do elemeto*/
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura no numero do elemento posterior ao"
             " elemento  %ld !\n",j);
      exit(0);
    }
/*...................................................................*/
/**/
/*... le os nos do elemento*/
    for (k = 0; k < nen; k++) 
      if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   { 
      printf("Erro na leitura dos nos do elemento !\n");
      exit(0);
     }
/*...................................................................*/
/**/
/*... le o meterial do elemento*/
     if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   { 
       printf("Erro na leitura do material do elemento !\n");
       exit(0);
     }
/*...................................................................*/
/**/
/*...tipo do elemento*/
     elmt[j-1].type = TQUAD4;
/*...................................................................*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 *read_tetra4: Le os nos e o material de um tetraedro com 4 nos      *
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * nnumel           -> numero de elementos                           *
 * nen              -> numero de nos                                 *
 * elmt[MAXELEMENTS].node[MAXNODEL] -> nos do elemento               *
 * elmt[MAXELEMENTS].mate -> material do elemento                    *
 * con -> convencão da malha de tetraedros                           *
 *       1-> convencao do fernado                                    *
 *       2-> convencao do gid                                        *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * elmt[numel].node[nen] -> nos do atualizado                        *
 * elmt[numel].mate-> material do atualizado                         *
 * ------------------------------------------------------------------*
 *  OBS:                                                             *
 *  -----------------------------------------------------------------* 
 *  TTETRA4 definido em Tipos.h                                      *
 *  -----------------------------------------------------------------*
 *********************************************************************/
void read_tetra4(FILE *fp)   {
/*===*/
  long i,j,k,a;
/*===================================================================*/
/**/
/*===*/
  for (i = 0; i < numel; i++)   {
/*... lendo numero do elemento*/
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura no numero do elemento posterior ao"
             " elemento  %ld !\n",j);
      exit(0);
    }
/*...................................................................*/
/**/
/*... lendo nos*/
    for (k = 0; k < nen; k++) 
      if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   {
        printf("Erro na leitura dos nos do elemento = %ld!\n",j);
        exit(0);
      }
/*...................................................................*/
/**/
/*... lendo material*/
    if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   {
      printf("Erro na leitura do material do elemento !\n");
      exit(0);
    }
/*...................................................................*/
/**/
/*... tipo do elemento*/
    elmt[j-1].type = TTRETA4;
/*...................................................................*/
/**/
/*... Convencao da orientacao do nos utilizada*/
/*... Convecao do fernando*/
    if ( con == 1 );
/*...................................................................*/
/**/
/*... Convencao do Gid*/
    else if ( con == 2 ){
       a=elmt[j-1].node[2];
       elmt[j-1].node[2]=elmt[j-1].node[3];
       elmt[j-1].node[3]=a;
    }
/*...................................................................*/
/**/
/*... */
    else{
       printf("\nConvencao utilizada para a numereção dos nos não "
             "foi especificada\nTetraedro\n"); 
      exit(0);
    }
/*...................................................................*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 *read_hexa8: Le os nos e o material de um hexaedro com 8 nos        *
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * nnumel           -> numero de elementos                           *
 * nen              -> numero de nos                                 *
 * elmt[MAXELEMENTS].node[MAXNODEL] -> nos do elemento               *
 * elmt[MAXELEMENTS].mate -> material do elemento                    *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * elmt[numel].node[nen] -> nos do atualizado                        *
 * elmt[numel].mate-> material do atualizado                         *
 * ------------------------------------------------------------------*
 *  OBS:                                                             *
 *  -----------------------------------------------------------------* 
 *  THEXA8 definido em Tipos.h                                       *
 *  -----------------------------------------------------------------*  
 *********************************************************************/
void read_hexa8(FILE *fp)   {
/*===*/
  long i,j,k;
/*===================================================================*/
/**/
/*===*/  
  for (i = 0; i < numel; i++)   {
/*...*/  
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura no numero do elemento posterior ao"
             " elemento  %ld !\n",j);
      exit(0);
    }
/*...................................................................*/
/**/
/*... lendo os nos*/
    for (k = 0; k < nen; k++) 
/*---*/
      if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   { 
        printf("Erro na leitura dos nos do elemento = %ld!\n",j);
        exit(0);
      }
/*-------------------------------------------------------------------*/
/**/
/*...................................................................*/
/**/
/*... lendo o meterial*/
    if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   { 
      printf("Erro na leitura do material do elemento = %ld!\n",j);
      exit(0);
    }
/*...................................................................*/
/**/
/*... tipo do elemento*/
    elmt[j-1].type = THEXA8;
/*...................................................................*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 *read_mate: Le os materiais e suas propriedades                     *
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * numat            -> numero de materias                            *
 * mate[MAXMAT].prop[MAXPROP] -> propriedades do material            *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * mate[numat].prop[0] -> propriedades do material                   *
 * ------------------------------------------------------------------*
 *********************************************************************/
void read_mate(FILE *fp)   {
/*===*/
  long i,j,k;
/*===================================================================*/
/**/
/*=== lendo materiais*/
  for (i = 0; i < numat; i++)   {
/*... Numero do material*/    
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura do numero do material !\n");
      exit(0);
    }
/*...................................................................*/
/**/
/*... Lendo as propriedades do material*/
    for (k = 0; k < 1; k++)
      if (fscanf(fp, "%lf",&mate[j-1].prop[k]) == 0)   {
        printf("Erro na leitura da propriedade do material = %ld !\n",j);
        exit(0);
      }
/*...................................................................*/
}
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 *read_boun:le nos com deslocamento prescrito                        *
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * num -> numero de nos com deslocamteno prescrito                   *
 * mode[MAXNODE].eqn[] ->                                            *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * node[num].prop[k] ->                                              *
 * ------------------------------------------------------------------*
 *********************************************************************/
void read_boun( FILE *fp , long num )   {
/*===*/
  long i,j,k;
/*===================================================================*/
/**/
/*===*/
  for (i = 0; i < num; i++)   {
/*...*/
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura das \"boun\"\n");
      exit(0);
    }
/*...................................................................*/
/**/
/*...*/
    for (k = 0; k < ndf; k++) 
      if (fscanf(fp, "%ld",&node[j-1].eqn[k]) == 0)   { 
        printf("!Erro na leitura das \"boun\" no = \n" , j );
        exit(0);
      }
/*...................................................................*/
   }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 *read_forces:le valores diferentes zero das amplitudes/fluxos/fontes*
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * num -> numero de nos com deslocamteno prescrito                   *
 * mode[MAXNODE].fp[] ->                                             *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * node[num].fp[k] ->                                                *
 * ------------------------------------------------------------------*
 *********************************************************************/
void read_forces( FILE *fp , long num )   {
/*===*/
  long i,j,k;
/*===================================================================*/
/**/
/*===*/
  for (i = 0 ; i < num ; i++)   {
/*...*/  
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura das forcas\n");
      exit(0);
    }
/*...................................................................*/
/**/
/*...*/
    for (k = 0; k < ndf; k++){ 
      if (fscanf(fp,"%lf",&node[j-1].fp[k]) == 0)   { 
        printf("Erro na leitura das forcas do no %ld\n" , j );
        exit(0);
      } 
     }
/*...................................................................*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 *read_intial:le valores diferentes zero das amplitudes iniciais     *
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * num -> numero de nos com deslocamteno prescrito                   *
 * mode[MAXNODE].u[] ->                                              *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * node[num].u[k] ->                                                 *
 * ------------------------------------------------------------------*
 *********************************************************************/
void read_initial( FILE *fp , long num)   {
/*===*/
  long i,j,k;
/*===================================================================*/
/**/
/*===*/
  for (i = 0 ; i < num ; i++)   {
/*...*/
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura no  deslocamentos  !\n");
      exit(0);
    }
/*...................................................................*/
/**/
/*...*/
    for (k = 0; k < ndf; k++) 
      if (fscanf(fp, "%lf",&node[j-1].u[k]) == 0)   { 
        printf( "Erro na leitura no deslocamentos do no %ld !\n" ,  j);
        exit(0);
      }
/*...................................................................*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 *read_veloc :le valores diferentes zero das velocidades iniciais    *
 *-------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * num -> numero de nos com deslocamteno prescrito                   *
 * mode[MAXNODE].v[] ->                                              *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * node[num].v[k] ->                                                 *
 * ------------------------------------------------------------------*
 *********************************************************************/
void read_veloc( FILE *fp , long num ){
/*===*/
  long i,j,k;
/*===================================================================*/
/**/
/*===*/
  for (i = 0 ; i < num ; i++)   {
/*...*/  
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura das velocidades.\n");
      exit(0);
    }
/*...................................................................*/
/**/
/*...*/
  for (k = 0; k < ndf; k++) 
    if (fscanf(fp, "%lf",&node[j-1].v[k]) == 0)   { 
     printf("Erro na leitura das velocidades no %ld.\n" , j);
     exit(0);
    }
/*...................................................................*/
  }
/*===================================================================*/
}
/*********************************************************************/
/**/
/*********************************************************************
 * tforces : tipo de forca.                                          *
 * ------------------------------------------------------------------*
 * Parametro de entrada:                                             *
 * ------------------------------------------------------------------*
 * fp               -> arquivo de saida                              *
 * num -> numero de nos com deslocamteno prescrito                   *
 * mode[MAXNODE].fonte_type                                          *
 * ------------------------------------------------------------------*
 * Parametros de saida:                                              *
 * ------------------------------------------------------------------*
 * node[num].fonte_type -> =                                         *
 *                      0 - normal                                   *
 *                      1 - geofisica(Especial_forces.c)             *
 * ------------------------------------------------------------------*
 *********************************************************************/
void read_tforces( FILE *fp , long num ){
/*###*/
  long i , j , k ;
  short type;
/*###################################################################*/
/**/
/*###*/
  for (i = 0; i < num; i++)   {
/*===*/  
    if (fscanf(fp, "%ld" ,&j) == 0) {
      printf("Erro na leitura no tipo de fonte\n");
      exit(0);
    }
/*===================================================================*/
/**/
/*===*/
    if (fscanf(fp, "%d",&node[ j-1 ].fonte_type) == 0)   { 
     printf("Erro na leitura no tipo da fonte no %ld.\n" , j);
     exit(0);
    }
/*===================================================================*/
/**/
/*===*/
    type = node[ j -1 ].fonte_type;
    switch ( type ) {
/*..."fcorte":*/
      case 1:
        if (fscanf(fp, "%lf",&fcorte) == 0)   { 
          printf("Erro na leitura da fcorte no %ld.\n" , j);
          exit(0);
        }
        break;
/*...................................................................*/
/**/
/*...*/
      default:
         printf("\ntipo de fonte invalida\n"
             "funcao read_tforces(*,*)\narquivo %s\n",NAMESRC);
         exit(0);
         break;
/*...................................................................*/
     }
/*===================================================================*/
  }
/*###################################################################*/
}
/*********************************************************************/
char ReadLine( char line[] , FILE *fp )
/*=====================================================================

   DESCRICAO:


=====================================================================*/
{
 int i = 0, ch;
    
 ClearLine(line);
 while(((ch=getc(fp))!='\n') && (ch!=EOF) && (i<LINE_SIZE) )
   line[i++] = (char)ch;
 return (char)ch;
}

void ClearLine( char line[] )
/*=====================================================================

   DESCRICAO:


=====================================================================*/
{
 int i;

 for (i=0; i<LINE_SIZE; i++) {
  line[i]    = ' ';
 }
}

int KeyStart(char line[],int *j)
/*=====================================================================

   DESCRICAO:


=====================================================================*/
{

 while((line[*j]==' ' || line[*j]=='\t') && *j<LINE_SIZE) (*j)++;
 return *j;
}

int KeyEnd(char line[],int Start,int *j)
/*=====================================================================

   DESCRICAO:


=====================================================================*/
{

 *j = Start;
 while(line[*j]!=' ' && *j<LINE_SIZE) (*j)++;
 return *j;
}

void GetKeyword(int Start,int End,char line[],char keyword[])
/*=====================================================================

   DESCRICAO:


=====================================================================*/
{
 int i;
    
 ClearLine(keyword);
 for (i=Start; i<End; i++)
   keyword[i-Start] = line[i];
 keyword[i-Start]='\0';
}
long ReadPar(char line[],int start)
/*=====================================================================

   DESCRICAO:


=====================================================================*/
{
 int i,j;
 char par[LINE_SIZE+1];
 long number;

 for (i= start; i<LINE_SIZE; i++)  {
  if (line[i] >= '0' && line[i] <= '9')  {
   j = i;
   while (line[j] >= '0' && line[j] <= '9' && j<LINE_SIZE)  {
    par[j-i] = line[j];
    j++;
   }
   par[j-i] = '\0';
   number = (long)atol(par);
   return number;
  }
 }
 printf("Parâmetro não especificado !");
 return 0;
}
