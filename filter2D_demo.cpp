#define D(x) fprintf(stderr, "%s = %g\n",  #x, (double) (x))
#define P(mat, i, j) (mat.data + mat.step[0]*i + mat.step[1]*j)
#define V(mat, i, j, type) (*((type *) P(mat, i, j)))
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


/**
 * @function main
 */
int main ( int, char** argv )
{
  /// Declare variables
  
 
  const char* window_name = "filter2D Demo";

  int c;

 Mat src, hor, ver, fin;
 Mat * mag;
 Mat * dir;
  /// Load an image
  fin = imread( argv[1] );

  

   if( !fin.data ){ 
	printf("no image");

	return -1; }

  cvtColor( fin, src, CV_BGR2GRAY);

  /// Create window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );
	    
         /// Apply filter
         GetHorizontalEdges(src, hor);//In Edge Functions
         GetVerticalEdges( src, ver);
	
	mag = new cv::Mat(hor.rows, hor.cols, CV_64F);
	dir = new cv::Mat(hor.rows, hor.cols, CV_64F);
	
	GetMagnatudeAndDirection(hor, ver, *mag, *dir);
	
	//imshow() expects values to be between 0 and 1 so I needed to properly shift it.
         imshow( "Horziontal Multiplied By 8",  ((hor/32767)*8) + .5);
         imshow( "Vertical Multiplied By 8", ((ver/32768)*8) + .5);
         imshow( "Magnatude Multiplied By 8", (((*mag)/32768)*8) + .5);
         
         	//need to unallocate and reallocate memory in loop
		 //destroy mag;
		 //destroy dir;
		 
         c = waitKey(0);

  return 0;
}
