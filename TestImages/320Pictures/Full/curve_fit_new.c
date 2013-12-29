#define CV_NO_BACKWARD_COMPATIBILITY
#define SHOW(x) fprintf(stderr, "%s = %g\r\n", #x, ((double) x))        // A convenient macro to print stuff
#define PAIR(x) #x, ((double) x)
#define SHOW4(s, x1,x2,x3,x4) \
        fprintf(stderr, "%s\t %s = %g\t%s=%g\t%s=%g\t%s=%g\r\n", s,\
        PAIR(x1),PAIR(x2),PAIR(x3),PAIR(x4))    // A convenient macro to print stuff

#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include "nnlib.c"
#include "roboteq.c"
#include "joystick.c"
#include "joystick.h"
  double alpha, beta;
 double targety, targetx;


#include "temp.c"

#define REDNESS(B,G,R) (R - MyMax(G,B))
#define NOT_REDNESS(B,G,R) (-REDNESS(B,G,R))
#define TAPENESS(B,G,R) REDNESS(B,G,R)  //(MyMax(REDNESS(B,G,R), NOT_REDNESS(B,G,R) ) )

double MyMax(double a, double b)
{                               // could be a macro also
    return a > b ? a : b;       // Look up ?: trinary operator
}

IplImage *image, *gray, *gray1, *gray2, *dst1, *dst2, *copy, *lanes;
HANDLE controller;              // Windows keeps track of resources using HANDLES

void byebye()
{

}
void goright() {}
void goleft() {}
void gostraight() {}
float turn_sensitivity = 0.5;
float center_bias = 0.75;       // Distance from the left edge to where we want to go
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


    //CvCapture* capture = 0; // variable used for camera feed
    // capture = cvCaptureFromCAM(0); // find the camera, not the webcam
    //printf ("im here4\r\n");

    //if( (image = cvQueryFrame(capture)) == 0 ) // load an image to process, the image is called "image"
    //{
    //        system("Pause");
    //        return -1;
    //  }
    char *filename = argc == 2 ? argv[1] : (char *) "lane3.jpg";
    if ((image = cvLoadImage(filename, 1)) == 0) {
        system("Pause");
        return -1;
    }
    if (gray == NULL)
        gray =
            cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_8U, 1);

    if (gray1 == NULL)
        gray1 =
            cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_8U, 1);
    if (dst1 == NULL)
        dst1 =
            cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_8U, 1);

    if (gray2 == NULL)
        gray2 =
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
    thresh = mean.val[0] - std_dev.val[0] / 3;  // Just channel 0
    //SHOW(thresh);
    cvThreshold(gray1, gray2, thresh, 255, CV_THRESH_BINARY);


    cvCanny(gray1, dst1, 20, 100, 3);
    cvCanny(gray2, gray, 20, 100, 3);
    cvCopy(image, copy, NULL);
    hough(gray, copy);

    cvShowImage("gray1", gray1);
    cvShowImage("Dst1", dst1);
    cvShowImage("gray2", gray2);
    cvShowImage("gray", gray);
    cvShowImage("original", image);
    cvShowImage("Marked up", copy);
    //  cvShowImage("Dst2", dst2);


    if (targetx > image->width*0.6) goright();
    else if(targetx < image->width*0.4) goleft();
    else gostraight();

    cvWaitKey(0);
    cvReleaseImage(&image);
    cvReleaseImage(&gray1);
    cvReleaseImage(&dst1);
    cvReleaseImage(&gray2);
    cvReleaseImage(&dst2);
    return 0;
}

