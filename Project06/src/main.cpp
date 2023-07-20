#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"

// int main(int argc, char** argv)
// {
//     //打开摄像头或视频
//     cv::namedWindow("real-time traking", cv::WINDOW_AUTOSIZE); //创建自动大小的窗口

//     cv::VideoCapture cap; //【将视频信息储存到cap中

//     if (argc == 1)
//     {
//         cap.open(0); //打开0号摄像头（默认摄像头）
//     }
//     else 
//     {
//         cap.open(argv[1]); //打开某地址指代的视频
//     }

//     if (!cap.isOpened())
//     {
//         std::cerr<<"摄像头未成功打开"<<std::endl;
//         return -1;
//     }
//     else {
//         while (1) {
//         cv::Mat frame; //将摄像头获取的视频数据转换成Mat型
//         cap>>frame;
//         cv::imshow("real-time traking", frame); //显示窗口

//         char c = (char) cv::waitKey(30); //从键盘获取命令
//         if (c == 27) //如果键入Esc,则退出摄像头
//             break;
//         }
//     }

// }

#include<opencv2/opencv.hpp>
using namespace cv;
//基于移动对象的轮廓的跟踪
int main()
{
    Mat frame;
    bool flag = true;
    VideoCapture capture;
    capture.open(0);
    if (!capture.isOpened())
    {
        printf("can not open ......\n");
        return -1;
    }
    namedWindow("mask", WINDOW_AUTOSIZE);
    namedWindow("output", WINDOW_AUTOSIZE); 
    Ptr<BackgroundSubtractor> pKNN = createBackgroundSubtractorKNN();
    //Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2();

    while (capture.read(frame))
    {
        Mat KNNMask;
        std::vector<std::vector<Point>>contours; 
        pKNN->apply(frame, KNNMask);
        //(*pMOG2).apply(frame, mogMask);
        threshold(KNNMask, KNNMask, 100, 255, THRESH_BINARY); //二值化
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(KNNMask, KNNMask, MORPH_OPEN, kernel, Point(-1,-1)); //图像形态学
        findContours(KNNMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0,0));

        for (int i = 0; i < contours.size(); i++)
        {
            //轮廓面积
            double area = contourArea(contours[i]);
            //轮廓外接矩阵
            Rect rect = boundingRect(contours[i]);
            if (area < 500 || rect.width < 50 || rect.height < 50) continue;
            rectangle(frame, rect, Scalar(0,255,255),2);
            putText(frame, "Target", Point(rect.x, rect.y), QT_FONT_NORMAL, FONT_HERSHEY_PLAIN, Scalar(0,255,0),2,8);
        }
        imshow("mask",KNNMask);
        imshow("output",frame);
        waitKey(1);

        char c = (char) cv::waitKey(30);
        if (c == 27)
            break;
    }
    return 0;
}
