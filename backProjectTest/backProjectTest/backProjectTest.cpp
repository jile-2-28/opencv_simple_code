// backProjectTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;


#define WINDOW_NAME1 "【原始图】"        //为窗口标题定义的宏 


Mat g_srcImage; Mat g_hsvImage; Mat g_hueImage;
int g_bins = 30;//直方图组距

static void ShowHelpText();
void on_BinChange(int, void*);

int main()
{
	//改变console字体颜色
	system("color 6F");

	//显示帮助文字
	ShowHelpText();

	//读取源图像，并转换到 HSV 空间
	g_srcImage = imread("1.jpg", 1);
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n"); return false; }
	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);

	//分离 Hue 色调通道
	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = { 0, 0 };
	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

	//创建 Trackbar 来输入bin的数目
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	createTrackbar("色调组距 ", WINDOW_NAME1, &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);//进行一次初始化

	//显示效果图
	imshow(WINDOW_NAME1, g_srcImage);

	// 等待用户按键
	waitKey(0);
	return 0;
}

void on_BinChange(int, void*)
{
	//参数准备
	MatND hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	//计算直方图并归一化
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	//计算反向投影
	MatND backproj;
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);

	//显示反向投影
	imshow("反向投影图", backproj);

	//绘制直方图的参数准备
	int w = 400; int h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	//绘制直方图
	for (int i = 0; i < g_bins; i++)
	{
		rectangle(histImg, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)), Scalar(100, 123, 255), -1);
	}

	//【7】显示直方图窗口
	imshow("直方图", histImg);
}

static void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//输出一些帮助信息
	printf("\n\n\t欢迎来到【反向投影】示例程序\n\n");
	printf("\n\t请调整滑动条观察图像效果\n\n");

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
