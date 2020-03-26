﻿// harriscornerTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【程序窗口1】"        //为窗口标题定义的宏  
#define WINDOW_NAME2 "【程序窗口2】"        //为窗口标题定义的宏  

Mat g_srcImage, g_srcImage1, g_grayImage;
int thresh = 30; //当前阈值
int max_thresh = 175; //最大阈值

void on_CornerHarris(int, void*);//回调函数
static void ShowHelpText();

int main(int argc, char** argv)
{
	//改变console字体颜色
	system("color 3F");

	//显示帮助文字
	ShowHelpText();

	//载入原始图并进行克隆保存
	g_srcImage = imread("1.jpg", 1);
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n"); return false; }
	imshow("原始图", g_srcImage);
	g_srcImage1 = g_srcImage.clone();

	//存留一张灰度图
	cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);

	//创建窗口和滚动条
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	createTrackbar("阈值: ", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);

	//调用一次回调函数，进行初始化
	on_CornerHarris(0, 0);

	waitKey(0);
	return(0);
}

void on_CornerHarris(int, void*)
{
	Mat dstImage;//目标图
	Mat normImage;//归一化后的图
	Mat scaledImage;//线性变换后的八位无符号整型的图

	//置零当前需要显示的两幅图，即清除上一次调用此函数时他们的值
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone();

	//进行角点检测
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);

	// 归一化与转换
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//将归一化后的图线性变换成8位无符号整型 

	//---------------------------【4】进行绘制-------------------------------------
	// 将检测到的，且符合阈值条件的角点绘制出来
	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			if ((int)normImage.at<float>(j, i) > thresh + 80)
			{
				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}
	//---------------------------【4】显示最终效果---------------------------------
	imshow(WINDOW_NAME1, g_srcImage1);
	imshow(WINDOW_NAME2, scaledImage);

}

static void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//输出一些帮助信息
	printf("\n\n\n\t【欢迎来到Harris角点检测示例程序~】\n\n");
	printf("\n\t请调整滚动条观察图像效果~\n\n");
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
