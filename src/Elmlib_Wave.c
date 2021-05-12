
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Tipos_Wave.h>
#include <Extern_Wave.h>
#include <int_num.h>
#define ZERO 1.0e-14  


void elmt01(long nel,short mat);
void elmt02(long nel,short mat);
void elmt03(long nel,short mat);
void elmt04(long nel,short mat);
void elmt05(long nel,short mat);
void jacob2d(double eps ,double nn,double *de,double *dn,double *hx,double *hy,long nel,double *det,short matriz);
void jacob3d(double eps ,double nn,double ze,double *deps,double *dnn,double *dze ,double *hx,double *hy,double *hz, long nel,double *det,short matriz);
void sfquad4(double eps ,double nn,double *N,double *de,double *dn,short matriz);   
void sfhexd8(double eps ,double nn,double ze,double *N,double *deps,double *dnn,double *dze,short matriz);



void elmlib(long nel,short type,short mat)   {
	switch(type) {
		case 1:
			elmt01(nel,mat);
			break;
		case 2:
			elmt02(nel,mat);
			break;
		case 3:
			elmt03(nel,mat);
		    break;
        case 4:
			elmt04(nel,mat);
		    break;
        case 5:
			elmt05(nel,mat);
		    break;
		default:	
		printf("Tipo de elemento nao especificado !");
		exit(0);
	}
}

/*________________________ ELMT01: Elemento unidimensional(dois nois) ________________________________________________
  Parametros de entrada:
                                   
     xl  - coordenadas nodais locais                         
     u   - valores prescritos                                
     p   - nodal forces                                             
     ndm - dimensao                                                 
     nst - numero de graus de liberdade por elemento                
     nel - numero do elemento                                       
     
  Parametros de saida:                                             
                                                                    
     s - matriz de elemento                                         
     p - resíduo        
    
_______________________________________________________________________________________*/
void elmt01(long nel,short mat)   {
      
	double hx[2],det,wt,e,m[2][2];
	long i,j;

	    for (i =0; i < 2; i++)   {
	     	for (j = 0; j < 2;j++)  { 
		     	s[i][j] = 0.0;
		        m[i][j] = 0.0;
		    }
	    }

	    det = 0;
	    for (i = 0; i < ndm; i++)   {
	     	det = det + (xl[i][1] - xl[i][0])*(xl[i][1] - xl[i][0]);
	    }
	    det = sqrt(det);
	    if (det <= 0.0)   {
		   printf("*** Subrotina ELMT01: determinante nulo ou negativo do elemento %ld", nel); 
		   exit(0); 
	    }
        /*... Derivadas das funcoes de interpolacao:*/
        hx[0] = -1/det;
        hx[1] = 1/det;
	    e = mate[mat-1].prop[0];

        /*... Matriz de rigidez: */

        wt =det;
        s[0][0] = (hx[0]*hx[0])*wt;
        s[0][1] = (hx[0]*hx[1])*wt;
        s[1][1] = (hx[1]*hx[1])*wt;
        s[1][0] =  s[0][1];
 
	
        /*... Matriz de massa: */

        wt =det*e*e;
        m[0][0] = wt/3.0;
        m[0][1] = wt/6.0;
        m[1][1] = m[0][0];
        m[1][0] =  m[0][1];

        /*... Forcas internas:*/ 

        p[0]= m[0][0]*a[0] + m[0][1]*a[1] + s[0][0]*u[0]+ s[0][1]*u[1];
        p[1]= m[0][1]*a[0] + m[1][1]*a[1] + s[0][1]*u[0]+ s[1][1]*u[1];

        /* calculo da matriz de Massa equivalente:*/

	    for (i=0;i<nen;i++)   
	     	  for (j=0;j<nen;j++)
	             s[i][j] = m[i][j] + beta*dt*dt*s[i][j];
	    
	 
}
/*__________________________elmt02: elemento triangular linear (3 nois)__________________

Parametros de entrada:
                                   
     xl  - coordenadas nodais locais                         
     u   - valores prescritos                                
     p   - nodal forces                                             
     ndm - dimensao                                                 
     nst - numero de graus de liberdade por elemento                
     nel - numero do elemento                                       
  
  Parametros de saida:                                             
                                                                    
     s - matriz de elemento                                         
     p - resíduo  


________________________________________________________________________________________*/

