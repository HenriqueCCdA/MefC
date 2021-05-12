#include<stdio.h>

extern long nnode, numel, ndm, ndf, nen, numat;
extern double  s[8][8], p[8], xl[3][8], u[8],v[8],a[8],b[MAXNODES],ad[MAXSIST],au[MAXSIST]
               ,al[MAXSIST],dt,fcorte,x[MAXNODES],r[MAXNODES],z[MAXNODES];
extern long ld[10],jc,step,con,jd[MAXNODES];
extern char arqsaida[81];
extern ELEMENT elmt[MAXELEMENTS];
extern MATERIAL mate[MAXMAT];
extern ELEMENT_TYPE eltype[MAXELTYPE];
extern NODE node[MAXNODES];
extern  FILE *fileout1;
