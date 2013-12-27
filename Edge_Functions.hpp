/*********************************************
*Author: Ken Yesh
*Date: 2013-12-26
*Purpouse: Functions used in determining edges and their location 
*********************************************/


void GetHorizontalEdges(cv::Mat &in, cv::Mat &out){
	
	cv::Mat temp;
	
	int ddepth = CV_16S;//Covert to Signed so we have negative and positive values
	cv::Point anchor = cv::Point( -1, -1 );
 	double delta = 0;

	//Set Data for Matrix
	float a[9]={    -1.0,	0,	1.0,	
	                -2.0,	0,	2.0,	
	                -1.0,	0,	1.0};
	
	//Creat matrix to use as Kernel 
	cv::Mat horizontal_kernel( 3, 3, CV_32F, a);
	
	filter2D(in, temp, ddepth , horizontal_kernel, anchor, delta, cv::BORDER_DEFAULT );
	
	temp.convertTo(out, CV_64F);//Why dosen't it have negative values and why is it creating noise?
					// See http://stackoverflow.com/questions/13484475/what-are-the-upper-and-lower-limits-and-types-of-pixel-values-in-opencv
}

void GetVerticalEdges(cv::Mat &in, cv::Mat &out){
	
	cv::Mat temp;
	
	int ddepth = CV_16S;//Convert to signed so we have negative and positive values
	cv::Point anchor = cv::Point( -1, -1 );
 	double delta = 0;
 	
 	//Set Data for Matrix
	float b[9]={ 	1.0,	2,	1.0,	
	                0,	0,	0,	
	               -1.0,	-2,	-1.0};
	            
	//Creat matrix to use as Kernel 
	cv::Mat vertical_kernel( 3, 3, CV_32F, b);
	
	filter2D(in, temp, ddepth , vertical_kernel , anchor, delta, cv::BORDER_DEFAULT );   
	
	temp.convertTo(out, CV_64F, 1.0/32767);//Why dosen't it have negative values and why is it creating noise?
					// See http://stackoverflow.com/questions/13484475/what-are-the-upper-and-lower-limits-and-types-of-pixel-values-in-opencv
	               
}
