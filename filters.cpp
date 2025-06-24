#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

#include <conio.h>
#include <windows.h>
#include "serial.h"
#define COM_PORT "COM4"
#define BUF_SIZE 256

// Mat objects
Mat imgOriginal;
Mat imgHSV;
Mat imgThresholded;
Mat imgGray;

Mat roi_frame;
Mat lower_red_hue_range;
Mat upper_red_hue_range;

// Vectors Rect
vector<Rect>leftRect;
vector<Rect>rightRect;
vector<Rect>roadUpRect;
vector<Rect>stopRect;
vector<Rect>straightRect;
vector<Rect>straightOrRightRect;

// Cascade objects
CascadeClassifier left;
CascadeClassifier right;
CascadeClassifierroadUp;
CascadeClassifier stop;
CascadeClassifier straight;
CascadeClassifierstraightOrRight;

int objectSize = 80;       // Minimal size of detect object

int trafficLightSize = 40;  // Minimal size of traffic light
double roiSize = 1.5;       // Coefficient for size of radius of ROI

void draving(vector<Rect>myRect, Mat image);
unsigned int heirarchyCount(vector<Vec4i>someVector);
int approxCount(vector<vector<Point>>someVector);

///* MAIN *///
int main()
{
    Serial com((char*)COM_PORT);

    // clear buffer
    char buf[BUF_SIZE];
for(int i = 0; i< BUF_SIZE; i++)
    {
buf[i] = '\0';
    }

    // Capture video
VideoCapturecapture(0);

    // We find out the width and height of the frame
    int width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

printf("Screen resolution\t%d x %d\n", width, height );

    // Load cascades (.xml file)
left.load("haar\\left_v3.xml");
right.load("haar\\right_v3.xml");
roadUp.load("haar\\roadUp_v4.xml");
stop.load("haar\\stop_v3.xml");
straight.load("haar\\straight_v3.xml");
straightOrRight.load("haar\\straightOrRight_v3.xml");

buf[0] = 'e';
com.WriteData(buf,BUF_SIZE-1);

    while (1)
    {
capture.read(imgOriginal);

        // Some fix ...
cvtColor( imgOriginal, imgGray, CV_BGR2GRAY );
equalizeHist( imgGray, imgGray );

        // Left sign found
	left.detectMultiScale( imgGray, leftRect, 1.1, 2,
	                          0|CV_HAAR_SCALE_IMAGE, Size(objectSize, ob-jectSize) );
	    if (!leftRect.empty())
	    {
	printf("A left found\n");
	draving(leftRect, imgOriginal);
	
            // A
buf[0] = 'a';
com.WriteData(buf,BUF_SIZE-1);
	    }

        // Right sign found
right.detectMultiScale( imgGray, rightRect, 1.1, 2,
                           0|CV_HAAR_SCALE_IMAGE, Size(objectSize, objectSize) );
	if (!rightRect.empty())
	    {
	printf("A right found\n");
	draving(rightRect, imgOriginal);
	
            //D
buf[0] = 'd';
com.WriteData(buf,BUF_SIZE-1);
	    }

        // RoadUp sign found
roadUp.detectMultiScale( imgGray, roadUpRect, 1.1, 2,
                            0|CV_HAAR_SCALE_IMAGE, Size(objectSize, object-Size) );
	if (!roadUpRect.empty())
	    {
	printf("A roadUp found\n");
	draving(roadUpRect, imgOriginal);
	
            // S
buf[0] = 's';
com.WriteData(buf,BUF_SIZE-1);
	    }

        // Stop sign found
stop.detectMultiScale( imgGray, stopRect, 1.1, 2,
                          0|CV_HAAR_SCALE_IMAGE, Size(120, 120) );
	    if (!stopRect.empty())
	    {
	printf("A stop found\n");
	draving(stopRect, imgOriginal);
	
            //H
buf[0] = 'h';
com.WriteData(buf,BUF_SIZE-1);
	    }

        // Straight sign found
straight.detectMultiScale( imgGray, straightRect, 1.1, 2,
                              0|CV_HAAR_SCALE_IMAGE, Size(objectSize, object-Size) );
	    if (!straightRect.empty())
	    {
	printf("A straight found\n");
	draving(straightRect, imgOriginal);
	
            //W
buf[0] = 'w';
com.WriteData(buf,BUF_SIZE-1);
	    }

	    // Straight or right sign found
straightOrRight.detectMultiScale( imgGray, straightOrRightRect, 1.1, 2,
                                     0|CV_HAAR_SCALE_IMAGE, Size(objectSize, objectSize) );
	    if (!straightOrRightRect.empty())
	    {
	printf("A straightOrRight found\n");
	draving(straightOrRightRect, imgOriginal);

	        // D
buf[0] = 'd';
com.WriteData(buf,BUF_SIZE-1);
	    }

	    // Detected traffic light
medianBlur(imgOriginal, imgHSV, 3);

cvtColor(imgHSV, imgHSV, CV_BGR2HSV);

inRange(imgHSV, Scalar(0, 100, 100), Scalar(10, 255, 255), low-er_red_hue_range);
inRange(imgHSV, Scalar(160, 100, 100), Scalar(179, 255, 255), up-per_red_hue_range);

addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, imgThresholded);

morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN,
getStructuringElement(MORPH_RECT, Size(10, 10)));

morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE,
getStructuringElement(MORPH_RECT, Size(10, 10)));

GaussianBlur(imgThresholded, imgThresholded, Size(9, 9), 2, 2);

        // ROI version
        vector<Vec3f> circles;

HoughCircles(imgThresholded, circles, CV_HOUGH_GRADIENT, 1,
imgThresholded.rows/8, 100, 20, trafficLightSize, 0);

        if(circles.size() != 0)
        {
for(size_ti = 0; i<circles.size(); i++)
            {
                int x = round(circles[i][0]) - roiSize * round(circles[i][2]);
                int y = round(circles[i][1]) - roiSize * round(circles[i][2]);
                int wAndH = 2 * roiSize * round(circles[i][2]);

                if (x > 0 && y > 0 &&wAndH> 0 &&
                    (x + wAndH) < width && (y + wAndH) < height)
                {
RectROI(x, y, wAndH, wAndH);

roi_frame = imgThresholded(ROI);

                    vector<vector<Point>> contours;
                    vector<Vec4i>heirarchy;

findContours( roi_frame.clone(), contours,
heirarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

                    // Detect circle
                    if (approxCount(contours) == 8)
                    {
                        // How many dots inside the circle
                        if (heirarchyCount(heirarchy) == (heirarchy.size()) * 4)
                        {
printf("A red color of traffic light find\n");

                            //H
buf[0] = 'h';
com.WriteData(buf,BUF_SIZE-1);

for(size_ti = 0; i<circles.size(); i++)
                            {
                                Point dot1(round(circles[i][0]) - round(circles[i][2]),
                                            round(circles[i][1]) - round(circles[i][2]));

                                Point dot2(round(circles[i][0]) + round(circles[i][2]),
                                            round(circles[i][1]) + round(circles[i][2]));

rectangle( imgOriginal, dot1, dot2, Scalar( 255, 255, 0 ), +2, 8 );
                            }
                        }
                    }
                }
            }
        }


imshow("Original", imgOriginal);

        if (waitKey(1) == 27)
            break;
    }

    return 0;
}


// The function that draws a square
void draving(vector<Rect>myRect, Mat image)
{
for(unsigned int i = 0; i<myRect.size(); i++ )
    {
        Point dot1(myRect[i].x, myRect[i].y);
        Point dot2( myRect[i].x + myRect[i].width, myRect[i].y + myRect[i].height);
rectangle( image, dot1, dot2, Scalar( 255, 255, 0 ), +2, 8 );
    }
}

// Counts corners
unsigned int heirarchyCount(vector<Vec4i>someVector)
{
    int counter = 0;
for( size_ti = 0; i<someVector.size(); i++ )
    {
        for ( size_t j = 0; j < 4; j++)
        {
            if (someVector[i][j] == -1)
            counter++;
        }
    }
    return counter;
}

// How many dots inside the circle
int approxCount(vector<vector<Point>>someVector)
{
    vector<Point>approx;

    for (size_ti = 0; i<someVector.size(); i++)
    {
approxPolyDP(Mat(someVector[i]), approx,
arcLength(Mat(someVector[i]), true)*0.02, true);
}
return approx.size();
}