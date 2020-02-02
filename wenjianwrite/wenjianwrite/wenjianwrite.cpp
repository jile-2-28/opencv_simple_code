// wenjianwrite.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "opencv2/opencv.hpp"  
#include <time.h>  
#include <iostream>
using namespace cv;
#define TIME_MAX 32

int main()
{
	//改变console字体颜色
	system("color 5F");


	//初始化
	FileStorage fs("test.yaml", FileStorage::WRITE);

	//开始文件写入
	fs << "frameCount" << 5;
	time_t rawtime; 
	time(&rawtime);
	struct tm tmTmp;
	char stTmp[TIME_MAX];
	//使用localtime函数把秒数时间rawtime转换为本地时间以tm结构体保存，并把tm结构体地址储存到timeinfo当中
	//使用asctime函数把tm结构体中储存的时间转换为字符串，并输出
	localtime_s(&tmTmp, &rawtime);
	asctime_s(stTmp, &tmTmp);
	fs << "calibrationDate" << stTmp;
	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
	fs << "features" << "[";
	for (int i = 0; i < 3; i++)
	{
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;

		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
		for (int j = 0; j < 8; j++)
			fs << ((lbp >> j) & 1);
		fs << "]" << "}";
	}
	fs << "]";
	fs.release();

	printf("\n文件读写完毕，请在工程目录下查看生成的文件~");
	getchar();

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
