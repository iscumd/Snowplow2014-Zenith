#define D(x) fprintf(stderr, "%s = %g\n",  #x, (double) (x))
/**
 * @file filter2D_demo.cpp
 * @brief Sample code that shows how to implement your own linear filters by using filter2D function
 * @author OpenCV team
 */

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
#define P(mat, i, j) (mat.data + mat.step[0]*i + mat.step[1]*j)
#define V(mat, i, j, type) (*((type *) P(mat, i, j)))

/**
 * @function main
 */
int main ( int, char** argv )
{
  /// Declare variables
  
  Point anchor;
  double delta;
  int ddepth;
  int kernel_size;
  const char* window_name = "filter2D Demo";

  int c;

 Mat src, dst, dst2, in, fin;
  /// Load an image
  fin = imread( argv[1] );

  

   if( !fin.data ){ 
	printf("no image");

	return -1; }

  cvtColor( fin, src, CV_BGR2GRAY);

	float a[9]={   1.0,	2.0,	1.0,	
	                0,	0,	0,	
	                -1.0,	-2.0,	-1.0};
  Mat kernel( 3, 3, CV_32F, a);



  /// Create window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Initialize arguments for the filter
  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;
  int i;
  int j;

  int ind = 0;

         /// Update kernel size for a normalized box filter
         kernel_size = 3;
	    
         /// Apply filter
         filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
         filter2D(src, dst2, ddepth , -kernel, anchor, delta, BORDER_DEFAULT );
	for(int i=0 ; i < kernel.rows; i++){
		for (int j=0; j < kernel.cols; j++){
		
			fprintf(stderr, "%f,",  V(kernel, i, j, float));
			
		}
		printf("\n");

	}
	D(kernel.cols);
         imshow( "up side",  abs(dst*4) );
         imshow( "down side", (dst2*4) );
         c = waitKey(0);
	D(c);
         ind++;

  return 0;
}


