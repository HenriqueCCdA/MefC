#include <Tipos_Wave.h>
#include <Extern_Wave.h>

void profil (long jd[],long neq, long *nad)  {
	int i, n, ii, jj, mm, k, no;

	for(i = 0; i < neq; i++)   
		jd[i] = 0 ;

	for (n = 0; n < numel; n++) {
		mm = -1;
		for (i = 0; i < nen; i++)   {
			no = elmt[n].node[i];
			if (no == 0) break;
			for (k = 0; k < ndf; k++)   {
				jj = node[no-1].eqn[k];
				if (jj > -1)   { 
					if (mm == -1) mm = jj;  
			        mm = min(mm,jj);
				}
			}
		}
		for (i = 0; i < nen; i++) {
			no = elmt[n].node[i];
			if (no == 0) break;
			for (k = 0; k < ndf; k++)   {
				ii = node[no-1].eqn[k];
				if (ii > -1)   {
					jj = jd[ii];
				    jd[ii] = max(jj,ii-mm);
				}
			}
		}
	}
	*nad = 0;
    jd[0] = 0;
	if (neq > 1)   {
		for (n = 1; n < neq; n++)  
			jd[n] = jd[n] + jd[n-1];
		*nad = jd[neq-1];
	}
	mm = 0;
	if (neq > 0) mm = (*nad+neq)/neq;
}
