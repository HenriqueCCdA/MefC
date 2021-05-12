void matvec_csr_c(long n,long ia[],long ja[],double ad[],double a[],double *dumf,double x[],double y[])

{
    long i, k;
	double t;
	
	for(i = 0; i < n; i++)   {

/*      Produto da diagonal de A por x:     */

		t = ad[i]*x[i];

/*      Produto da linha i pelo vetor x (parte triangular inferior):   */
       
	    for(k = ia[i]; k < ia[i+1]; k++)
            t += a[k]*x[ja[k]];

/*      Armazena o resultado em y(i):    */
        
        y[i] = t;
	}      
}

void matvec_csrc_sym_c(long n,long ia[],long ja[],double ad[],double al[],double au[],double x[],double y[])
{
    long i,k,jak;
	double s,t,xi;

/*  Produto da parte triangular superior pelo vetor x:  */
	
	for(i = 0; i < n; i++)   {

/*      Produto da diagonal de A por x:   */
        xi = x[i];
		t = ad[i]*x[i];

       
		for(k = ia[i]; k < ia[i+1]; k++)   {
            jak = ja[k];
            s   = al[k];
/*          Produto da linha i pelo vetor x (parte triangular inferior):*/
            t += s*x[jak];
/*          Produto dos coef. da parte triangular superior por x(i):*/
            y[jak] += s*xi;
	    }
/*     Armazena o resultado em y(i):*/       
        y[i] = t;
	}      
}

void matvec_skyline(long neq,long *dum,long jd[],double ad[],double *dumf,double au[],double x[],double y[]) {
	
	long i, j, l, c, k;
    
	for(i = 0; i < neq; i++) {
    	y[i] = ad[i]*x[i];
	}
           /*atriz superior*/
	for (j = 1; j < neq; j++)   {
		c = jd[j] - jd[j-1];
		i = j-c;
		for (k = 0; k < c; k++)   {
		   l = jd[j]-c+k;
		   y[i] = y[i] + au[l]*x[j];
		   y[j] = y[j] + au[l]*x[i];
		   i++;
		}
	}
}
double dot_c(double a[],double b[],long n)
{
    long i;
    double c = 0.0;

	for(i = 0; i < n; i++) c += a[i]*b[i];
	return(c);
}
