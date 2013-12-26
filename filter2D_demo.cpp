#define D(x) fprintf(stderr, "%s = %g\n",  #x, (double) (x))
/**
 * @file filter2D_demo.cpp
 * @brief Sample code that shows how to implement your own linear filters by using filter2D function
 * @author OpenCV team
 *
 * Modfied by: Ken Yesh and others
 */

//OpenCV libraries
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

//Standar Libraries
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//User Made Libraries
#include "Edge_Functions.hpp" //Author: Ken Yesh


using namespace cv;
#define P(mat, i, j) (mat.data + mat.step[0]*i + mat.step[1]*j)
#define V(mat, i, j, type) (*((type *) P(mat, i, j)))

/**
 * @function main
 */
int main ( int, char** argv )
{
  /// Declare variables
  
 
  const char* window_name = "filter2D Demo";

  int c;

 Mat src, dst, dst2, fin;
  /// Load an image
  fin = imread( argv[1] );

  

   if( !fin.data ){ 
	printf("no image");

	return -1; }

  cvtColor( fin, src, CV_BGR2GRAY);

  /// Create window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );
	    
         /// Apply filter
         GetHorizontalEdges(src, dst);//In Edge Functions
         GetVerticalEdges( src, dst2);
	
         imshow( "Horziontal Multiplied By 8",  (dst*8) );
         imshow( "Vertical Multiplied By 8", (dst2*8) );
         c = waitKey(0);

  return 0;
}
