#include "my_libs/include/serial.hpp"
using namespace std;

int main() {
    cout << "h" << endl;
    // 指定串口文件路径（例如，在Linux上为"/dev/ttyUSB0"，在Windows上为"COM3"）
    const char* serialPortFile = "/dev/ttyUSB0"; // 根据实际串口更改此处

    // 创建Serial类的实例
    Serial serial(serialPortFile);

    // 创建一个缓冲区，用于存储从串口接收到的数据
    uint8_t buffer[14]; // 假设缓冲区大小为256字节，根据实际需求更改
    
    // 创建一个OpenCV的Mat对象，用于存储进一步处理的画布
    const char * img = "/home/ciao/Firefox_wallpaper.png";
    cv::Mat canvas = cv::imread(img , -1);

    // 从串口读取数据，并将其存储在缓冲区和画布中
    serial.read_data(buffer, canvas);

    // 在此处可以根据需要对数据或画布进行进一步处理
    // 例如，您可以使用缓冲区中接收到的数据，或使用OpenCV显示画布。

    return 0;
}
