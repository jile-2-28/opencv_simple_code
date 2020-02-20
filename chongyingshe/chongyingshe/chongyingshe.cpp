// chongyingshe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;

int main()
{
	//变量定义
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	//载入原始图
	srcImage = imread("2.jpg", 1);
	if (!srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n"); return false; }
	imshow("原始图", srcImage);

	//创建和原始图一样的效果图，x重映射图，y重映射图
	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	//双层循环，遍历每一个像素点，改变map_x & map_y的值
	for (int j = 0; j < srcImage.rows; j++)
	{
		for (int i = 0; i < srcImage.cols; i++)
		{
			//改变map_x & map_y的值. 
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}
	}

	//进行重映射操作
	remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	//显示效果图
	imshow("【程序窗口】", dstImage);
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