void elmt02(long nel,short mat)   {
      
	double hx[2],hy[2],xj11,xj22,xj12,xj21,det,wt,m[3][3],e;
	long i,j;

	for (i =0; i < 3; i++)   {
		for (j = 0; j < 3;j++)  { 
			s[i][j] = 0.0;
		    m[i][j] = 0.0;
		}
	}

      xj11 = xl[0][0]-xl[0][2];
      xj12 = xl[1][0]-xl[1][2];
      xj21 = xl[0][1]-xl[0][2];
      xj22 = xl[1][1]-xl[1][2];
      det  = xj11*xj22-xj12*xj21;
	  if (det <= 0.0)   {
		  printf("*** Subrotina ELMT02: determinante nulo ou negativo do elemento %ld", nel); 
		  exit(0); 
	  }
/*... Derivadas das funcoes de interpolacao:*/
      hx[0] =  xj22/det;
      hx[1] = -xj12/det;
      hy[0] = -xj21/det;
      hy[1] =  xj11/det;
	  e = mate[mat-1].prop[0];

/*... Matriz de rigidez:  */

      wt =0.5*det;
      s[0][0] = (hx[0]*hx[0]+hy[0]*hy[0])*wt;
      s[0][1] = (hx[0]*hx[1]+hy[0]*hy[1])*wt;
      s[1][1] = (hx[1]*hx[1]+hy[1]*hy[1])*wt;
      s[0][2] = -s[0][0]-s[0][1];
      s[1][2] = -s[0][1]-s[1][1];
      s[2][2] = -s[0][2]-s[1][2];
      s[1][0] =  s[0][1];
      s[2][0] =  s[0][2];
      s[2][1] =  s[1][2];

 /*... Matriz de massa:*/
	  wt =det*e*e;
	  m[0][0] =  wt/12.0;
	  m[0][1] =  wt/24.0;
	  m[1][1] =  wt/12.0;
	  m[0][2] =  m[0][1];
	  m[1][2] =  m[0][1];
	  m[2][2] =  m[1][1];
	  m[1][0] =  m[0][1];
	  m[2][0] =  m[0][2];
	  m[2][1] =  m[1][2];


/*... Forcas internas:*/

      p[0]= m[0][0]*a[0] + m[0][1]*a[1] + m[0][2]*a[2] + s[0][0]*u[0]+ s[0][1]*u[1]+s[0][2]*u[2];
      p[1]= m[1][0]*a[0] + m[1][1]*a[1] + m[1][2]*a[2] + s[1][0]*u[0]+ s[1][1]*u[1]+s[1][2]*u[2];
      p[2]= m[2][0]*a[0] + m[2][1]*a[1] + m[2][2]*a[2] + s[2][0]*u[0]+ s[2][1]*u[1]+s[2][2]*u[2];

/*... calculo de Massa equivalente:*/

	  for (i=0;i<nen;i++)   
		  for (j=0;j<nen;j++)
	         s[i][j] = m[i][j] + beta*dt*dt*s[i][j];

}


/*__________________________elmt03: elemento quadrilatero bilinear (4 nois)__________________

Parametros de entrada:
                                   
     xl  - coordenadas nodais locais                         
     u   - valores prescritos                                
     p   - nodal forces                                             
     ndm - dimensao                                                 
     nst - numero de graus de liberdade por elemento                
     nel - numero do elemento                                       
  
  Parametros de saida:                                             
                                                                    
     s - matriz de elemento                                         
     p - resíduo  


_____________________________________________________________________________________________*/

