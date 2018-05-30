/*

  Adam Majewski
  c console progam
  
  
  gcc s.c =lm -Wall
  ./a.out
  
  
  
============ git ==========  
  cd existing_folder
git init
git remote add origin git@gitlab.com:adammajewski/sequence_of_parabolic_points_on_the_boundary_of_main_cardioid_3.git
git add .
git commit -m "Initial commit"
git push -u origin master
  
*/



#include <stdio.h>
#include <math.h> // M_PI; needs -lm also 
#include <complex.h>


 double twopi = 2.0*M_PI;


/*

https://en.wikibooks.org/wiki/Fractals/Mathematics/sequences#sequence_of_parabolic_points_on_the_boundary_of_main_cardioid

*/

double Give_t(int nMax){

	double t = 0.0; // = p/q 
	// ratio
	long long  int p = 3; // numerator of t
	long long int q = 10; // denominator of t
	
	int n = 1;
	
	
	// bounds check 
	if (nMax < 1) {printf(" error nMax < 1 \n"); return t;}
	if (nMax > 20) {printf(" error nMax > 20 \n"); return t;}
	
	while ( n< nMax){
		
		p = p + 3*q;
		q = q*10;
		n++;
	
	
	}
	 
	t = (double)p/q; // compute floating point value 
	printf( "for n = %2d  p/q = %18Ld / %18Ld  \tt =  %.16f\t",n, p, q, t); 
	
	
	
	
	return t; 




}



/* computes c on the boundary of Main cardioid of Mandelbrot set */
complex double Give_c(  double InternalAngleInTurns )
{
  
  complex double w;
  complex double c; 
  
  
  double InternalRadius = 1.0; // only boundary points
  
  double t = InternalAngleInTurns *twopi; // from turns to radians
  w = InternalRadius*cexp(I*t); // point of the unit circle 
  
  // main cardioid
  c = w/2 - w*w/4;
  printf("\tc = (%+.16f ; %+.16f)\n",creal(c), cimag(c)); 

  return c;
}





   


/* -----------------------------------------  main   -------------------------------------------------------------*/
int main()
{

	int n;
	double t; 
		
	for (n = 1; n < 17; n++){
		t = Give_t(n);
		Give_c(t);
		
		}
		
	 	
  

 
  return 0;
}
