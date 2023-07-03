#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


int main(int argc, char** argv)
{
    cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);

    cv::VideoCapture cap;

    if (argc == 1)
    {
        cap.open(0);
    }
    else {
    cap.open(argv[1]);
    }


    if (!cap.isOpened())
    {
        std::cerr<<"摄像头未成功打开"<<std::endl;
        return -1;
    }    
    else 
    {
        while (1) {
            cv::Mat frame;
            cap>>frame;
            cv::imshow("Example", frame);

            char c = (char) cv::waitKey(30);
            if (c == 27)
                break;
        }
    }
}



    // //读取视频或摄像头
    // VideoCapture capture(0);
 
    // while (true)
    // {
    //     Mat frame;
    //     capture >> frame;
    //     imshow("读取视频", frame);
    //     waitKey(30);    //延时30
    // }
    // return 0;



    
    // std::cout << argc << '\n';

    // std::cout << argv[1][0] << '\t' <<argv[1][1] << '\n';

    // return 0;
