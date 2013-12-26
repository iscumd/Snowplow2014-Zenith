/*********************************************
*Author: Ken Yesh
*Date: 2013-12-26
*Purpouse: Functions used in determining edges and their location 
*********************************************/


void GetHorizontalEdges(cv::Mat in, cv::Mat out){
	
	int ddepth = CV_16S;
	cv::Point anchor = cv::Point( -1, -1 );
 	double delta = 0;

	float a[9]={    -1.0,	0,	1.0,	
	                -2.0,	0,	2.0,	
	                -1.0,	0,	1.0};
	                
	cv::Mat horizontal_kernel( 3, 3, CV_32F, a);
	
	filter2D(in, out, ddepth , horizontal_kernel, anchor, delta, cv::BORDER_DEFAULT );
}

void GetVerticalEdges(cv::Mat in, cv::Mat out){
	
	int ddepth = CV_16S;
	cv::Point anchor = cv::Point( -1, -1 );
 	double delta = 0;
 	
 	float b[9]={ 	1.0,	2,	1.0,	
	                0,	0,	0,	
	               -1.0,	-2,	-1.0};
	            
	cv::Mat vertical_kernel( 3, 3, CV_32F, b);
	
	filter2D(in, out, ddepth , vertical_kernel , anchor, delta, cv::BORDER_DEFAULT );   
	               
}
