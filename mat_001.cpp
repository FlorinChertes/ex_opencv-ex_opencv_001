#include <opencv2/opencv.hpp>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#include<iostream>

std::string time_in_HH_MM_SS_MMM()
{
    using namespace std::chrono;

    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

void test_webcam()
{
    std::cout << "instatiate VideoCpture." << std::endl;
    cv::VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.

    const int device_id = 0;
    const int api_id = cv::CAP_ANY;

    cap.open(device_id, api_id);


    if(cap.isOpened() == false) {
        std::cout << "could not open camera" << std::endl;
        return;
    }

    const double d_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    const double d_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    std::cout << "Resolution: " << d_width << " x " << d_height << std::endl;

    cv::Mat frame;
    
    for(int i = 0; ; ++i) {

        const bool success = cap.read(frame);
        if (not success) {
            std::cout << "error read frame." << std::endl;
        }
        else if( frame.empty() ) {
            std::cout << "got empty frame." << std::endl;
        }
        
        const std::string file_name ("../images/img_" + time_in_HH_MM_SS_MMM() + ".jpg");

        cv::imshow("this is you, smile! :)", frame);

        imwrite( file_name, frame );        

        if( cv::waitKey(10) == 27 )
            break; // stop capturing by pressing ESC     
    }

    // the camera will be closed automatically upon exit
    // cap.close();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void mat_test_002()
{
    cv::Mat M(2,2, CV_8UC3, cv::Scalar(0,0,255));
    std::cout << "M = " << std::endl << 
        " " << M << std::endl << std::endl;    
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void mat_test_001(char* imageName )
{
    cv::Mat image;
    image = imread( imageName, cv::IMREAD_COLOR );

    if(!image.data )
    {
        printf( " No image data \n " );
    }

    cv::Mat img_copy_01(image);
    cv::Mat img_copy_02 = image;    
 }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main( int argc, char** argv )
{
    if( argc != 2)
    {
        printf( " No image data \n " );
        return -1;
    }

    char* imageName = argv[1];
    //mat_test_001(imageName);
    //mat_test_002();
    test_webcam();

    return 0;
}
