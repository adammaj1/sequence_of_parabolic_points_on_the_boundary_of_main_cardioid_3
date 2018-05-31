/*

  Adam Majewski
  c console progam
  
  
  gcc s.c =lm -Wall
  ./a.out
  time ./a.out
  
  
  
============ git ==========  
  cd existing_folder
git init
git remote add origin git@gitlab.com:adammajewski/sequence_of_parabolic_points_on_the_boundary_of_main_cardioid_3.git
git add .
git commit -m "Initial commit"
git push -u origin master
  
*/



#include <stdio.h>
#include <stdlib.h> // malloc
#include <math.h> // M_PI; needs -lm also 
#include <complex.h>
#include <string.h> // strncat





// ------------ global variables, see also give_t  ==================================================

double i_Max ; // = iPeriodChild*1.0; see setup 
unsigned long long int i_Max_multiplier =  10000; 






 double twopi = 2.0*M_PI;
 
 
// virtual 2D array and integer ( screen) coordinate
// Indexes of array starts from 0 not 1 
//unsigned int ix, iy; // var
unsigned int ixMin = 0; // Indexes of array starts from 0 not 1
unsigned int ixMax ; //
unsigned int iWidth = 1000 ; // horizontal dimension of array
 
unsigned int iyMin = 0; // Indexes of array starts from 0 not 1
unsigned int iyMax ; //
unsigned int iHeight = 1000; //  odd number !!!!!! = (iyMax -iyMin + 1) = iyAboveAxisLength + iyBelowAxisLength +1
// The size of array has to be a positive constant integer 
unsigned int iSize ; // = iWidth*iHeight; 




double AspectRatio; // width : height  https://en.wikipedia.org/wiki/Aspect_ratio_(image)

/* world ( double) coordinate = dynamic plane */
// center and radius : https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#radius
complex double center = -0.250000000000000  +0.433012701892219*I; // alfa fixed point
double radius = 0.5; 

// corners: https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#Corners
double ZxMin ;
double ZxMax;
double ZyMin;
double ZyMax;
double PixelWidth; // =(ZxMax-ZxMin)/iXmax;
double PixelHeight; // =(ZyMax-ZyMin)/iYmax;


complex double c; 

 
 
// memmory 1D array 
unsigned char *image; 


// parabolic point = root is a common points between 2 componnets of Mandelbrot set : parent and child
unsigned long long int iPeriodChild; // = q = denominator( Internal angle t = p/q)



// ----------------------  functions ===========================================


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
		// global variable 
		iPeriodChild = q; 
		
	
	
	}
	 
	t = (double)p/q; // compute floating point value 
	printf( "for n = %2d  p/q = %18Ld / %18Ld  \tt =  %.16f\t",n, p, q, t); 
	
	// !!!! global variable setup for each n 
	iPeriodChild = q; 
	i_Max = iPeriodChild*i_Max_multiplier;
	// !!!!!
	
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



// arrray functions ===============================================

/* gives position of 2D point (iX,iY) in 1D array  ; uses also global variable iWidth */
unsigned int Give_i(unsigned int ix, unsigned int iy)
{ return ix + iy*iWidth; }



// plots raster point (ix,iy) 
int PlotPoint(complex double z, unsigned char A[])
{
  	// indices of virtual 2D array
  	unsigned int ix;
  	unsigned int iy;
	unsigned i; /* index of memory dynamic 1D array */
	
	double Zx = creal(z);
	double Zy = cimag(z);
  
  
	//compute integer coordinate  
	if ( Zx<=ZxMax && Zx>=ZxMin && Zy>=ZyMin && Zy<=ZyMax ) // check bounds, comment it if you are sure
	// for n =  9  p/q =          333333333 /         1000000000  	t =  0.3333333330000000		c = (-0.1249999981862006 ; +0.6495190528383290) Naruszenie ochrony pamięci !!! error
	// point z =  (-0.4365786152835205 ; -0.1839796132996155) is out of drawing rectangle 
	//  error from DrawCriticalOrbit for i = 999999998 

      		{ix = (int)round((Zx-ZxMin)/PixelWidth);
      		iy = (int)round((ZyMax-Zy)/PixelHeight); // reverse y axis
  		i = Give_i(ix,iy); /* compute index of 1D array from indices of 2D array */
  		A[i] = 255;
  		return 0;}
  		
  	printf(" error from  PlotPoint function : point z =  (%+.16f ; %+.16f) is out of drawing rectangle \n",creal(z), cimag(z));
  		
  	return 1;
}


