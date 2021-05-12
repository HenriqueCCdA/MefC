#include <Tipos_Wave.h>
#include <Extern_Wave.h>

void apply_forces (void)   {
    long i,j,no,k,ii;
	
	for(i = 0; i < numel; i++)   {

		for(j = 0; j < nen; j++)   {
		   no = elmt[i].node[j];
		   for (k = 0; k < ndf; k++)   {
			  ii = node[no-1].eqn[k];
		      if (node[no-1].eqn[k] > -1)  b[ii] = node[no-1].fp[k];/*fontes e fluxos prescritos*/		   }
		}

	}

}
 
