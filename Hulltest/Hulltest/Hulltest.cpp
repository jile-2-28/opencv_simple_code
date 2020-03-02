﻿// Hulltest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图窗口】"					//为窗口标题定义的宏 
#define WINDOW_NAME2 "【效果图窗口】"					//为窗口标题定义的宏

static void ShowHelpText();
void on_ThreshChange(int, void*);

Mat g_srcImage; Mat g_grayImage;
int g_nThresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = g_srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

int main()
{
	system("color 3F");
	ShowHelpText();

	// 加载源图像
	g_srcImage = imread("jay.jpg", 1);

	// 将原图转换成灰度图并进行模糊降
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// 创建原图窗口并显示
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	//创建滚动条
	createTrackbar(" 阈值:", WINDOW_NAME1, &g_nThresh, g_maxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);//调用一次进行初始化

	waitKey(0);
	return(0);
}

void on_ThreshChange(int, void*)
{
	// 对图像进行二值化，控制阈值
	threshold(g_grayImage, g_thresholdImage_output, g_nThresh, 255, THRESH_BINARY);

	// 寻找轮廓
	findContours(g_thresholdImage_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// 遍历每个轮廓，寻找其凸包
	vector<vector<Point> >hull(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		convexHull(Mat(g_vContours[i]), hull[i], false);
	}

	// 绘出轮廓及其凸包
	Mat drawing = Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	// 显示效果图
	imshow(WINDOW_NAME2, drawing);
}

void ShowHelpText()
{
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");
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
