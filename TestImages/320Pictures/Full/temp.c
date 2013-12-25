#define METHOD CV_HOUGH_PROBABILISTIC
#define LEFTLANE ((dx*dy<0) && (mx < edge->width/2)&& abs(dy)>abs(dx))
#define RIGHTLANE ((dx*dy>0) && (mx > edge->width/2)&& abs(dy)>abs(dx))

#define SUM0(N) (N)
#define SUM1(N) ((N)*((N)+1)/2)
#define SUM2(N) ((N)*((N)+1)*(2*((N)+1)+1)/6)
 void hough(IplImage * edge, IplImage * output_image)
{
    static CvMemStorage *storage;
    double dx, dy, mx, my, ldx, ldy, rdx = 0, rdy = 0;
    double Ls1, Lsy, Lsyy, Lsx, Lsxy, Lalpha, Lbeta;
    double Rs1, Rsy, Rsyy, Rsx, Rsxy, Ralpha, Rbeta;
    double m, intercept, det;
    double x1, y0, y1;
    // From demo code on hough transform
    // No clue what this all means
    CvSeq *lines = 0;
    int i, l = 0, r = 0;
    CvPoint top, bottom;

    if (storage == NULL)
        storage = cvCreateMemStorage(0);
    lines = cvHoughLines2(edge, storage, METHOD, 1, 3.1416 / 180.0, edge->height / 10, edge->height / 10, edge->height / 4);    // Check these numbers
    SHOW(lines->total);
    Ls1 = Lsy = Lsyy = Lsx = Lsxy = 0;
    Rs1 = Rsy = Rsyy = Rsx = Rsxy = 0;

    for (i = 0; i < lines->total; i++) {
        CvPoint *line = (CvPoint *) cvGetSeqElem(lines, i);
        dx = line[1].x - line[0].x;
        dy = line[1].y - line[0].y;
        mx = (line[1].x + line[0].x) / 2;
        my = (line[1].y + line[0].y) / 2;
        if (LEFTLANE) {

            cvLine(output_image, line[0], line[1], CV_RGB(0, 0, 255), 6,
                   CV_AA, 0);
            SHOW4("Left:", dx, dy, mx, my);
            m = dx / dy;
            if (line[0].y < line[1].y) {
                y1 = line[1].y;
                y0 = line[0].y;
                x1 = line[1].x;
            } else {
                y1 = line[0].y;
                y0 = line[1].y;
                x1 = line[0].x;
            }
            y0 = y0 - 1;
            Ls1 += y1 - y0;
            Lsy += SUM1(y1) - SUM1(y0);
            Lsyy += SUM2(y1) - SUM2(y0);

            intercept = x1 - m * y1;
            Lsx += intercept * (y1 - y0) + m * (SUM1(y1) - SUM1(y0));
            Lsxy +=
                intercept * (SUM1(y1) - SUM1(y0)) + m * (SUM2(y1) -
                                                         SUM2(y0));

        } else if (RIGHTLANE) {
            cvLine(output_image, line[0], line[1], CV_RGB(255, 0, 0), 6,
                   CV_AA, 0);
            SHOW4("Right:", dx, dy, mx, my);
            m = dx / dy;
            if (line[0].y < line[1].y) {
                y1 = line[1].y;
                y0 = line[0].y;
                x1 = line[1].x;
            } else {
                y1 = line[0].y;
                y0 = line[1].y;
                x1 = line[0].x;
            }
            y0 = y0 - 1;
            Rs1 += y1 - y0;
            Rsy += SUM1(y1) - SUM1(y0);
            Rsyy += SUM2(y1) - SUM2(y0);

            intercept = x1 - m * y1;
            Rsx += intercept * (y1 - y0) + m * (SUM1(y1) - SUM1(y0));
            Rsxy +=
                intercept * (SUM1(y1) - SUM1(y0)) + m * (SUM2(y1) -
                                                         SUM2(y0));


        } else
            SHOW4("Ignored:", dx, dy, mx, my);
    }
    /*     if (fabs(dy)>fabs(dx)) {
       if(dy*dx >0) {
       if (mx > edge->width/2)  {
       cvLine(output_image, line[0], line[1], CV_RGB(0, 0, 255), 6, CV_AA, 0);

       }
       else 
       cvLine(output_image, line[0], line[1], CV_RGB(0, 0, 255), 1, CV_AA, 0);
       }
       else {
       if (mx < edge->width/2) {
       cvLine(output_image, line[0], line[1], CV_RGB(255, 0, 0), 6, CV_AA, 0);

       }
       else
       cvLine(output_image, line[0], line[1], CV_RGB(255, 0, 0), 1, CV_AA, 0);
       }
       }
       else
       cvLine(output_image, line[0], line[1], CV_RGB(0, 255, 255), 1, CV_AA, 0);
       }
     */
    det = Lsyy * Ls1 - Lsy * Lsy + 0.000001;    // looks like y^2
    Lalpha = (Lsxy * Ls1 - Lsx * Lsy) / det;    // Looks like x y /y^2
    Lbeta = (Lsx * Lsyy - Lsy * Lsxy) / det;    // Looks like x y^2/y^2
    top.y = 0;
    top.x = Lbeta;
    bottom.y = output_image->height - 1;
    bottom.x = Lbeta + Lalpha * bottom.y;
    cvLine(output_image, top, bottom, CV_RGB(255, 255, 255), 1, CV_AA, 0);

    det = Rsyy * Rs1 - Rsy * Rsy + 0.000001;    // looks like y^2
    Ralpha = (Rsxy * Rs1 - Rsx * Rsy) / det;    // Rooks like x y /y^2
    Rbeta = (Rsx * Rsyy - Rsy * Rsxy) / det;    // Rooks like x y^2/y^2
    top.y = 0;
    top.x = Rbeta;
    bottom.y = output_image->height - 1;
    bottom.x = Rbeta + Ralpha * bottom.y;
    cvLine(output_image, top, bottom, CV_RGB(255, 255, 255), 1, CV_AA, 0);


    alpha = (Lalpha + Ralpha) / 2;
    beta = (Lbeta + Rbeta) / 2;
    top.y = 0;
    top.x = beta;
    bottom.y = output_image->height - 1;
    bottom.x = beta + alpha * bottom.y;
    cvLine(output_image, top, bottom, CV_RGB(255, 255, 255), 1, CV_AA, 0);
    
    targety = 2*output_image->height/3;
    targetx = alpha*targety+beta;
    cvCircle(output_image, cvPoint(targetx,targety), 10, CV_RGB(255,255,255),1, CV_AA,0);
}
