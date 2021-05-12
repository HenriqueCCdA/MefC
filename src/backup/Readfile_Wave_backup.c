#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Tipos_Wave.h>
#include <Extern_Wave.h>

void read_forces(FILE *fp);
void read_boun(FILE *fp) ;
void read_mate(FILE *fp);
void read_coord(FILE *fp);
void read_bar2(FILE *fp);
void read_tria3(FILE *fp);
void read_quad4(FILE *fp);
void read_tetra4(FILE *fp);
void read_hexa8(FILE *fp);
char ReadLine(char line[],FILE *fp);
void ClearLine(char line[]);
int KeyStart(char line[], int *j);
int KeyEnd(char line[],int Start, int *j);
void GetKeyword(int Start,int End,char line[],char keyword[]);
void read_veloc(FILE *fp);
void read_initial(FILE *fp);
void re_execucao2(void);

#define LINE_SIZE 80
#define NUMMACRO 21
#define WORD_SIZE 15

void read_file()    {

	FILE *fp;
	char nomearq[81],line[LINE_SIZE+1],keyword[LINE_SIZE+1];
	int i, j, Start, End, k;
	char macro[NUMMACRO][WORD_SIZE]={"coor","bar2","tria3","quad4","tetra4",
									"hexa8","mate","nnode","numel","ndm",
									"ndf","nen","numat","end","forces","boun","dt","initial","veloc","step","con"};


 /* Pega o nome do arquivo*/

	fp = NULL;
	
	
	    
	    printf("Entre o nome do arquivo: ");
		while ((fp = fopen(gets(nomearq),"r")) == NULL){   
		  printf ("Arquivo nao existente !\n");
	      re_execucao2();   
		  printf("Entre o nome do arquivo: "); 
		}
   
	
	printf("Entre o nome de arquivo  saida : ");
    gets(arqsaida);
	
		
	while(ReadLine(line,fp)!=EOF)   {
		j = 0;
		while(j < LINE_SIZE) {
		Start = KeyStart(line,&j);
/*   	Fim da palavra chave:*/
		End = KeyEnd(line,Start,&j);
/*   	Palavra chave:*/
		GetKeyword(Start,End,line,keyword);
		j++;
	
/*   	Compara palavra chave com as macros pre-definidas:*/
	    for (i=0; i<NUMMACRO; i++) {
	    k = strcmpi(macro[i],keyword);
			if (k == 0)
				 break;
	    }

/*   	Executa acao correspondente:*/
		switch(i) {
			case 0:  /* macro "coor":*/
				read_coord(fp);
				break;
			case 1:	/* macro "bar2":*/
				read_bar2(fp);
				break;
			case 2:	/* macro "tria3":*/
				read_tria3(fp);
				break;
			case 3:	/* macro "quad4":*/
				read_quad4(fp);
				break;
			case 4:	/* macro "tetra4":*/
				read_tetra4(fp);
				break;
			case 5:	/* macro "hexa8":*/
				read_hexa8(fp);
				break;
			case 6:	/* macro "mate":*/
				read_mate(fp);
				break;
			case 7: /*macro "nnode":*/
		        Start = KeyStart(line,&j);
/*   	        Fim da palavra chave:*/
		        End = KeyEnd(line,Start,&j);
/*   	        Palavra chave:*/
		        GetKeyword(Start,End,line,keyword);
		        j = j + 1;
				nnode = atol(keyword);
				break;
			case 8: /*macro "numel":*/
		        Start = KeyStart(line,&j);
/*   	        Fim da palavra chave:*/
		        End = KeyEnd(line,Start,&j);
/*   	        Palavra chave:*/
		        GetKeyword(Start,End,line,keyword);
		        j = j + 1;
				numel = (atol(keyword));
				break;
			case 9: /*macro "ndm":*/
		        Start = KeyStart(line,&j);
/*   	        Fim da palavra chave:*/
		        End = KeyEnd(line,Start,&j);
/*   	        Palavra chave:*/
		        GetKeyword(Start,End,line,keyword);
		        j = j + 1;
				ndm = (atol(keyword));
				break;
			case 10: /*macro "ndf":*/
		        Start = KeyStart(line,&j);
/*   	        Fim da palavra chave:*/
		        End = KeyEnd(line,Start,&j);
/*   	        Palavra chave:*/
		        GetKeyword(Start,End,line,keyword);
		        j = j + 1;
				ndf = (atol(keyword));
				break;
			case 11: /*macro "nen":*/
		        Start = KeyStart(line,&j);
/*   	        Fim da palavra chave:*/
		        End = KeyEnd(line,Start,&j);
/*   	        Palavra chave:*/
		        GetKeyword(Start,End,line,keyword);
		        j = j + 1;
				nen =(atol(keyword));
				break;
			case 12: /*macro "numat":*/
		        Start = KeyStart(line,&j);
/*   	        Fim da palavra chave:*/
		        End = KeyEnd(line,Start,&j);
/*   	        Palavra chave:*/
		        GetKeyword(Start,End,line,keyword);
		        j = j + 1;
				numat = (atol(keyword));
				break;
			case 13: /*macro "end":*/
				break;
			case 14: /*macro "forces":*/
				read_forces(fp);
                break;
            case 15: /*macro "eqn":*/
				read_boun(fp);
				break;
	        case 16: /*macro "dt":*/
		        Start = KeyStart(line,&j);
/*   	        Fim da palavra chave:*/
		        End = KeyEnd(line,Start,&j);
/*   	        Palavra chave:*/
		        GetKeyword(Start,End,line,keyword);
		        j = j + 1;
				dt = (atof(keyword));
				break;
			case 17: /*macro "initial":*/
				read_initial(fp);
				break;
			case 18: /*macro "veloc":*/
				read_veloc(fp);
				break;
			case 19: /*macro "step":*/
                Start = KeyStart(line,&j);
   	        /*Fim da palavra chave:*/
		        End = KeyEnd(line,Start,&j);
/*   	        Palavra chave:*/
		        GetKeyword(Start,End,line,keyword);
		        j = j + 1;
				step = atol(keyword);
				break;
		     
/*----con->1 para malha com convenção de numeração de nois normal			
	  con->2 para malha com convenção diferente(gid)----*/	 	
			
			case 20: /*macro "con":*/                 
                Start = KeyStart(line,&j);
/*   	        Fim da palavra chave:*/
		        End = KeyEnd(line,Start,&j);
/*   	        Palavra chave:*/
		        GetKeyword(Start,End,line,keyword);
		        j = j + 1;
				con = atol(keyword);
				break;
			}
	   }
   
   }
/* ===================================
	for (i=0; i<numel; i++)
		for(j=0; j<MAXNODEL; j++)
			elmt[i].node[j]--;
   ====================================*/

/* supondo que na primeira linha esteja o numero de nos, o numero de elementos, a dimensao do problema, 
   o grau de liberdade e o numero maximo de nos por elemento*/

/*	fscanf(fp, "%ld %ld %ld %ld %ld %ld\n",&nnode,&numel,&ndm,&ndf,&nen,&numat);
	read_mate(fp);
    read_coord(fp);
    read_element(fp);*/
fclose(fp);


}