void elmt03(long nel, short mat){


	double det,de[4],dn[4],e,eps,nn,wt,hx[4],hy[4],N[4],m[4][4],alf,bet;
	long k, q;
    short matriz,i,j,nint;
		 
    for (i =0; i < 4; i++)   {
		for (j = 0; j < 4;j++)   { 
			s[i][j] = 0.0;
		    m[i][j]= 0.0; 
		}
	}
/*Matriz de rigidez - 2 pontos de integração*/
	nint=2;
	matriz=2;/* matriz rigides -2 convenção minha */
	for(i=0;i<nint;i++){			
	    eps = intponto(nint,i);
		alf = peso(nint,i);
		for(j=0;j<nint;j++){
			nn=intponto(nint,j);
	        bet=peso(nint,j);
			sfquad4(eps,nn,N,de,dn,matriz);
		    jacob2d(eps,nn,de,dn,hx,hy,nel,&det,matriz);
			e = mate[mat-1].prop[0];                   
			wt = det;
			for (k=0;k<4;k++)  
				for ( q=0;q<4;q++)   
					s[k][q] = s[k][q] +  alf*bet*wt*(hx[k]*hx[q]+hy[k]*hy[q]);
		}
	}
 /*Matriz de massa- 3 pontos de integração*/	
    matriz=1;/* matriz rigides -1 convenção minha */
	nint=3;
	for(i=0;i<nint;i++){			
	    eps=intponto(nint,i);
		alf=peso(nint,i);
		for(j=0;j<nint;j++){
			nn=intponto(nint,j);
	        bet=peso(nint,j);
			sfquad4(eps,nn,N,de,dn,matriz);
			jacob2d(eps,nn,de,dn,hx,hy,nel,&det,matriz);
			wt = det*e*e;
			for(k=0;k<4;k++)
				for(q=0;q<4;q++){
				   m[k][q]= alf*bet*N[k]*N[q]*wt +m[k][q];
				}
		
		}
	}	
		
	
/*forças internas*/
for(i=0;i<4;i++){
     p[i]= 0.0;
     for(j=0;j<4;j++)
	       p[i]= m[i][j]*a[j]+ s[i][j]*u[j]+ p[i];
} 
/*matiz de massa equivalente*/
for (i=0;i<nen;i++)   
		  for (j=0;j<nen;j++)
	         s[i][j] = m[i][j] + beta*dt*dt*s[i][j];

}



/*__________________________elmt04: elemento tetraedrico  (4 nois)__________________

Parametros de entrada:
                                   
     xl  - coordenadas nodais locais                         
     u   - valores prescritos                                
     p   - nodal forces                                             
     ndm - dimensao                                                 
     nst - numero de graus de liberdade por elemento                
     nel - numero do elemento                                       
  
  Parametros de saida:                                             
                                                                    
     s - matriz de elemento                                         
     p - resíduo  


_____________________________________________________________________________________________*/

