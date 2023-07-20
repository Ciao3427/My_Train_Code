#ifndef __SERIAL_HPP__
#define __SERIAL_HPP__

#include<iostream>
#include <fstream>
#include <string>

#include <fcntl.h>  //文件控制选项头文件
#include <stdio.h>
#include <termios.h>  //linux串口相关的头文件
#include <unistd.h>
#include <stdlib.h>  // 引用system()函数

#include <thread>
#include <chrono>


#include <opencv2/opencv.hpp> 


class Serial {
private:
    int fd;              // 串口文件描述符
    struct termios options;  // 串口配置选项


public:
    Serial(const char* file);  // 构造函数
    void read_data(uint8_t buff[], cv::Mat &canvas);
};

union ConvertData {
    // int o;  // 示例中使用的字段类型为int，根据实际情况进行调整
    // unsigned char data[14];
    uint8_t data[14];
    uint16_t o;
};


#endif