/*funcao que le as coordenadas de cada nó*/

void read_coord(FILE *fp) {
	long i, j;
	for(i = 0; i < nnode; i++) {
		if (fscanf(fp, "%d" ,&j) == 0) {
			printf("Erro na leitura das coordenadas !\n");
			exit(0);
		}
		switch(ndm) {
			case 1:
		       if (fscanf(fp, "%lf\n", &node[j-1].x)==0) {
			      printf("Erro na leitura das coordenadas !\n");
			       exit(0);
			   }
			   break;
			case 2:
			   if (fscanf(fp, "%lf %lf\n", &node[j-1].x,&node[j-1].y)==0) {
			      printf("Erro na leitura das coordenadas !\n");
			      exit(0);
			   }
			   break;
			case 3:
		       if (fscanf(fp, "%lf %lf %lf\n", &node[j-1].x,&node[j-1].y,&node[j-1].z)==0) {
			      printf("Erro na leitura das coordenadas !\n");
			      exit(0);
			   }
			   break;
			default:
				  printf("Erro na leitura das coordenadas - dimensao do problema incorreta\n");
				  exit(0);
		}
	}
}

/*funcao que le os nos de cada elemento, o material de cada elemento, e o tipo de cada elemento*/

void read_bar2(FILE *fp)   {

	long i,j,k;

	for (i = 0; i < numel; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura das coordenadas !\n");
			exit(0);
		}
		for (k = 0; k < 2; k++) 
			if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   { 
			   printf("Erro na leitura dos nos do elemento !\n");
			   exit(0);
			}
		if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   { 
		   printf("Erro na leitura do material do elemento !\n");
		   exit(0);
		 }
		elmt[j-1].type = 1;
	}
}
void read_tria3(FILE *fp)   {

	long i,j,k;

	for (i = 0; i < numel; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura das coordenadas !\n");
			exit(0);
		}
		for (k = 0; k < 3; k++) 
			if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   { 
			   printf("Erro na leitura dos nos do elemento !\n");
			   exit(0);
			}
		if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   { 
		   printf("Erro na leitura do material do elemento !\n");
		   exit(0);
		 }
		elmt[j-1].type = 2;
	}
}
void read_quad4(FILE *fp)   {

	long i,j,k;

	for (i = 0; i < numel; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura das coordenadas !\n");
			exit(0);
		}
		for (k = 0; k < 4; k++) 
			if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   { 
			   printf("Erro na leitura dos nos do elemento !\n");
			   exit(0);
			}
		if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   { 
		   printf("Erro na leitura do material do elemento !\n");
		   exit(0);
		 }
		elmt[j-1].type = 3;
	}
}
void read_tetra4(FILE *fp)   {

	long i,j,k,a;

	for (i = 0; i < numel; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura das coordenadas !\n");
			exit(0);
		}
		for (k = 0; k < 4; k++) 
			if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   { 
			   printf("Erro na leitura dos nos do elemento !\n");
			   exit(0);
			}
		if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   { 
		   printf("Erro na leitura do material do elemento !\n");
		   exit(0);
		 }
			elmt[j-1].type = 4;
		
		if (con==0){
			printf("\nConvenção utilizada para a numereção dos nois não especificada\nTetraedro\n"); 
		    exit(0);
		}
		if (con==2){
			a=elmt[j-1].node[2];
			elmt[j-1].node[2]=elmt[j-1].node[3];
			elmt[j-1].node[3]=a;
		}
	}
}
void read_hexa8(FILE *fp)   {

	long i,j,k;

	for (i = 0; i < numel; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura das coordenadas 1!\n");
			exit(0);
		}
		for (k = 0; k < 8; k++) 
			if (fscanf(fp, "%ld",&elmt[j-1].node[k])== 0)   { 
			   printf("Erro na leitura dos nos do elemento 2!\n");
			   exit(0);
			}
		if (fscanf(fp, "%hd\n",&elmt[j-1].mate) == 0)   { 
		   printf("Erro na leitura do material do elemento 3!\n");
		   exit(0);
		 }
		elmt[j-1].type = 5;
	}
}
void read_mate(FILE *fp)   {

	long i,j,k;

	for (i = 0; i < numat; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura dos materiais 1 !\n");
			exit(0);
		}
		for (k = 0; k < 1; k++) 
			if (fscanf(fp, "%lf",&mate[j-1].prop[k]) == 0)   { 
			   printf("Erro na leitura dos materiais 2 !\n");
			   exit(0);
			}
	}
}

