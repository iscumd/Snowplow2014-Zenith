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

 Mat src, dst, in;
  /// Load an image
  in = imread( argv[1] );

   if( !in.data ){ 
	printf("no image");

	return -1; }

  cvtColor( in, src, CV_BGR2GRAY);

	float a[9]={   -1.0/4.0,0,1.0/4.0,
	                -2.0/4.0,0,2.0/4.0,
	                -1.0/4.0,0,1.0/4.0};
  Mat kernel( 3, 3, CV_32F, a);



  /// Create window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Initialize arguments for the filter
  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;
  int i;
  int j;

  /// Loop - Will filter the image with different kernel sizes each 0.5 seconds
  int ind = 0;
  //for(;;)
       //{
         c = waitKey(500);
         /// Press 'ESC' to exit the program
         if( (char)c == 27 )
           //{ break; }

         /// Update kernel size for a normalized box filter
         kernel_size = 3;
	    
         //kernel = Mat( kernel_size, kernel_size, src.type(), a);
	 /*i = 0;
         j = 0;
	 *(kernel.data + kernel.step[0]*i + kernel.step[1]*j) = -1;
         i = 0;
         j = 1;
	 *(kernel.data + kernel.step[0]*i + kernel.step[1]*j) = -2;
         i = 0;
         j = 2;
	 *(kernel.data + kernel.step[0]*i + kernel.step[1]*j) = -1;

	 i = 1;
         j = 0;
	 *(kernel.data + kernel.step[0]*i + kernel.step[1]*j) = 0;
         i = 1;
         j = 1;
	 *(kernel.data + kernel.step[0]*i + kernel.step[1]*j) = 0;
         i = 1;
         j = 2;
	 *(kernel.data + kernel.step[0]*i + kernel.step[1]*j) = 0;

         i = 2;
         j = 0;
	 *(kernel.data + kernel.step[0]*i + kernel.step[1]*j) = 1;
         i = 2;
         j = 1;
	 *(kernel.data + kernel.step[0]*i + kernel.step[1]*j) = 2;
         i = 2;
         j = 2;
	 *(kernel.data + kernel.step[0]*i + kernel.step[1]*j) = 1;
*/
         /// Apply filter
         filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
	for(int i=0 ; i < kernel.rows; i++){
		for (int j=0; j < kernel.cols; j++){
		
			printf("%f,",  V(kernel, i, j, float));
			
		}
		printf("\n");

	}
         imshow( window_name, abs(dst) );
         ind++;
     //  }

  return 0;
}
