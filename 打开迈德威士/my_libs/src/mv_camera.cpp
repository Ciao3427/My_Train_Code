#include "../include/mv_camera.hpp"
#include <fmt/color.h>
#include "../include/MVSDK/CameraApi.h"
#include "../include/MVSDK/CameraDefine.h"

// API    相当于一个连接用户与处理器的信息交换接口
// app(餐厅) / user(顾客) / API(服务员：将菜谱交给厨子，把菜端给顾客) / 处理器(厨子)

namespace Devices
{
// Assert
#define MV_ASSERT_WARNING(expr, info, ...)                                                 \
    do {                                                                                   \
        if ((expr) == false) {                                                             \
            fmt::print(fg(fmt::color::orange), "[WARNING] " #expr info "\n"##__VA_ARGS__); \
        }                                                                                  \
    } while (0)
// 用于检查表达式的结果是否为假，如果是假，则输出一个警告信息
// expr     表达式
// info     描述警告信息的字符串
// ...      可变参数
// ##__VA_ARGS__      表示还可以打印更多的内容
// fmt::print(fg(fmt::color::orange), "[WARNING] " #expr info "\n"##__VA_ARGS__);   调用 fmt库 print函数：
// fg(fmt::color::orange)   字体为橙色
// 输出的警告信息格式为：[WARNING] expr info

#define MV_ASSERT_ERROR(expr, info, ...)                                                \
    do {                                                                                \
        if ((expr) == false) {                                                          \
            fmt::print(fg(fmt::color::red), "[ERROR] " #expr info "\n", ##__VA_ARGS__); \
            return false;                                                               \
        }                                                                               \
    } while (0)
// 用于断言和错误处理
// expr     一个表达式，用于进行断言。如果表达式的结果为false，则表示断言失败
// info     一个字符串，用于提供额外的错误信息
// ...      可变参数列表，用于格式化输出错误信息
// fmt::print(fg(fmt::color::red), "[ERROR] " #expr info "\n", ##__VA_ARGS__);   调用 fmt库 print函数：
// fg(fmt::color::red)    字体为红色
// 输出格式为：[ERROR] expr info

#define MV_ASSERT_THROW(expr, info, ...)                                         \
    do {                                                                         \
        if ((expr) == false) {                                                   \
            throw MindVision_FrameError(                                         \
                fmt::format("'" #expr "' = ({}) " info, status, ##__VA_ARGS__)); \
        }                                                                        \
    } while (0)
// 用于断言表达式的真假，如果断言失败（即表达式结果为 false），则抛出一个带有格式化错误信息的 MindVision_FrameError 异常
// fmt::format      格式化输出函数
// #expr    表示print输入的表达式 expr
// {}   替换符，替换的是 status中的内容
// info     信息语句，通常是 print已经整合过数据后的语句
// 最后输出的格式为：' expr ' + (status) info

// check_api
#define MV_CHECK_API_WARNING(expr, info, ...)                                         \
    do {                                                                              \
        auto status = (expr);                                                         \
        if (status != CAMERA_STATUS_SUCCESS) {                                        \
            fmt::print(                                                               \
                fg(fmt::color::orange), "[WARNING] '" #expr "' = ({}) " info, status, \
                ##__VA_ARGS__);                                                       \
        }                                                                             \
    } while (0)
//用于检查 MindVision API 调用的状态，如果返回的状态不是 CAMERA_STATUS_SUCCESS，则输出警告信息
// 因为这是一个警告，所以宏的执行流程会继续向下执行，而不会返回或抛出异常
// auto     可以根据表达式的类型自动推断变量的类型
// 输出格式为：[WARNING] ' expr ' = (status) info
// 颜色为橙色

#define MV_CHECK_API_ERROR(expr, info, ...)                                           \
    do {                                                                              \
        auto status = (expr);                                                         \
        if (status != CAMERA_STATUS_SUCCESS) {                                        \
            fmt::print(                                                               \
                fg(fmt::color::red), "[ERROR] '" #expr "' = ({}) " info "\n", status, \
                ##__VA_ARGS__);                                                       \
            return false;                                                             \
        }                                                                             \
    } while (0)
// 用于检查 MindVision API 调用的状态并输出错误信息
// 用于检查 MindVision API 调用的状态，如果返回的状态不是 CAMERA_STATUS_SUCCESS，则输出错误信息，并返回 false 表示发生了错误
// 输出格式为：[ERROR] ' expr ' = (status) info \n
// 颜色为红色

#define MV_CHECK_API_THROW(expr, info, ...)                                      \
    do {                                                                         \
        auto status = (expr);                                                    \
        if (status != CAMERA_STATUS_SUCCESS) {                                   \
            throw MindVision_FrameError(                                         \
                fmt::format("'" #expr "' = ({}) " info, status, ##__VA_ARGS__)); \
        }                                                                        \
    } while (0)
// 用于检查 MindVision API 调用的状态并抛出异常
// 用于检查 MindVision API 调用的状态，
// 如果返回的状态不是 CAMERA_STATUS_SUCCESS，则抛出一个 MindVision_FrameError 异常，
// 异常的错误消息包含详细的错误信息
// 输出格式为：' expr ' = (status) info

MV_Camera::MV_Camera(const char * camera_cfg) : camera_cfg(camera_cfg)
{
    
    MV_CHECK_API_WARNING(CameraSdkInit(1), "");  
    handle = -1;
}
// CameraSdkInit(1)     表示SDK内部提示信息和界面的语种为中文(0为英文，1为中文)
// expr     CameraSdkInit(1)
// info     空字符串""
// 输出格式为：[WARNING] 'CameraSdkInit(1)' = (some_status) 
// 颜色为橙色

MV_Camera::~MV_Camera()
{
    if (isOpen()) {
        close();
    }
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "相机已释放！");
}
// 用于释放相机资源
// 首先调用 isOpen()查看相机是否打开，如果处于打开状态，则调用 close()函数将其关闭，最后输出 "相机已释放"
// fm::color::red       字体为红色
// fmt::emphasis::bold      字体加粗

bool MV_Camera::open()
{
    if (isOpen()) {
        if (!close()) return false;
    }

    tSdkCameraDevInfo infos[2];

    int dev_num = 2;
    //获得设备的信息, dev_num返回找到的相机个数
    MV_CHECK_API_ERROR(CameraEnumerateDevice(infos, &dev_num), "");
    // CameraEnumerateDevice( tSdkCameraDevInfo* pCameraList , INT*piNums )
    // infos        pCmeraList      设备列表数组指针
    // &dev_num     piNums      设备的个数指针，调用时传入pCameraList
    // 成功时，返回CAMERA_STATUS_SUCCESS (0)
    // 最后输出格式为：[ERROR] ' CAMERA_STATUS_SUCCESS (0) ' = ({}) \n

    MV_ASSERT_ERROR(dev_num > 0, "未发现设备！");
    // 断言，意为如果不满足 dev_num > 0 则返回“未发现设备”

    //相机初始化，根据相机型号名从文件中加载参数，例如MV-U300
    MV_CHECK_API_ERROR(CameraInit(&infos[0], PARAM_MODE_BY_MODEL, -1, &handle), "");
    // CameraInit( SdkCameraDevInfo* pCameraInfo , int emParamLoadMode , int emTeam , CameraHandle* pCameraHandle )
    // 用于相机初始化：初始化成功后，才能调用任何其他相机相关的操作接口；成功时，返回值为
    // &infos[0]                    SdkCameraDevInfo* pCameraInfo     设备的枚举信息结构体指针，由CameraEnumerateDevice获得
    // PARAM_MODE_BY_MODEL(值为0)    int emParamLoadMode               相机初始化时使用的参数加载方式：-1表示使用上次退出时的参数加载方式；那么0呢？
    // -1                           int emTeam                        初始化时使用的参数组：-1表示加载上次退出时的参数组
    // &handle                      CameraHandle* pCameraHandle       相机的句柄指针，初始化成功后，该指针返回该相机的有效句柄；在调用其他相机相关的操作接口时，都需要传入该句柄；主要用于多相机之间的区分

    MV_ASSERT_ERROR(handle >= 0, "相机未找到！");
    // 通常在相机句柄 handle >= 0时表示相机成功初始化，handle <= 0时表示相机初始化失败
    // 那为什么在 handle >= 0时要报错相机未找到？？？
    // 断言，一般为判断条件为假的的时候执行，也就是说，当检测到不满足条件 handle >= 0时执行"相机未找到"

    tSdkCameraCapbility tCapability;  //设备描述信息
    MV_CHECK_API_ERROR(CameraGetCapability(handle, &tCapability), "");

    /*
    fmt::print(
        "是否可从文件读取参数: {}, 相机name: {}\n", tCapability.bParamInDevice,
        infos[0].acFriendlyName);

    if (tCapability.bParamInDevice == 0) {  //不支持从相机中读写参数组
        fmt::print("不支持从相机读写参数组\n");
        setConfig();
    } else {
        fmt::print("配置文件路径：{}\n", camera_cfg);
        MV_CHECK_API_WARNING(
            CameraReadParameterFromFile(handle, (char *)camera_cfg.data()),
            "从文件读取相机配置文件错误，路径为: {}", camera_cfg);
    }
    */
    // 保存相机配置
    // MV_CHECK_API_ERROR(CameraSaveParameterToFile(handle, "/home/dji/Codes/rm_auto_aim/Configs/camera/MV-SUA133GC-T-Manifold.config"), "");
    //相机配置文件的index要改成255, 否则设置的图片大小无效!!
    fmt::print("配置文件路径：{}\n", camera_cfg);
    MV_CHECK_API_WARNING(
        CameraReadParameterFromFile(handle, (char *)camera_cfg.data()),
        "从文件读取相机配置文件错误，路径为: {}", camera_cfg);

    // tSdkImageResolution * resolution;
    // MV_CHECK_API_ERROR(CameraGetImageResolution(handle, resolution), "");
    // fmt::print(fg(fmt::color::orange), "{} {}\n", resolution->iHeight, resolution->iWidth);

    // 设置相机触发模式, 用不了
    // MV_CHECK_API_ERROR(CameraSetTriggerMode(handle, 0), "");

    MV_CHECK_API_ERROR(CameraPlay(handle), "");
    //加载参数组
    //MV_CHECK_API_ERROR(CameraLoadParameter(handle, PARAMETER_TEAM_A), "");

    MV_CHECK_API_ERROR(CameraSetIspOutFormat(handle, CAMERA_MEDIA_TYPE_BGR8), "");


    return true;
}

/**
 * @brief 当从文件读取失效后，手动设置。
 * 
 */
bool MV_Camera::setConfig()
{
    /**
     * @brief 设置相机配置参数
     * 
     */
    CameraGetImageResolution(handle, &pImageResolution);
    /*
    pImageResolution.iIndex      = 0xFF;
    pImageResolution.iWidthFOV   = _CAMERA_RESOLUTION_COLS;
    pImageResolution.iHeightFOV  = _CAMERA_RESOLUTION_ROWS;
    pImageResolution.iWidth      = _CAMERA_RESOLUTION_COLS;
    pImageResolution.iHeight     = _CAMERA_RESOLUTION_ROWS;
    pImageResolution.iHOffsetFOV = static_cast<int>((1280 - _CAMERA_RESOLUTION_COLS) * 0.5);
    pImageResolution.iVOffsetFOV = static_cast<int>((1024 - _CAMERA_RESOLUTION_ROWS) * 0.5);
    */
    CameraSetImageResolution(handle, &pImageResolution);

    // 设置曝光时间
    CameraGetAeState(handle, &AEstate);
    CameraSetAeState(handle, FALSE);
    // CameraSetExposureTime(handle, _CAMERA_EXPOSURETIME);
    // 设置颜色增益
    CameraSetGain(handle, 145, 130, 105);
    return true;
}

bool MV_Camera::close()
{
    MV_ASSERT_WARNING(handle >= 0, "相机已经关闭！\n");  //
    if (handle < 0) return true;
    MV_CHECK_API_ERROR(CameraUnInit(handle), "");
    handle = -1;
    return true;
}

bool MV_Camera::isOpen() const
{
    return handle >= 0;
}

bool MV_Camera::read(cv::Mat & img) const
{
    // fmt::print(bg(fmt::color::green),"相机句柄为 {}",this->handle);
    MV_ASSERT_ERROR(isOpen(), "相机未打开！");
    tSdkFrameHead head;
    BYTE * buffer;
    // 100 为超时时间
    MV_CHECK_API_ERROR(CameraGetImageBuffer(handle, &head, &buffer, 1000), "");
    img = cv::Mat(head.iHeight, head.iWidth, CV_8UC3);
    MV_CHECK_API_ERROR(CameraImageProcess(handle, buffer, img.data, &head), "");
    MV_CHECK_API_ERROR(CameraReleaseImageBuffer(handle, buffer), "");
    return true;
}
/**
 * @brief 这个函数的double是可以获取当前帧的采集时间
 *
 */
bool MV_Camera::read(cv::Mat & img, double & timestamp_ms) const
{
    MV_ASSERT_ERROR(isOpen(), "相机未打开！");
    tSdkFrameHead head;
    BYTE * buffer;
    // 100 为超时时间
    MV_CHECK_API_ERROR(CameraGetImageBuffer(handle, &head, &buffer, 1000), "");
    // fmt::print(fg(fmt::color::green), "[{}, {}]", head.iHeight, head.iWidth);
    img = cv::Mat(head.iHeight, head.iWidth, CV_8UC3);
    MV_CHECK_API_ERROR(CameraImageProcess(handle, buffer, img.data, &head), "");
    // timestamp_ms = head.uiTimeStamp;  // uiTimeStamp 该帧的采集时间，单位0.1毫秒
    timestamp_ms = head.uiExpTime;  //当前图像的曝光值，单位为微秒us
    MV_CHECK_API_ERROR(CameraReleaseImageBuffer(handle, buffer), "");
    return true;
}

bool MV_Camera::get_exposure_us(double & us) const
{
    MV_ASSERT_ERROR(isOpen(), "相机未打开！");
    MV_CHECK_API_ERROR(CameraGetExposureTime(handle, &us), "");
    return true;
}

bool MV_Camera::set_exposure_us(double us) const
{
    MV_ASSERT_ERROR(isOpen(), "相机未打开！");
    MV_CHECK_API_ERROR(CameraSetExposureTime(handle, us), "");
    return true;
}

}  // namespace Devices
