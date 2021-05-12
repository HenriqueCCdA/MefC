#include <stdio.h>
#include <stdlib.h>
#include <Tipos.h>
#include <Global.h>

                                                                     

void read_file(void);
void numeq(long *);
void profil (long [],long, long *);
void apply_forces (void); 
void predict(void);
void pform(long jd[]);
void correct (double x[]);
void solver_c(long n,long ia[],long ja[],double ad[],double a[],double b[],double x[],double z[],double r[],double tol,long maxit);
void arqu_malha ();
int re_execucao1(void);
void saida (long j);

void arqu_res(long j);
void main(void){
   
	
	long neq, nad, maxit,*dum;
	long jd[1000],i;
	double x[1000],r[1000],z[1000],tol;
    
	
	tol = 1.0e-011;
	maxit = 1000;
	dum = jd;
	
	
	
	
	do{
		read_file();
	    arqu_malha ();
		numeq(&neq);
	    profil(jd,neq,&nad);
		for (i = 0; i < step; i++)   {
	       printf ("step=%ld \n",i);  
	       arqu_res(i);
		   apply_forces(); 
		   predict();
		   pform(jd);
           /*saida(i);*/
		   solver_c(neq,dum,jd,ad,au,b,x,z,r,tol,maxit);
		   correct(x);	 
		  		
		   
		}  
	}while(re_execucao1());   

}

 /*  dt <= L/c 
 L= comprimento do elemento
 c= velocidade da onda no meio
  */ 
