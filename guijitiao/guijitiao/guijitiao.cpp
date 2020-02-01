// guijitiao.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

#define WINDOW_NAME "【线性混合示例】"

const int g_nMaxAlphaValue = 100;//Alpha值的最大值
int g_nAlphaValueSlider;//滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

//响应滑动条的回调函数
void on_Trackbar(int, void*)
{
    //求出当前alpha值相对于最大值的比例
    g_dAlphaValue = (double) g_nAlphaValueSlider / g_nMaxAlphaValue;
    //则bata值为1减去alpha值
    g_dBetaValue = (1.0 - g_dAlphaValue);
    //根据alpha和beta值进行线性混合
    addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
    imshow(WINDOW_NAME, g_dstImage);
}



int main(int agrc, char** argv)
{
    g_srcImage1 = imread("1.jpg");
    g_srcImage2 = imread("2.jpg");
    if (!g_srcImage1.data) {
        printf("读取第一幅图片错误，请确定目录下是否有imread函数指定图片存在~！\n");
        return -1;
    }
    if (!g_srcImage2.data) {
        printf("读取第二幅图片错误，请确定目录下是否有imread函数指定图片存在~！\n");
        return -1;
    }

    g_nAlphaValueSlider = 70;
    namedWindow(WINDOW_NAME, 1);

    char TrackbarName[50];
    sprintf_s(TrackbarName,"透明值%d", g_nMaxAlphaValue);
    createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);
    on_Trackbar(g_nAlphaValueSlider,0);
    waitKey(0);
    return 0;
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