void elmt04(long nel, short mat)   {

	double hx[4],hy[4],hz[4],Jac[3][3],det,wt,m[4][4],e;
	long i,j;
  
	for (i =0; i < 4; i++)   {
		for (j = 0; j < 4;j++)   { 
			s[i][j] = 0.0;
		    m[i][j]= 0.0; 
		}
	}
  
  /*Matriz Jacobiana*/
	         
	  Jac[0][0] = xl[0][0]-xl[0][3];
      Jac[0][1] = xl[1][0]-xl[1][3];
      Jac[0][2] = xl[2][0]-xl[2][3];
      Jac[1][0] = xl[0][1]-xl[0][3];
      Jac[1][1] = xl[1][1]-xl[1][3];
      Jac[1][2] = xl[2][1]-xl[2][3];
      Jac[2][0] = xl[0][2]-xl[0][3];
      Jac[2][1] = xl[1][2]-xl[1][3];
      Jac[2][2] = xl[2][2]-xl[2][3];




    det=   Jac[0][0] * Jac[1][1] * Jac[2][2]  +  Jac[0][1] * Jac[1][2] * Jac[2][0] +  Jac[0][2] * Jac[1][0] * Jac[2][1]   
     - Jac[2][0] * Jac[1][1] * Jac[0][2] -  Jac[0][1] * Jac[1][0] * Jac[2][2] -  Jac[0][0] * Jac[2][1] * Jac[1][2];
 
    if (det <= 0.0)   {
		printf("*** Subrotina ELMT04: determinante nulo ou negativo do elemento ->  %ld ", nel); 
		exit(0); 
	 }
     /*Derivadas das funcoes N:*/

	hx[0] = (1/det)* (Jac[1][1]*Jac[2][2]-Jac[1][2]*Jac[2][1]);
	hx[1] = (1/det)* (Jac[0][2]*Jac[2][1]-Jac[2][2]*Jac[0][1]);
	hx[2] = (1/det)* (Jac[0][1]*Jac[1][2]-Jac[0][2]*Jac[1][1]);
	hy[0] = (1/det)* (Jac[2][0]*Jac[1][2]-Jac[1][0]*Jac[2][2]);
	hy[1] = (1/det)* (Jac[0][0]*Jac[2][2]-Jac[2][0]*Jac[0][2]);
	hy[2] = (1/det)* (Jac[1][0]*Jac[0][2]-Jac[0][0]*Jac[1][2]);
	hz[0] = (1/det)* (Jac[1][0]*Jac[2][1]-Jac[2][0]*Jac[1][1]);
	hz[1] = (1/det)* (Jac[2][0]*Jac[0][1]-Jac[0][0]*Jac[2][1]);
	hz[2]=  (1/det)* (Jac[0][0]*Jac[1][1]-Jac[1][0]*Jac[0][1]);
	hx[3] = -hx[0]-hx[1]-hx[2];
	hy[3] = -hy[0]-hy[1]-hy[2];
	hz[3] = -hz[0]-hz[1]-hz[2];

	e = mate[mat-1].prop[0];

	/*matriz de rigidez: */                  

    wt = det/6.0;
		for (i = 0; i < 4;i++)   {
			for (j = 0; j < 4; j ++)   {
				s[i][j] = (hx[i]*hx[j] + hy[i]*hy[j] + hz[i]*hz[j])*wt;
			}
		}

    /* Matriz de massa:*/

	 wt = det*e*e;
		for (i = 0; i < 4;i++)   {
			for (j = 0; j < 4; j ++)   {
				if ( i == j) 
					m[i][j] = wt/60.0;
				else 
					m[i][j] = wt/120.0;
			}
		}
	/*... Forcas internas:*/

      p[0]= m[0][0]*a[0] + m[0][1]*a[1] + m[0][2]*a[2] + m[0][3]*a[3]+ s[0][0]*u[0]+ s[0][1]*u[1]+s[0][2]*u[2]+ s[0][3]*u[3];
      p[1]= m[1][0]*a[0] + m[1][1]*a[1] + m[1][2]*a[2] + m[1][3]*a[3]+ s[1][0]*u[0]+ s[1][1]*u[1]+s[1][2]*u[2]+ s[1][3]*u[3];
      p[2]= m[2][0]*a[0] + m[2][1]*a[1] + m[2][2]*a[2] + m[1][3]*a[3]+ s[2][0]*u[0]+ s[2][1]*u[1]+s[2][2]*u[2]+ s[2][3]*u[3];
	  p[3]= m[3][0]*a[0] + m[3][1]*a[1] + m[3][2]*a[2] + m[3][3]*a[3]+ s[3][0]*u[0]+ s[3][1]*u[1]+s[3][2]*u[2]+ s[3][3]*u[3];

	 /*... calculo de Massa equivalente:*/

	  for (i=0;i<nen;i++)   
		  for (j=0;j<nen;j++)
	         s[i][j] = m[i][j] + beta*dt*dt*s[i][j]; 

}




