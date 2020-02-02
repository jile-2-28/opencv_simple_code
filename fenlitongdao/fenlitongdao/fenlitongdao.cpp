// fenlitongdao.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool  MultiChannelBlending();

int main()
{
	system("color 9F");

	if (MultiChannelBlending())
	{
		cout << endl << "\n运行成功，得出了需要的图像~! ";
	}

	waitKey(0);
	return 0;
}

bool  MultiChannelBlending()
{
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat  imageBlueChannel;

	logoImage = imread("logo.jpg", 0);
	srcImage = imread("kobe.jpg");

	if (!logoImage.data) { printf("Oh，no，读取logoImage错误~！ \n"); return false; }
	if (!srcImage.data) { printf("Oh，no，读取srcImage错误~！ \n"); return false; }

	split(srcImage, channels);//分离色彩通道

	//将原图的蓝色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	imageBlueChannel = channels.at(0);
	//将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//将三个单通道重新合并成一个三通道
	merge(channels, srcImage);

	//显示效果图
	namedWindow(" <1>原画+logo蓝色通道");
	imshow(" <1>原画+logo蓝色通道", srcImage);

	Mat  imageGreenChannel;

	logoImage = imread("logo.jpg", 0);
	srcImage = imread("kobe.jpg");

	if (!logoImage.data) { printf("读取logoImage错误~！ \n"); return false; }
	if (!srcImage.data) { printf("读取srcImage错误~！ \n"); return false; }

	split(srcImage, channels);//分离色彩通道

	//将原图的绿色通道的引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	imageGreenChannel = channels.at(1);
	//将原图的绿色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageGreenChannel中
	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//将三个独立的单通道重新合并成一个三通道
	merge(channels, srcImage);

	//显示效果图
	namedWindow("<2>原画+logo绿色通道");
	imshow("<2>原画+logo绿色通道", srcImage);

	Mat  imageRedChannel;

	logoImage = imread("logo.jpg", 0);
	srcImage = imread("kobe.jpg");

	if (!logoImage.data) { printf("Oh，no，读取logoImage错误~！ \n"); return false; }
	if (!srcImage.data) { printf("Oh，no，读取srcImage错误~！ \n"); return false; }

	split(srcImage, channels);//分离色彩通道

	//将原图的红色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	imageRedChannel = channels.at(2);
	//将原图的红色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageRedChannel中
	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//将三个独立的单通道重新合并成一个三通道
	merge(channels, srcImage);

	//显示效果图
	namedWindow("<3>原画+logo红色通道 ");
	imshow("<3>原画+logo红色通道 ", srcImage);

	return true;
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
