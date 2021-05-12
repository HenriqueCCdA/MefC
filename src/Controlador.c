#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int re_execucao1(void);
void re_execucao2(void);




/*_______________________________Controle de execuçao do programa_________________________*/             
int re_execucao1(){
    
	char resposta[10];
    int i=0;
	do{
	   if(i)
	      printf("\n!!!Resposta invalida!!!");
	   printf("\nDeseja executar novamente?(y/n) ");
       gets(resposta);
       i=++i;
	}while(strcmp(resposta,"Y") && strcmp(resposta,"y") && strcmp(resposta,"N")
           && strcmp(resposta,"n")); 
    
		   
	if(!strcmp(resposta,"Y") || !strcmp(resposta,"y"))
	    return 1;
	
	else{
		printf("\n***FIM***\n");
	    return 0;
	}
}

void re_execucao2(){

    char resposta[10];
    int i=0;
	
	
	do{
	   if(i)
	      printf("\n!!!Resposta invalida!!!");
	   printf("\nDeseja tentar novamente?(y/n) ");
       gets(resposta);
       i=++i;
	}while(strcmp(resposta,"Y") && strcmp(resposta,"y") && strcmp(resposta,"N")
           && strcmp(resposta,"n")); 
       
	if(!strcmp(resposta,"n") || !strcmp(resposta,"N")){
	    printf("\n***FIM***\n");
		exit(0);    
	}
}
