#define CV_NO_BACKWARD_COMPATIBILITY
#define SHOW(x) fprintf(stderr, "%s = %g\r\n", #x, ((double) x))        // A convenient macro to print stuff
#define PAIR(x) #x, ((double) x)
#define SHOW4(s, x1,x2,x3,x4) \
        fprintf(stderr, "%s\t %s = %g\t%s=%g\t%s=%g\t%s=%g\r\n", s,\
        PAIR(x1),PAIR(x2),PAIR(x3),PAIR(x4))    // A convenient macro to print stuff

#include "opencv/highgui.h"
#include "opencv/cv.h"
#include <stdio.h>
#include <stdlib.h>
  double alpha, beta;
 double targety, targetx;



#define REDNESS(B,G,R) (R - MyMax(G,B))
#define NOT_REDNESS(B,G,R) (-REDNESS(B,G,R))
#define TAPENESS(B,G,R) REDNESS(B,G,R)  //(MyMax(REDNESS(B,G,R), NOT_REDNESS(B,G,R) ) )

double MyMax(double a, double b)
{                               // could be a macro also
    return a > b ? a : b;       // Look up ?: trinary operator
}

IplImage *image, *Thresholded_edges, *gray1, *thresholded, *Original_edges, *dst2, *copy, *lanes;

void byebye()
{

}
void goright() {}
void goleft() {}
void gostraight() {}
float turn_sensitivity = 0.5;
double mx, my, cxx, cxy, cyy, blobsize;
double enclosing_area;
void find_blob(IplImage *img) { /* Assumes only one blob in the image*/
	int r, c;
	unsigned char *imgptr;
	mx=my=cxx=cxy=cyy=blobsize=0;

	for (r=0; r< img->height; r++) {
		imgptr = img->imageData;
		imgptr += img->widthStep * r;
		for (c=0; c<img->width; imgptr+=img->nChannels, c++) {
			if (*imgptr) { // White pixel
				double wt;
				wt = 1; // Can be adjusted
				mx += wt*c;
				my += wt*r;
				cxx += wt*c*c;
				cxy += wt*c*r;
				cyy += wt*r*r;
				blobsize +=wt;
			}
		}
	}
	if (blobsize !=0) {
		mx /=blobsize;
		my /= blobsize;
		cxx /= blobsize;
		cxy /= blobsize;
		cyy /= blobsize;
		// Now that we have averages remove the mean
		cxx -= mx*mx;
		cxy -= mx*my;
		cyy -= my*my;
		// Now cxx, cxy, cyy are covariance matrices
		enclosing_area= sqrt(0.1+cxx*cyy - cxy*cxy);

		SHOW(sqrt(cxx));
		SHOW(sqrt(cyy));
		SHOW(cxy);
		SHOW(enclosing_area);
		SHOW(blobsize);
		SHOW(blobsize/enclosing_area);

#define BOXSIZE 5
		
		for (r=my-BOXSIZE; r<my+BOXSIZE; r++) 
		if(r >=0 && r <img->height) {
			imgptr = img->imageData;
			imgptr += img->widthStep * r;
			for (c=mx-BOXSIZE; c<mx+BOXSIZE; c++) 
			if(c>=0 && c<img->width)
				imgptr[c*img->nChannels]=128;
		}
	}
}

int main(int argc, char **argv)
{

    char command[80];
    atexit(byebye);
    int lspeed, rspeed;
    int speed = 50;
    int maxspeed = 100;
    unsigned char *graypixel, *g0;

    int r, c;
    double target_c;
    int target_r;
    int npts, lspd, rspd;
    double istape, avgistape, stdevistape, maxistape, threshold, thresh;
    double S0left, S1left, S2left, b1left, b2left, alphaleft, betaleft;
    double S0right, S1right, S2right, b1right, b2right, alpharight,
        betaright;
    int dr, dc;
    int cleft, cright;
    CvScalar mean, std_dev;


    char *filename = argc == 2 ? argv[1] : (char *) "1m.png";
    if ((image = cvLoadImage(filename, 1)) == 0) {
        system("Pause");
        return -1;
    }
    if (Thresholded_edges == NULL)
        Thresholded_edges =
            cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_8U, 1);

    if (gray1 == NULL)
        gray1 =
            cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_8U, 1);
    if (Original_edges == NULL)
        Original_edges =
            cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_8U, 1);

    if (thresholded == NULL)
        thresholded =
            cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_8U, 1);
    if (dst2 == NULL)
        dst2 =
            cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_8U, 1);


    if (copy == NULL)
        copy =
            cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_8U, 3);


    cvCvtColor(image, gray1, CV_BGR2GRAY);


    cvAvgSdv(gray1, &mean, &std_dev, NULL);
    thresh = mean.val[0] - 3*std_dev.val[0];  // Just channel 0
    SHOW(thresh);
    if (thresh < 10) thresh=10;
    SHOW(thresh);
    cvThreshold(gray1, thresholded, thresh, 255, CV_THRESH_BINARY_INV);


    cvCanny(gray1, Original_edges, 20, 100, 3);
    cvCanny(thresholded, Thresholded_edges, 20, 100, 3);
    find_blob(thresholded);
    cvCopy(image, copy, NULL);

    cvShowImage("gray1", gray1);
    cvShowImage("Original_edges", Original_edges);
    cvShowImage("thresholded", thresholded);
    cvShowImage("Thresholded_edges", Thresholded_edges);
    cvShowImage("original", image);
    cvShowImage("Marked up", copy);
    //  cvShowImage("Dst2", dst2);



    cvWaitKey(0);
    cvReleaseImage(&image);
    cvReleaseImage(&gray1);
    cvReleaseImage(&Original_edges);
    cvReleaseImage(&thresholded);
    cvReleaseImage(&dst2);
    return 0;
}

