/* 
   Modificar uma imagem passada por parametro
   e gravar uma nova imagem processada no disco
*/

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include <wiringPi.h>
#include <stdio.h>
#include <iostream>
#include <limits.h>

using namespace std;
using namespace cv;

/// Global variables

Mat frame, frame_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( frame_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  frame.copyTo( dst, detected_edges);
  imshow( window_name, dst );
 }


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  VideoCapture cap(0); // open the video file for reading
  cap.set(CV_CAP_PROP_BUFFERSIZE, 3);
  
  while(1)
    {
        //Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video
        

        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read the frame from video file" << endl;
            break;
        }
        
        if( !frame.data )
        { return -1; }

          /// Create a matrix of the same type and size as frame (for dst)
          dst.create( frame.size(), frame.type() );

          /// Convert the image to grayscale
          cvtColor( frame, frame_gray, COLOR_BGR2GRAY );

          /// Create a window
          namedWindow( window_name, WINDOW_AUTOSIZE );

          /// Create a Trackbar for user to enter threshold
          createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

          /// Show the image
          CannyThreshold(0, 0);

        //imshow("MyVideo", frame); //show the frame in "MyVideo" window

        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break; 
        }
        
    //    sleep(1);
  
}
  return 0;
  }