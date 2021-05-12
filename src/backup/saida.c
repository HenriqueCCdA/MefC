#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Tipos.h>
#include <Extern.h>

/*--------------- Saida quebra galho excel - deslocamentos de um unico ponto ----------- */


void saida(long j){
  
	FILE *fp2;
	char s1[81];
	
	strcpy(s1,arqsaida);
	
	
	
	/*so precisa fazer na primeira  vez*/
	if(j==0){
		if(  (fp2 = fopen(strcat(s1,".dat"),"w"))== NULL){
	    	printf("\n\t!! Erro na ma criação do arquivo RES!!\n ");
			exit(1);
		}
	}
	
	
	else
		if(  (fp2 = fopen(strcat(s1,".dat"),"a"))== NULL){
	    	printf("\n\t!! Erro na ma criação do arquivo dat!!\n ");
			exit(1);
	    }
	
	
		
fclose(fp2);	
	
} 
