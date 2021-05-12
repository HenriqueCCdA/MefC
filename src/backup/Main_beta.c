#include <stdio.h>
#include <stdlib.h>
#include <Tipos_Wave.h>
#include <Global_Wave.h>
#include <math.h>

void read_file(void);
void numeq(long *);
void profil (long [],long, long *);
void apply_forces (void);
void predict(void);
void pform(long jd[]);
void correct (double x[]);
void solver_c(long n,long ia[],long ja[],double ad[],double a[],double b[],double x[],double z[],double r[],double tol,long maxit);
double dot_c(double a[],double b[],long n);
void arqu_malha ();
int re_execucao1(void);
void saida (long j);
void arqu_res(long j);


int main(){


	long neq, nad, maxit,*dum;
	long i,j;
	double tolsolv,tol,resid,resid0;


	tolsolv = 1.0e-011;
	tol=1.0e-007;
	maxit = 1000;
	dum = jd;
    resid0=0.0;



	do{
		
		read_file();
	    arqu_malha ();
		numeq(&neq);
	    profil(jd,neq,&nad);
		
		
		for (i = 0; i < step; i++)   {
	       printf ("step=%ld \n",i);
	       arqu_res(i);
           
/*-------------------Preditor/multicorretor-------------------------------*/		   
		 		   
	     predict();
 		 
		 
/*---------------------laco nao linear------------------------------------*/		 
		 do{ 
		   
		   j=1; 
		   printf("\nInteracao nao-lineares= %d \n",j);
           	      
		   apply_forces();
		   pform(jd);
           
		   resid = sqrt(dot_c(b,b,neq));
           if(j==1)
			   resid0 = max(resid0,resid);
           if ((resid/resid0) < tol) 
			   break;  
		  
		   solver_c(neq,dum,jd,ad,au,b,x,z,r,tolsolv,maxit);
		   
		   /*atualizacao:node[i].a[k] = node[i].a[k] + x[ii];
			                     node[i].u[k] = node[i].u[k] + beta*dt*dt*node[i].a[k];
			                     node[i].v[k] = node[i].v[k] + alfa*dt*node[i].a[k]; */
		   correct(x);
		   /*-----------------------------------------------------------------------*/
		   
		   j=++j;
		   }while( (--j)==maxit ); 

/*-----------------------------fim do laco nao linear-------------------------------*/
		 
		 
		 
/*----------------------------fim do preditor/multicorretor------------------------ */		
		}
	}while(re_execucao1());
return 0;
}

 /*  dt <= L/c
 L= comprimento do elemento
 c= velocidade da onda no meio
  */

