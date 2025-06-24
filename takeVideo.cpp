#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
 
int main(intargc, char* argv[])
{
    // We get the camera
    CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
    cvCaptureFromCAM( 0 );
 
    // We find out the width and height of the frame
    doublewidth = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    doubleheight = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    printf("Screen resolution\t%.0f x %.0f\n", width, height );
 
    IplImage* frame = 0;
 
    cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);
 
    intcounter = 0;
    charfilename[512];
    chardir[] = "C:\\Users\\const\\Desktop\\openCV\\cascades\\AutoNet\\right\\temp\\";
 
    while(true)
    {
        // Get the picture
        frame = cvQueryFrame( capture );
 
        // Showing
        cvShowImage("capture", frame);
 
        charclick = cvWaitKey(1);
        if(click == 27)        // ESC
        {
            break;
        }
        elseif(tolower(click) == 32)    // Space
        {
            sprintf(filename, "%s%d.jpg",dir, counter);
            printf("capture... %s\n", filename);
            cvSaveImage(filename, frame);
            counter++;
        }
    }
    // Releases resources
    cvReleaseCapture( &capture );
    cvDestroyWindow("capture");
    return 0;
}
