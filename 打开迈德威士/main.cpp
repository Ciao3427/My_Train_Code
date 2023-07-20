#include <iostream>
#include <functional>

#include "my_libs/include/mv_camera.hpp"
#include "my_libs/include/camera.hpp"
#include "my_libs/include/time/timer.hpp"

using namespace cv;
using namespace std;

int main()
{
    // 初始化相机
    Devices::MV_Camera mv_camera{PROJECT_DIR "/Configs/camera/MV-SUA133GC-T-Manifold.config"};
    
    // 打开相机
    cv::Mat frame;
    cv::namedWindow("Camera" , cv::WINDOW_AUTOSIZE);
    mv_camera.open();

    //计时
    // 为什么要有时间戳？
    // 每一帧都对应了一个时间戳，这样就可以每读到一帧动一下,尽量使最后车头摆动的结果与预计的目的点相吻合
    struct timespec tv_start;  //开始的时间戳
    struct timespec tv_end;    //结束的时间戳
    double a         = 0.99;   //进程运行时间的动量更新超参数
    double temp_time = 0;      //temp
    double this_time = 0;

    //返回一个表示当前时间的std::chrono::time_point对象，可以用来计算时间间隔。
    auto startTime = std::chrono::system_clock::now();

    


    return 0;
}




// int frame = 1; // 主线程帧数为 1
// std::mutex camera_mutex;
// cv::Mat img;
// cv::Mat copyImg;
// double timestamp_ms;  //曝光时间, 单位us


// int main()
// {
//     std::thread camerathread{ 
//         camera_thread , 
//         std::ref(main_loop_condition) ,
//         std::ref(img) ,
//         std::ref(camera_mutex) ,
//         std::ref(timestamp_ms) };
//     // 创造了一个线程 camerathread
//     // camera_thread 是一个函数指针或可调用对象，表示线程函数的入口点
//     // std::ref 是 c++ 11 的一种函数，它的作用是将一个对象转换成一个引用包装器

//     camerathread.detach();  // 线程分离

//     //计时
//     struct timespec tv_start;        //开始的时间戳
//     struct timespec tv_end;          //结束的时间戳
//     double a                = 0.99;  //线程运行时间的动量更新超参数
//     double temp_time        = 0;     //temp
//     double main_thread_time = 0;     //主线程的时间

//     //返回一个表示当前时间的std::chrono::time_point对象，可以用来计算时间间隔。
//     auto startTime = std::chrono::system_clock::now();

//     for(; main_loop_condition ; frame++)
//     {
        
//     }



//     return 0;
// }