/*necessario testar*/
void elmt05(long nel, short mat){

    double det,e,eps,nn,ze,wt,hx[8],hy[8],hz[8],deps[8],dnn[8],dze[8],N[8],m[8][8],alf,bet,teta;
	long k, q;
    short matriz,i,j,l,nint;
		 
    for (i =0; i < 8; i++)   {
		for (j = 0; j < 8;j++)   { 
			s[i][j] = 0.0;
		    m[i][j]= 0.0; 
		}
	}
    
/*Matriz de rigidez - 2 pontos de integração............................................*/
	nint=2;
	matriz=2;/* matriz rigides -2 convenção minha */ 
	for(i=0;i<nint;i++){			
	    eps = intponto(nint,i);
		alf = peso(nint,i);
		for(j=0;j<nint;j++){
			nn=intponto(nint,j);
	        bet=peso(nint,j);
			for(l=0;l<nint;l++){
			  ze=intponto(nint,l);
	          teta=peso(nint,l);
			  sfhexd8(eps , nn, ze, N,deps,dnn,dze, matriz);
 		      jacob3d(eps, nn, ze, deps, dnn, dze ,hx, hy, hz, nel,&det,matriz);
			  e = mate[mat-1].prop[0];                   
			  wt = alf*bet*teta*det;
			  for (k=0;k<8;k++)  
				 for (q=0;q<8;q++)   
				   	s[k][q] = s[k][q] + wt*( hx[k]*hx[q] + hy[k]*hy[q]+ hz[k]*hz[q] );
			}
	 	}
	}
/*.....................................................................................*/
	
/*Matriz de massa- 3 pontos de integração...............................................*/	
    matriz=1;/* matriz rigides -1 convenção minha */
	nint=3;
	for(i=0;i<nint;i++){			
	    eps=intponto(nint,i);
		alf=peso(nint,i);
		for(j=0;j<nint;j++){
			nn=intponto(nint,j);
	        bet=peso(nint,j);
			for(l=0;l<nint;l++){
			   ze=intponto(nint,l);
	           teta=peso(nint,l);
			   sfhexd8(eps,nn,ze,N,deps,dnn,dze,matriz);
			   jacob3d(eps,nn,ze,deps,dnn,dze,hx,hy,hz,nel,&det,matriz);
			   wt = alf*bet*teta*det*e*e;
			   for(k=0;k<8;k++)
			    	for(q=0;q<8;q++){
				      m[k][q]= N[k]*N[q]*wt +m[k][q];
				}
			}
		}
	}	
/*....................................................................................*/

	
/*.............................forças internas........................................*/
for(i=0;i<8;i++){
     p[i]= 0.0;
     for(j=0;j<8;j++)
	       p[i]= m[i][j]*a[j]+ s[i][j]*u[j]+ p[i];
}
/*....................................................................................*/


/*.............................matiz de massa equivalente.............................*/
for (i=0;i<nen;i++)   
	  for (j=0;j<nen;j++)
	         s[i][j] = m[i][j] + beta*dt*dt*s[i][j];
/*....................................................................................*/

}
/*_____________________________________ Funções de apoio __________________________________*/



