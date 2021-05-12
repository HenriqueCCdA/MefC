#include <Tipos_Wave.h>
#include <Extern_Wave.h>

void numeq (long *neq) {
   long i,j;
	
   *neq = 0;
   for (i = 0; i < nnode; i++)   {
      for (j = 0; j < ndf; j++)   {
	     if (node[i].eqn[j] == 0)   
		    node[i].eqn[j] = (*neq)++;
		 else   {
			 node[i].eqn[j] = -1;
		 }
	  }
   }
}
