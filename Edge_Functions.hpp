/*********************************************
*Author: Ken Yesh
*Date: 2013-12-26
*Purpouse: Functions used in determining edges and their location 
*********************************************/

Void GetHorizontalEdges(Mat in, Mat out){
	
	ddepth = CV_16S;
	anchor = Point( -1, -1 );
 	delta = 0;

	float a[9]={    -1.0,	0,	1.0,	
	                -2.0,	0,	2.0,	
	                -1.0,	0,	1.0};
	                
	Mat horizontal_kernel( 3, 3, CV_32F, a);
	
	filter2D(in, out, ddepth , horizontal_kernel, anchor, delta, BORDER_DEFAULT );
}

Void GetVerticalEdges(Mat in, Mat out){
	
	ddepth = CV_16S;
	anchor = Point( -1, -1 );
 	delta = 0;
 	
 	float b[9]={ 	1.0,	2,	1.0,	
	                0,	0,	0,	
	               -1.0,	-2,	-1.0};
	            
	Mat vertical_kernel( 3, 3, CV_32F, b);
	
	filter2D(in, out, ddepth , vertical_kernel , anchor, delta, BORDER_DEFAULT );   
	               
}