/*____________________________ Jacob2d __________________________________________
 *Quadrilátero bilenear
 *Descrição
  Calcula a matriz jacobiana inversa e o det do ponto (e,n) e as derivada da em
  função de intepolação em relação a x,y   

*parametros de entrada: 

eps - coordenada do ponto de integração 
nn  - coordenada do ponto de integração
nel - numero do elemneto
matriz - Matriz de massa ou rigidez

*parametros intrisicos a lingagem c:

*dn,*de -  endereço das derivadas(e,n) da funçao de interpolação( em relação a elmt03)
det -  endereço do determinante( em relação a elmt03)
*hx,*hy -endereço das derivadas(x,y) da funçao de interpolação( em relação a elmt03)

*parametros de saida: 
hx,hy- derivadas(x,y) da funçao de interpolação
det - determinante da matriz jacobiana normal
___________________________________________________________________________________
*/
void jacob2d(double eps ,double nn,double *de,double *dn,double *hx,double *hy,long nel,double *det,short matriz)
{
    
 double DET,jaci[2][2],jac[2][2];
 long z,i,j;
            
/*.................................matriz jacobiana..................................... */
 for(i=0;i<2;i++){
         jac[0][i] = 0.0;
         jac[1][i] = 0.0;
         
		 for(j=0;j<nen;j++){
            jac[0][i] = jac[0][i] + de[j] * xl[i][j];
            jac[1][i] = jac[1][i] + dn[j] * xl[i][j];
         }
 }
/*.......................................................................................*/		    

			DET = jac[0][0]*jac[1][1]-jac[1][0]*jac[0][1];

		    if (DET <= ZERO)   {
		        printf("*** Subrotina ELMT03: determinante nulo ou negativo do elemento %ld", nel); 
		        exit(0); 
		    }

/*..................................jacobiano inverso....................................*/
	
	if(matriz==2){		
			jaci[0][0]= (1/DET )*jac[1][1];
		    jaci[0][1]=-(1/DET )*jac[1][0];
		    jaci[1][0]=-(1/DET )*jac[0][1];
		    jaci[1][1]= (1/DET )*jac[0][0];
/*.......................................................................................*/
    
			
/*........................Derivadas(x,y) das funcoes de interpolacao:................... */			
			for (z = 0; z<4;z++)   {
			hx[z] = jaci[0][0]*de[z] +jaci[0][1]*dn[z];
			hy[z] = jaci[1][0]*de[z] +jaci[1][1]*dn[z];
			}
	}
/*.......................................................................................*/					
			*det=DET;

}


/*_______________________________jacob3d_______________________________________

*Descrição
 Calcula a matriz jacobiana inversa e o det do ponto (eps,nn,ze) e as derivada da em
 função de intepolação em relação a x,y,z, para um elemento geral em 3d  

*parametros de entrada: 
nen       - numero de nois por elemento
eps,nn,ze - coordenada do ponto de integração 
nel       - numero do elemento
matriz - Matriz de massa ou rigidez

*parametros intrisicos a lingagem c:
hx,hy,hz     -  endereço das derivadas de N em relação a coordenadas (x,y,z)( em relação a elmt05)
deps,dnn,dze -  endereço das derivadas de N em relação a coordenadas naturais( em relação a elmt05)
det          -  endereço do determinante( em relação a elmt03)

*parametros de saida: 
hx,hy,hz -  derivadas de N em relação a coordenadas (x,y,z)
det      -  determinante da matriz jacobiana normal

___________________________________________________________________________________________________________
*/