// fill array 
// uses global var :  ...
// scanning complex plane 
int ClearArray(unsigned char A[] )
{
  
  	unsigned int i; // index of 1D array

  	// every pixel of the image is black
	for(i= 0; i<=iSize; ++i) A[i] = 0; 
			     	
	return 0;
}

/*
 save data array to pgm file 
SaveArray2PGMFile(data0 , iterMax+9, "marked first quadrant should be up and right", 100, 100); // save array (image) to pgm filename
*/

int SaveArray2PGMFile( unsigned char A[], int n, unsigned long long int  i_Max_multiplier, char* comment, int iWidth, int iHeight, int iSize )
{
  
  FILE * fp;
  const unsigned int MaxColorComponentValue=255; /* color component is coded from 0 to 255 ;  it is 8 bit color file */
  char name [100]; /* name of file */
  snprintf(name, sizeof name, "%d_%Ld", n, i_Max_multiplier); /*  */
  char *filename =strncat(name,".pgm", 4);
  
  
  
  /* save image to the pgm file  */      
  fp= fopen(filename,"wb"); /*create new file,give it a name and open it in binary mode  */
  fprintf(fp,"P5\n # %s\n %u %u\n %u\n", comment, iWidth, iHeight, MaxColorComponentValue);  /*write header to the file*/
  fwrite(A,iSize,1,fp);  /*write image data bytes to the file in one step */
  
  //
  printf("File %s saved. ", filename);
  if (comment == NULL)  printf ("empty comment \n");
                   else printf (" comment = %s \n", comment); 
  fclose(fp);

  return 0;
}


int DrawCriticalOrbit(int n, unsigned char A[]){

	double i;
	// 18,446,744,073,709,551,615
	// 10 000 000 000
	int error; // true =  nonzero number
	
	
	complex double z=0.0; // critical point 
	
	PlotPoint(z, A);
	// iterate
	for(i=0; i < i_Max; i=i+1.0 ){
		z = z*z + c;
		error = PlotPoint(z, A);
		// stop computing in case of error, save image and do not crash the whole program
		if (error) {printf(" error from DrawCriticalOrbit for i = %.0f \n", i ); return 1;}
	}

	return 0;
}



/* draw to the array and save it to pgm image */
int MakeImage(int n){

	double t;
	
	
	
	t = Give_t(n);
	c = Give_c(t);

	ClearArray(image);
	// draw
	
	DrawCriticalOrbit( n, image);
	
	SaveArray2PGMFile( image, n, i_Max_multiplier, " ",  iWidth, iHeight, iSize );
	return 0;
}










// https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#radius
int SetPlane(complex double center, double radius){
	ZxMin = creal(center) - AspectRatio*radius;
	ZxMax = creal(center) + AspectRatio*radius;;
	ZyMin = cimag(center) - radius;
	ZyMax = cimag(center) + radius;
	


	return 0;


}


// 
int setup(){



		
	// plane 
	iSize = iWidth*iHeight; // size = number of points in array 
	iyMax = iHeight - 1 ; // Indexes of array starts from 0 not 1 so the highest elements of an array is = array_name[size-1].
  	ixMax = iWidth - 1;
  	AspectRatio = (double) iWidth/iHeight;// width : height  https://en.wikipedia.org/wiki/Aspect_ratio_(image)
  	SetPlane( center, radius);
	PixelWidth = (ZxMax-ZxMin)/ixMax;
	PixelHeight = (ZyMax-ZyMin)/iyMax;
	
	
	/* create dynamic 1D arrays for colors ( shades of gray ) */
  	image = malloc( iSize * sizeof(unsigned char) );
  	if (image == NULL )
    	{
      		fprintf(stderr,"Could not allocate memory\n");
      		return 1;
    	}
  	else fprintf(stderr,"memory is OK \n");

	// see also Give_t  for rest of setup
	
	
	printf(" i_Max_multiplier = %Ld \n", i_Max_multiplier);
	return 0;
}
   


/* -----------------------------------------  main   -------------------------------------------------------------*/
int main()
{

	int n;
	
	setup();
		
	for (n = 1; n < 10; n++)
		MakeImage( n);
	 	
  

 
  return 0;
}
