#include <iostream>
#include <vector>

#include "./identify.hpp"
#include "my_libs/camera/mv_camera.cpp"
#include "my_libs/camera/mv_camera.hpp" 

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

cv::Mat read_img; // 原相
cv::Mat HSV_img; // HSV色相
cv::Mat binary_img; // 二值化图像

int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;

int main()
{
    cv::namedWindow("Camera" , cv::WINDOW_AUTOSIZE);
    cv::namedWindow("HSV" , cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("Canny" , cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Binary" , cv::WINDOW_AUTOSIZE);

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
        while (1) {
            mv_camera.read(read_img); // 抽帧

            THREAD_ASSERT_WARNING(mv_camera.read(read_img), "读取相机图片失败");

            // RGB2HSV
            cv::cvtColor(read_img, HSV_img, cv::COLOR_BGR2HSV);
            // change_img = RGB2HSV(read_img);
 
			Scalar lower(hmin, smin, vmin);
			Scalar upper(hmax, smax, vmax);
			inRange(HSV_img, lower, upper, binary_img);



            cv::imshow("Camera" , read_img);
            cv::imshow("HSV" , HSV_img);
            // cv::imshow("Canny" , canny_img);
            cv::imshow("Binary" , binary_img);
			

            char c = (char) cv::waitKey(10);
            if (c == 27)
                break;

        }
    }

    mv_camera.close();

    return 0;
}