void jacob3d(double eps,double nn,double ze,double *deps,double *dnn,double *dze ,double *hx,double *hy,double *hz, long nel,double *det,short matriz){

 double jac[3][3],jaci[3][3],DET;
 long i,j;

 
 
/*..................Calculo da matriz jacobiana...................... */ 
 for(i=0;i<3;i++){
         jac[0][i] = 0.0;
         jac[1][i] = 0.0;
         jac[2][i] = 0.0;
		 for(j=0;j<nen;j++){
            jac[0][i] = jac[0][i] + deps[j] * xl[i][j];
            jac[1][i] = jac[1][i] + dnn[j]  * xl[i][j];
            jac[2][i] = jac[2][i] + dze[j]  * xl[i][j];
		 }
/*....................................................................*/ 
 }

/*..................determinante da matriz jacobiana...................... */ 
      DET=jac[0][0]*jac[1][1]*jac[2][2] + jac[0][1]*jac[1][2]*jac[2][0] + jac[0][2]*jac[1][0]*jac[2][1]   
     - jac[2][0]*jac[1][1]*jac[0][2] - jac[0][1]*jac[1][0]*jac[2][2] - jac[0][0]*jac[2][1]*jac[1][2];
 
   if (DET <= ZERO)   {
		printf("*** Subrotina ELMT05: determinante nulo ou negativo do elemento ->  %ld ", nel); 
		exit(0); 
   }
/*..........................................................................*/
	
/*...................Inversa da matriz Jacobiana:...........................*/  
   if(matriz==2){
      jaci[0][0] =  ( jac[1][1] * jac[2][2] - jac[1][2] * jac[2][1] ) / DET;
      jaci[1][0] = -( jac[1][0] * jac[2][2] - jac[1][2] * jac[2][0] ) / DET;
      jaci[2][0] =  ( jac[1][0] * jac[2][1] - jac[1][1] * jac[2][0] ) / DET;
      jaci[0][1] = -( jac[0][1] * jac[2][2] - jac[0][2] * jac[2][1] ) / DET;
      jaci[1][1] =  ( jac[0][0] * jac[2][2] - jac[0][2] * jac[2][0] ) / DET;
      jaci[2][1] = -( jac[0][0] * jac[2][1] - jac[0][1] * jac[2][0] ) / DET;
      jaci[0][2] =  ( jac[0][1] * jac[1][2] - jac[0][2] * jac[1][1] ) / DET;
      jaci[1][2] = -( jac[0][0] * jac[1][2] - jac[0][2] * jac[1][0] ) / DET;
      jaci[2][2] =  ( jac[0][0] * jac[1][1] - jac[0][1] * jac[1][0] ) / DET;
/*...........................................................................*/
 

/*...............Derivadas(x,y,z) das funcoes de interpolacao:.............. */
      for(i=0;i<nen;i++){   
         hx[i] = jaci[0][0]*deps[i] + jaci[0][1]*dnn[i] + jaci[0][2]*dze[i];
         hy[i] = jaci[1][0]*deps[i] + jaci[1][1]*dnn[i] + jaci[1][2]*dze[i];
         hz[i] = jaci[2][0]*deps[i] + jaci[2][1]*dnn[i] + jaci[2][2]*dze[i];
      }
   }
/*............................................................................*/
  *det=DET;

}



/*___________________SFQUADD4 __________________ 
*Quadrilatero bilinear
  Calculo das Funções de interpolaçãp 
  

*parametros de entrada:

eps - coordenada do ponto de integração 
nn  - coordenada do ponto de integração
matriz - qual matriz esta sendo calculada (massa ou rigidez)

*parametros intrisicos a lingagem c:

N   - endereço funções de interpolacão( em relação a elmt03)
de,dn - endereço das derivadas(e,n) das funções deinterpolação( em relação a elmt03)
hx -  endereço das derivadas(x)das funções interpolacão( em relação a elmt03)
hy -  endereço das derivadas(y)das funções interpolacão( em relação a elmt03)

 calculo das Funções de interpolaçãp 
 calculo das derivas em relação a x e y  

*parametros de entrada: 
N  - Funçao de interpolação 
dn - derivada de N em relação a n
de - derivada de N em relação a e
_____________________________________________________________________________________
*/


void   sfquad4(double eps ,double nn,double *N,double *de,double *dn,short matriz){
		
		
	if(matriz==1){
	
		/* função de interpolação*/
	       N[0]=(1/4.0)*(1+eps)*(1+nn);
	       N[1]=(1/4.0)*(1-eps)*(1+nn);
	       N[2]=(1/4.0)*(1-eps)*(1-nn);
	       N[3]=(1/4.0)*(1+eps)*(1-nn);
	}	
  

		
	/*calculando os dNi/dx e dNi/dy*/
	else if(matriz==2) { 
		de[0]= (1+nn)/4.0;
		de[1]= (-1-nn)/4.0;
		de[2]= (-1+nn)/4.0;
		de[3]= (1-nn)/4.0;
		dn[0]= (1+eps)/4.0;
		dn[1]= (1-eps)/4.0;
		dn[2]= (-1+eps)/4.0;
		dn[3]= (-1-eps)/4.0;		
	}	
}






