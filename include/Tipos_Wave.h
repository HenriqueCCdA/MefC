#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

/***************************Defines***********************************/
/* ...*/
#define MAXNODES    1000000
#define MAXELEMENTS 1000000
#define MAXNODEL  20
#define MAXDOF     6
#define MAXPROP   10
#define MAXELTYPE 20
#define MAXMAT   100
#define MAXLOADS 100
#define MAXSIST  1000000
#define beta 1
#define alfa 0.5
/*...................................................................*/
/**/
/* ... acrencenta saida no terminal para melhor depuração dos erros*/
#define FLAG_DEBUG 0
/* ..................................................................*/
/**/
/* ... tipos de elemetos */
#define TBAR2      1
#define TTRIA3     2
#define TQUAD4     3
#define TTRETA4    4
#define THEXA8     5
/* ..................................................................*/
/**/
/* ...Arquivos*/
#define NAMEFILE  81
/* ..................................................................*/ 
/*********************************************************************/
/**/
/**********************************************************************
 *Estrutura ElEMENT: Utiliza para guardar informacoes sobre os        *
 *elementos.                                                          *
 *--------------------------------------------------------------------*
 *         type-> tipo do elemento                                    *
 *         mate-> material                                            *
 *node[MAXNODE]-> nos                                                 *
 *    q[MAXDOF]->                                                     *
 *--------------------------------------------------------------------*
**********************************************************************/
typedef struct {
 short type;
 short mate;
 long  node[MAXNODEL];
 short q[MAXDOF];
} ELEMENT;
/*********************************************************************/
/**/
/**********************************************************************
 *Estrutura MATERIAL: Utilizada para guardar informacao da propriedade*
 *de um determinadio material.                                        *
 *--------------------------------------------------------------------*
 *prop[MAXPROP] ->                                                    *
 *--------------------------------------------------------------------*
**********************************************************************/
typedef struct {
  double prop[MAXPROP];
} MATERIAL;
/*********************************************************************/
/**/
/**********************************************************************
 * ELEMENT_TYPE:                                                      *
**********************************************************************/
typedef struct {
  short nnodes;
  char name[8];
} ELEMENT_TYPE;
/*********************************************************************/
/**/
/**********************************************************************
 * Estrutura NODE: Utilizada para guardar informacoes nodais.         *
 *--------------------------------------------------------------------*
 * x -> coordenada x                                                  *
 * y -> coordenada y                                                  *
 * z -> coordenada z                                                  *
 * u[MAXDOF]-> deslocamantos                                          *
 * v[MAXDOF]-> velocidades                                            *
 * a[MAXDOF]-> aceleracoes                                            *
 * fp[MAXDOF] ->deslocamanetos, fluxos e fontes precritas             *
 * fonte_type-> tipo da fonte                                         *
 *              0 -> normal                                           *
 *              1 -> impulsiva (geofisica)                            *
 * eqn[MAXDOF]-> numero da equacao                                    *
 * -------------------------------------------------------------------*
**********************************************************************/
typedef struct {
  double x;
  double y;
  double z;
  double u[MAXDOF];
  double v[MAXDOF];
  double a[MAXDOF];
  double fp[MAXDOF];
  short fonte_type;
  long num;
  long eqn[MAXDOF];
} NODE;
/*********************************************************************/

