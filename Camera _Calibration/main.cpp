#include <iostream>
#include <string>
#include <vector>


#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "my_libs/camera/mv_camera.cpp"
#include "my_libs/camera/mv_camera.hpp" 
#include "my_libs/timer/timer.hpp"
#include "./identify.hpp"

using namespace cv;
using namespace std;

// RGB 识别

// cv::Mat read_img;#include <opencv2/imgcodecs.hpp>
    
//     Ptr<BackgroundSubtractor> pKNN = createBackgroundSubtractorKNN();

//     //初始化相机
//     Devices::MV_Camera mv_camera{PROJECT_DIR "/Configs/camera/MV-SUA133GC-T-Manifold.config"};
//     mv_camera.open();   // 打开相机

//     if (mv_camera.isOpen()) {#include <opencv2/imgcodecs.hpp>


//             THREAD_ASSERT_WARNING(mv_camera.read(read_img), "读取相机图片失败");

//             std::vector<std::vector<Point>>contours;
//             pKNN->apply(read_img, mask);
//             //(*pMOG2).apply(frame, mogMask);
//             threshold(mask, mask, 100, 255, THRESH_BINARY); //二值化
//             Mat kernel = getStructuringElement(MORPH_REC#include <opencv2/imgcodecs.hpp>

//                 double area = contourArea(contours[i]);
//                 //轮廓外接矩阵
//                 Rect rect = boundingRect(contours[i]);
//                 if (area < 500 || rect.width < 50 || rect.height < 50) continue;
//                 rectangle(read_img, rect, Scalar(0,255,255),2);
//                 putText(read_img, "Target", Point(rect.x, rect.y), QT_FONT_NORMAL, FONT_HERSHEY_PLAIN, Scalar(0,255,0),2,8);
//             }

//             cv::imshow("Camera" , read_img);
//             cv::imshow("OutPut" , mask);

//             char c = (char) cv::waitKey(10);
//             if (c == 27)
//                 break;

//         }
//     }

//     mv_camera.close();

//     return 0;
// }


// HSV 识别

cv::Mat read_img; // 原相
cv::Mat HSV_img; // HSV色相
cv::Mat binary_img; // 二值化图像
cv::Mat dier_img; // 膨胀腐蚀图像
cv::Mat canny_img; // 边缘检测图像

cv::RotatedRect target_rect;
cv::Point2f pts[4];
cv::Point2f pts1[4];
cv::Point2f pts2[4];
cv::Point2f top1;
cv::Point2f bottom1;
cv::Point2f top2;
cv::Point2f bottom2;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;

int main()
{
    cv::namedWindow("Camera" , cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("HSV" , cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Binary" , cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("Dier_After" , cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("Canny" , cv::WINDOW_AUTOSIZE);

    namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

    // 初始化相机
    Devices::MV_Camera mv_camera{PROJECT_DIR "/Configs/camera/MV-SUA133GC-T-Manifold.config"};
    mv_camera.open();   // 打开相机

    if (mv_camera.isOpen()) {
        cout << "相机已打开" << endl;

        while (1) {
            mv_camera.read(read_img); // 抽帧

            THREAD_ASSERT_WARNING(mv_camera.read(read_img), "读取相机图片失败");

            // RGB2HSV
            cv::cvtColor(read_img, HSV_img, 40); 
            // cv::Color_GBR2HSV = 40
            // change_img = RGB2HSV(read_img);

            // 二值化
            // cv::inRange(HSV_img, Scalar(0, 142, 199), Scalar(98, 255, 255), binary_img); 
            Scalar lower(hmin, smin, vmin);
			Scalar upper(hmax, smax, vmax);
			inRange(HSV_img, lower, upper, binary_img);

            //因为有轮廓有断点，故要膨胀，将断点连起来  
            // 定义kernel  
            Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5), Point(-1,-1));  
            // 膨胀  
            dilate(binary_img, dier_img, kernel, Point(-1,-1));  
            // 腐蚀  
            erode(dier_img, dier_img, kernel, Point(-1,-1));
            // 高斯滤波
            cv::GaussianBlur(dier_img, dier_img, Size(5,5), 10, 20 );

            // 边缘检测
            cv::Canny(dier_img , canny_img , 10 , 100 , 3);

            

            // 轮廓外接矩形
            vector <vector<Point>> contours;  // 创建矩阵
            // 定义两个容器存放左右灯条的矩形
            vector<Rect> leftLampRects, rightLampRects;

            // 查找轮廓  
            cv::findContours(canny_img, contours, 0, 1); // 最外层轮廓  
            // 由轮廓确定正外接矩形  
            int width = 0;  
            int height = 0;  
            int x = 0;  
            int y = 0;  
            // 定义Rect类型的vector容器boundRect存放正外接矩形，初始化大小为contours.size()即轮廓个数  
            vector<Rect> boundRect(contours.size());  

            // 遍历每个轮廓  
            for (int i = 0; i < contours.size(); i++)  
            {  
                // // 由轮廓（点集）确定出正外接矩形  
                // boundRect[i] = boundingRect(Mat(contours[i])); 

                // // 获得正外接矩形的左上角坐标及宽高  
                // width = boundRect[i].width;  
                // height = boundRect[i].height;  
                // x = boundRect[i].x;  
                // y = boundRect[i].y;  

                // // 计算四个角坐标
                // Point pt1(x, y);                            // 左上角
                // Point pt2(x + width, y);                    // 右上角
                // Point pt3(x + width, y + height);           // 右下角
                // Point pt4(x, y + height);                   // 左下角

                if (contours.size() > 1) {
                    cv::RotatedRect rect1 = cv::minAreaRect(contours[0]); 

                    rect1.points(pts1);

                    std::sort(pts1,pts1 + 4, [](const cv::Point2f & a,const cv::Point & b){return a.y < b.y;});
                    top1 = (pts1[0] + pts1[1]) / 2;
                    bottom1 = (pts1[2] + pts1[3]) / 2;


                    cv::RotatedRect rect2 = cv::minAreaRect(contours[1]);

                    rect2.points(pts2);

                    std::sort(pts2,pts2 + 4, [](const cv::Point2f & a,const cv::Point & b){return a.y < b.y;});
                    top2 = (pts2[0] + pts2[1]) / 2;
                    bottom2 = (pts2[2] + pts2[3]) / 2;

                    cv::line(read_img,top1,bottom2,cv::Scalar(0,255,0),3,8,0);
                    cv::line(read_img,top2,bottom1,cv::Scalar(0,255,0),3,8,0);
                }

            }

            cv::imshow("Camera" , read_img);
            // cv::imshow("HSV" , HSV_img);
            cv::imshow("Binary" , binary_img);
            // cv::imshow("Dier_After" , dier_img);
            // cv::imshow("Canny" , canny_img);

            char c = (char) cv::waitKey(10);
            if (c == 27)
                break;

            }
    }

    else {
        cout << "相机打开失败" << endl;
    }

    mv_camera.close();

    return 0;
}

