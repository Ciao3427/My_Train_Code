#include "../include/serial.hpp"
using namespace std;


Serial::Serial(const char *file) {
    // 整个过程是固定的：
    // 给串口设备赋权，使它可以读写
    system("sudo -S chmod 777 /dev/ttyUSB0");

    // 打开串口
    fd = open(file, O_RDWR | O_NOCTTY); 
    // O_RDWR 可读可写
    // O_NOCTTY 如果file指的是终端设备，则不将此设备分配作为此进程的控制终端

    // if串口打开失败
    if (fd == -1) throw "open fail ..."; // throw 抛出异常
   
    // 配置：
    // 获取fd的属性结构体
    tcgetattr(fd, &options);
    
    options.c_iflag = IGNPAR;                            //输入模式
    options.c_oflag = 0;                                 //输出模式
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;    //控制模式
    options.c_lflag = 0;                                 //本地模式
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    options.c_cc[VTIME] = 0;  //最少读取字符数
    options.c_cc[VMIN]  = 1;  //超时时间, 单位: 100ms

    tcsetattr(fd, TCSANOW, &options);  //应用上面的设置

    // IGNPAR：忽略奇偶校检错误的字符。
    // baud_rate: 比如波特率是115200, 就是B115200
    // CS8: 8 位数据位
    // CLOCAL： 忽略调制调解器状态行
    // CREAD： 启动接收
}

// 读取数据，数据转化
void Serial::read_data(uint8_t buff[], cv::Mat &canvas) {
    if (fd == -1) {
        std::cout << "open fail..." << std::endl;
        return;
    }
    // 定义字体
    auto font_face = cv::FONT_HERSHEY_COMPLEX; // 正常大小有衬线字体
    // 关于font_face参数：
    // CV_FONT_HERSHEY_SIMPLEX                正常大小无衬线字体. 
    // CV_FONT_HERSHEY_PLAIN                  小号无衬线字体.
    // CV_FONT_HERSHEY_DUPLEX                 正常大小无衬线字体比 CV_FONT_HERSHEY_SIMPLEX 更复杂) 
    // CV_FONT_HERSHEY_COMPLEX                正常大小有衬线字体.
    // CV_FONT_HERSHEY_TRIPLEX                正常大小有衬线字体 (  比 CV_FONT_HERSHEY_COMPLEX更复杂) 
    // CV_FONT_HERSHEY_COMPLEX_SMALL          CV_FONT_HERSHEY_COMPLEX 的小译本.
    // CV_FONT_HERSHEY_SCRIPT_SIMPLEX         手写风格字体.
    // CV_FONT_HERSHEY_SCRIPT_COMPLEX         比 CV_FONT_HERSHEY_SCRIPT_SIMPLEX 更复杂.
    // 参数能够由一个值和可选择的 CV_FONT_ITALIC  字体标记合成。就是斜体字.

    // 定义颜色
    auto font_color = cv::Scalar(255, 255, 255);
    // define CV_RGB(r, g, b) cv::Scalar((b), (g), (r), 0)
    // OpenCV color channel order is BGR[A]
    // OpenCV 颜色通道的顺序为 BGR [A]

    //创建一个 cv::Point 对象，并命名为 Point
    cv::Point point;
    point.x = 0, point.y = 30;

    while (true) {
        // auto st = std::clock();
        if (read(fd, buff, 1) == 1) {
            uint8_t frame_head = buff[0]; // 从文件描述符fd中读取1个字节的数据，并储存到buff中

            // 帧头正确
            if (frame_head == 0xff) {
                if (read(fd, buff + 1, 13) == 13) {
                    uint8_t frame_tail = buff[13]; // 如果帧头正确，则继续读取3个字节的数据，并存储到buff的后续位置
                    std::cout<<frame_tail;

                    // 帧尾正确
                    if (frame_tail == 0xfe) {
                        ConvertData convert_data;  // 定义convert_data变量

                        // 转换数据格式
                        // convert_data.data[0] = buff[2];
                        // convert_data.data[1] = buff[1];
                        int j = 12;
                        for (int i = 0 ; i <= 12 && j >= 2 ; i += 1 , j -= 1) {
                            convert_data.data[i] = buff[j];
                        }

                        // 将十六为数据转为string可以画在Mat上
                        auto data = std::to_string(convert_data.o); // 如果帧尾正确，则将读取到的数据转换为特定格式，并将其字符串表示存储到data变量中

                        // 在图像canvas上绘制文本data，使用指定的字体、颜色和大小
                        cv::putText(canvas, data, point, font_face, 1, font_color, 2);
                        // cv::putText 绘制文字：
                        // void cv::putText(
                        // cv::Mat& img,                  // 待绘制的图像
                        // const string& text,            // 待绘制的文字
                        // cv::Point origin,              // 文本框的左下角
                        // int fontFace,                  // 字体 (如cv::FONT_HERSHEY_PLAIN)
                        // double fontScale,              // 尺寸因子，值越大文字越大
                        // cv::Scalar color,              // 线条的颜色（RGB）
                        // int thickness = 1,             // 线条宽度
                        // int lineType = 8,              // 线型（4邻域或8邻域，默认8邻域）
                        // bool bottomLeftOrigin = false  // true='origin at lower left'
                        // );
                        cv::imshow("img", canvas); // 将图像canvas显示在名为“img”的窗口上
                        
                        // 按下esc结束程序(退出循环)
                        int k = cv::waitKey(2);
                        if (k == 27) break;

                        // 竖直方向画出数字
                        point.y += 30;
                        if (point.y > canvas.rows) {
                            point.y = 30;
                            point.x += 140;
                        }
                        // 休眠20ms
                        std::this_thread::sleep_for(std::chrono::milliseconds(20));
                    }
                }
                if (read(fd, buff + 1, 13) < 13)
                    break;
            }
        }
        
        auto ed = std::clock();
        // std::cout << "spend :" << double(ed - st) / CLOCKS_PER_SEC  << "ms" << std::endl;
    }
}

// 这段代码实现了通过串口读取数据，
// 并将读取到的数据转换为字符串，
// 使用OpenCV在图像上显示出来。
// 具体实现方式是：
// 定义一个Serial类，
// 构造函数中打开串口设备并设置串口属性，
// read_data函数通过循环不停地从串口读取数据，
// 并对数据格式进行转换，
// 最终将转换后的字符串使用OpenCV中的putText函数写入到一个Mat图像中，
// 展示在窗口中。