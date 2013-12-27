/*********************************************
*Author: Ken Yesh
*Date: 2013-12-26
*Purpouse: Functions used in determining edges and their location 
*********************************************/


void GetHorizontalEdges(cv::Mat &in, cv::Mat &out){
	
	int ddepth = CV_64F;//Covert to Signed so we have negative and positive values
	cv::Point anchor = cv::Point( -1, -1 );
 	double delta = 0;

	//Set Data for Matrix
	float a[9]={    -1.0,	0,	1.0,	
	                -2.0,	0,	2.0,	
	                -1.0,	0,	1.0};
	
	//Creat matrix to use as Kernel 
	cv::Mat horizontal_kernel( 3, 3, CV_32F, a);
	
	filter2D(in, out, ddepth , horizontal_kernel, anchor, delta, cv::BORDER_DEFAULT );
	
}

void GetVerticalEdges(cv::Mat &in, cv::Mat &out){
	
	int ddepth = CV_64F;//Convert to signed so we have negative and positive values
	cv::Point anchor = cv::Point( -1, -1 );
 	double delta = 0;
 	
 	//Set Data for Matrix
	float b[9]={ 	1.0,	2,	1.0,	
	                0,	0,	0,	
	               -1.0,	-2,	-1.0};
	            
	//Creat matrix to use as Kernel 
	cv::Mat vertical_kernel( 3, 3, CV_32F, b);
	
	filter2D(in, out, ddepth , vertical_kernel , anchor, delta, cv::BORDER_DEFAULT );   
	               
}

void GetMagnatudeAndDirection(cv::Mat &horizontal, cv::Mat &vertical, cv::Mat &mag, cv::Mat &direction){

	double hor_cel, ver_cel;
	
	if((horizontal.cols != vertical.cols) || (horizontal.rows != vertical.row)){
	
		fprintf(stderr, "Uh Oh! not the same size");
		
	}
	
	for(int i = 0; i < horizontal.cols; i++){
	
		for(int j = 0; j < horizontal.rows; j++){
		
		hor_cel = V(horizontal, i, j, double);
		ver_cel = V(vertical, i, j, double);
		
		V(mag, i, j, double) = sqrt( hor_cel*hor_cel + ver_cel*ver_cel );
		
		V(direction, i, j, double) = atan2 (ver_cel,hor_cel);
		
		}
	
	}
		

}