void read_boun(FILE *fp)   {

	long i,j,k;

	for (i = 0; i < nnode; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura das forcas\ncode[0] -> %ld!\n",i);
			exit(0);
		}
		for (k = 0; k < ndf; k++) 
			if (fscanf(fp, "%ld",&node[j-1].eqn[k]) == 0)   { 
			   printf("Erro na leitura das forcas\ncode[1] -> %ld!\n",k);
			   exit(0);
			}
	}
}
void read_forces(FILE *fp)   {

	long i,j,k;

	for (i = 0; i < nnode; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura das forcas\ncode[2] -> %ld!\n",i);
			exit(0);
		}
		for (k = 0; k < ndf; k++) 
			if (fscanf(fp, "%lf",&node[j-1].fp[k]) == 0)   { 
				printf("Erro na leitura das forcas\ncode[3] -> %ld!\n",k);
			   exit(0);
			}
	}
}




void read_initial(FILE *fp)   {

	long i,j,k;

	for (i = 0; i < nnode; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura dos deslocamentos(1) !\n");
			exit(0);
		}
		for (k = 0; k < ndf; k++) 
			if (fscanf(fp, "%lf",&node[j-1].u[k]) == 0)   { 
			   printf("Erro na leitura dos deslocamentos(2) !\n");
			   exit(0);
			}
	}
}

void read_veloc(FILE *fp){
	long i,j,k;

	for (i = 0; i < nnode; i++)   {
		if (fscanf(fp, "%ld" ,&j) == 0) {
			printf("Erro na leitura das velocidades(1)!\n");
			exit(0);
		}
		for (k = 0; k < ndf; k++) 
			if (fscanf(fp, "%lf",&node[j-1].v[k]) == 0)   { 
			   printf("Erro na leitura das velocidades(2)!\n");
			   exit(0);
			}
	}
}
char ReadLine(char line[],FILE *fp)
/*============================================================================

   DESCRICAO:


============================================================================*/
{
	int i = 0, ch;
    
	ClearLine(line);
	while(((ch=getc(fp))!='\n') && (ch!=EOF) && (i<LINE_SIZE) )
			line[i++] = (char)ch;
	return (char)ch;
}

void ClearLine(char line[])
/*============================================================================

   DESCRICAO:


============================================================================*/
{
	int i;

	for (i=0; i<LINE_SIZE; i++)	{
		line[i]    = ' ';
	}
}

int KeyStart(char line[],int *j)
/*============================================================================

   DESCRICAO:


============================================================================*/
{

	while((line[*j]==' ' || line[*j]=='\t') && *j<LINE_SIZE) (*j)++;
	return *j;
}

int KeyEnd(char line[],int Start,int *j)
/*============================================================================

   DESCRICAO:


============================================================================*/
{

	*j = Start;
	while(line[*j]!=' ' && *j<LINE_SIZE) (*j)++;
	return *j;
}

void GetKeyword(int Start,int End,char line[],char keyword[])
/*============================================================================

   DESCRICAO:


============================================================================*/
{
	int i;
    
	ClearLine(keyword);
	for (i=Start; i<End; i++)
			keyword[i-Start] = line[i];
	keyword[i-Start]='\0';
}
long ReadPar(char line[],int start)
/*===========================================================================

   DESCRICAO:


============================================================================*/
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
