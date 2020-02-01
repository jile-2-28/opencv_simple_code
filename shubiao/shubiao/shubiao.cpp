// shubiao.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

#define WINDOW_NAME "【程序窗口】"

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);

Rect g_rectangle;
bool g_dDrawingBox = false;
RNG g_rng(12345);


int main()
{
    g_rectangle = Rect(-1, -1, 0, 0);
    Mat srcImage(600, 800, CV_8UC3), tempImage;
    srcImage.copyTo(tempImage);
    g_rectangle = Rect(-1, -1, 0, 0);
    srcImage = Scalar::all(0);

    namedWindow(WINDOW_NAME);
    setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

    while (1) {
        srcImage.copyTo(tempImage);//复制源图到临时变量
        if(g_dDrawingBox)  DrawRectangle(tempImage, g_rectangle);
        imshow(WINDOW_NAME, tempImage);
        if (waitKey(10) == 27) break;//按下ESC键，程序退出

    }
    return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param) {
    Mat& image = *(cv::Mat*) param;
    switch (event) {
        //鼠标移动消息
    case EVENT_MOUSEMOVE: {
        if (g_dDrawingBox)//如果是否进行绘制的标识符为真，则记录下长和宽到RECT型变量中
        {
            g_rectangle.width = x - g_rectangle.x;
            g_rectangle.height = y - g_rectangle.y;
        }
    }
                        break;
    //左键按下消息
    case EVENT_LBUTTONDOWN: { 
        g_dDrawingBox = true;
        g_rectangle = Rect(x, y, 0, 0);//记录起始点
    }
                        break;
    //左键抬起消息
    case EVENT_LBUTTONUP: {
        g_dDrawingBox = false;
        if (g_rectangle.width < 0) {
            g_rectangle.x += g_rectangle.width;
            g_rectangle.width *= -1;
        }
        if (g_rectangle.height < 0) {
            g_rectangle.y += g_rectangle.height;
            g_rectangle.height *= -1;
        }
        DrawRectangle(image, g_rectangle);
    }
                        break;

    }

}

void DrawRectangle(cv::Mat& img, cv::Rect box) {
    rectangle(img, box.tl(),box.br(),Scalar(g_rng.uniform(0,255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//随机颜色
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
