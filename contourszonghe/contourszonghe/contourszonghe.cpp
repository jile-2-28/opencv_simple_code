// contourszonghe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图窗口】"			//为窗口标题定义的宏 
#define WINDOW_NAME2 "【轮廓图】"					//为窗口标题定义的宏 

Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345); ////构造方法设定一个具体值，表示下面代码每次生成的结果都是一样的
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

static void ShowHelpText();
void on_ThreshChange(int, void*);

int main(int argc, char** argv)
{
	//改变console字体颜色
	system("color 1F");

	//显示欢迎和帮助文字
	ShowHelpText();

	// 加载源图像
	g_srcImage = imread("jay.jpg", 1);
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n"); return false; }

	// 转成灰度并模糊化降噪
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// 创建窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	// 创建窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	//创建滚动条并初始化
	createTrackbar("canny阈值", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return(0);
}

void on_ThreshChange(int, void*)
{

	// 用Canny算子检测边缘
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	// 寻找轮廓
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// 绘出轮廓
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//任意值
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}

	// 显示效果图
	imshow(WINDOW_NAME2, drawing);
}

static void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//输出一些帮助信息  
	printf("\n\n\t欢迎来到【在图形中寻找轮廓】示例程序~\n\n");
	printf("\n\n\t按键操作说明: \n\n"
		"\t\t键盘按键任意键- 退出程序\n\n"
		"\t\t滑动滚动条-改变阈值\n");
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
