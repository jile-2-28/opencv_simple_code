// houghyuan.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	//载入原始图、Mat变量定义   
	Mat srcImage = imread("logo.jpg");  //工程目录下应该有一张名为logo.jpg的素材图
	Mat midImage, dstImage;//临时变量和目标图的定义

	//显示原始图
	imshow("【原始图】", srcImage);

	//转为灰度图并进行图像平滑
	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);//转化边缘检测后的图为灰度图
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

	//进行霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

	//依次在图中绘制出圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		//参数定义
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

	//显示效果图  
	imshow("【效果图】", srcImage);

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
