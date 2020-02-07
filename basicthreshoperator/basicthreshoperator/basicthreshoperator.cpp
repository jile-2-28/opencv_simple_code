// basicthreshoperator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME "【程序窗口】"

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

static void ShowHelpText();
void on_Threshold(int, void*);

int main()
{
    g_srcImage = imread("lee.jpg");
    if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！\n"); return false; }
    cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    createTrackbar("模式", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
    createTrackbar("参数值", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);
    on_Threshold(0, 0);
    while (1)
    {
        int key;
        key = waitKey(20);
        if ((char)key == 27) { break; }//如果按下ESC键则退出程序
    }
}

void on_Threshold(int, void*)
{
    threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
    imshow(WINDOW_NAME, g_dstImage);
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