/* _______________________           sfhex8          ___________________________________
* HEXAEDRO LINEAR DE 8 NÓS.
Cálculo da função de interpolação e suas derivadas(x,y,z) 
nas coordenadas naturais (eps,nn,ze) no hexaedro linear de 8 nós.
Calculo das Funções de interpolaçãp 
 

*parametros de entrada:

eps,nn,ze - coordenada do ponto de integração 

matriz - qual matriz esta sendo calculada (massa ou rigidez)

*parametros intrisicos a lingagem c:

N   - endereço funções de interpolacão( em relação a elmt05)
deps,dnn,dze -  endereço das derivadas( em relação a elmt05)


*parametros de saida: 
N  - Funçao de interpolação 
deps,dnn,dze - derivada de N em relação a (eps,nn,ze)

______________________________________________________________________________________
*/


void sfhexd8(double eps ,double nn,double ze,double *N,double *deps,double *dnn,double *dze,short matriz){


/*............Função de interpolação..............*/
	if(matriz==1){
	  N[0]  = ( 1.0+eps ) * ( 1.0+nn ) * (1.0+ze) / 8.0;
      N[1]  = ( 1.0-eps ) * ( 1.0+nn ) * (1.0+ze) / 8.0;
      N[2]  = ( 1.0-eps ) * ( 1.0-nn ) * (1.0+ze) / 8.0;
      N[3]  = ( 1.0+eps ) * ( 1.0-nn ) * (1.0+ze) / 8.0;
      N[4]  = ( 1.0+eps ) * ( 1.0+nn ) * (1.0-ze) / 8.0;
      N[5]  = ( 1.0-eps ) * ( 1.0+nn ) * (1.0-ze) / 8.0;
      N[6]  = ( 1.0-eps ) * ( 1.0-nn ) * (1.0-ze) / 8.0;
      N[7]  = ( 1.0+eps ) * ( 1.0-nn ) * (1.0-ze) / 8.0;
	}
/*.................................................*/

/*..................derivadas......................*/
	else if(matriz==2){
/*...........derivadas em relacao a eps :..........*/

      deps[0]  =   (1.0+nn) * (1.0+ze) / 8.0;
      deps[1]  = - (1.0+nn) * (1.0+ze) / 8.0;
      deps[2]  = - (1.0-nn) * (1.0+ze) / 8.0;
      deps[3]  =   (1.0-nn) * (1.0+ze) / 8.0;
      deps[4]  =   (1.0+nn) * (1.0-ze) / 8.0;
      deps[5]  = - (1.0+nn) * (1.0-ze) / 8.0;
      deps[6]  = - (1.0-nn) * (1.0-ze) / 8.0;
      deps[7]  =   (1.0-nn) * (1.0-ze) / 8.0;

/*...........derivadas em relacao a nn :...........*/

      dnn[0]  =  (1.0+eps) * (1.0+ze) / 8.0;
      dnn[1]  =  (1.0-eps) * (1.0+ze) / 8.0;
      dnn[2]  = -(1.0-eps) * (1.0+ze) / 8.0;
      dnn[3]  = -(1.0+eps) * (1.0+ze) / 8.0;
      dnn[4]  =  (1.0+eps) * (1.0-ze) / 8.0;
      dnn[5]  =  (1.0-eps) * (1.0-ze) / 8.0;
      dnn[6]  = -(1.0-eps) * (1.0-ze) / 8.0;
      dnn[7]  = -(1.0+eps) * (1.0-ze) / 8.0;

/*............derivadas em relacao a eps :..........*/

      dze[0]  =  ( 1.0+eps ) * ( 1.0+nn ) / 8.0;
      dze[1]  =  ( 1.0-eps ) * ( 1.0+nn ) / 8.0;
      dze[2]  =  ( 1.0-eps ) * ( 1.0-nn ) / 8.0;
      dze[3]  =  ( 1.0+eps ) * ( 1.0-nn ) / 8.0;
      dze[4]  = -( 1.0+eps ) * ( 1.0+nn ) / 8.0;
      dze[5]  = -( 1.0-eps ) * ( 1.0+nn ) / 8.0;
      dze[6]  = -( 1.0-eps ) * ( 1.0-nn ) / 8.0;
      dze[7]  = -( 1.0+eps ) * ( 1.0-nn ) / 8.0;
	}
/*...................................................................*/	
}                                                                       
