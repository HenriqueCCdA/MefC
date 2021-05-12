
/*	Headers:   */
	#include <stdio.h>
	#include <math.h>

/*	Prototipos de funcoes:   */
	void pcg_c(long n,long ia[],long ja[],double ad[],double a[],double b[],double x[],double z[],double r[],double tol,long maxit,void(*matvec)());
	void matvec_csr_c(long n,long ia[],long ja[],double ad[],double a[],double *dumf,double x[],double y[]);
	void matvec_csrc_sym_c(long n,long ia[],long ja[],double ad[],double al[],double au[],double x[],double y[]);
    void matvec_skyline(long neq,long *dum,long jd[],double ad[],double *dumf,double au[],double x[],double y[]);

	double dot_c(double a[],double b[],long n);


void solver_c(long n,long ia[],long ja[],double ad[],double a[],double b[],double x[],double z[],double r[],double tol,long maxit)
{
	void(*matvec)();

	long i;
	for (i = 0; i < n; i++)   {
		x[i] = 0.0;	
	}
    matvec = matvec_skyline;
	pcg_c(n,ia,ja,ad,a,b,x,z,r,tol,maxit,matvec);
}

void pcg_c(long n,long ia[],long ja[],double ad[],double a[],double b[],double x[],double z[],double r[],double tol,long maxit,void(*matvec)())
{
      long i,j;
	  double alpha,c,d,conv,energy;

	  matvec(n,ia,ja,ad,a,a,x,z);
     
	  for(i = 0; i < n; i++)   {
         r[i] = b[i] - z[i];
         z[i] = r[i] / ad[i];
         b[i] = z[i];
	  }
      d    = dot_c(r,z,n);
      conv = tol * sqrt(fabs(d));
/*--------------------------------------------------------*/   
	  for(j = 0; j < maxit; j++)   {
         matvec(n,ia,ja,ad,a,a,b,z);
         alpha = d / dot_c(b,z,n);

	     for(i = 0; i < n; i++)   {
            x[i] +=  alpha * b[i];
            r[i] -=  alpha * z[i];
            z[i] = r[i] / ad[i];
		 }
         c = dot_c(r,z,n) / d;

		 for(i = 0; i < n; i++)   {
            b[i] = z[i] + c * b[i];
		 }
         d = c * d;
	   if (sqrt(fabs(d)) < conv) break;
	  }
/* -------------------------------------------------------*/
      matvec(n,ia,ja,ad,a,a,x,z);
      energy = dot_c(x,z,n);
/* -------------------------------------------------------*/
	  printf(" (PCG) solver:\n\tEquations   = %13d\n\tIterarions  = %13d\n\tEnergy norm = %e\n",n,++j,energy);
	  if(--j == maxit) printf(" *** WARNING: no convergende reached !\n");

}

