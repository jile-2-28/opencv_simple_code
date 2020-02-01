// bianyuanjiance.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
int main()
{
    Mat srcImage = imread("1.jpg");
    imshow("原图", srcImage);
    Mat dstImage, edge, grayImage;
    dstImage.create(srcImage.size(), srcImage.type());//创造与src类型和大小相同的矩阵；
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);//将原图像转换为灰度图像
    blur(grayImage, edge, Size(3, 3));//使用3*3内核来降噪
    Canny(edge, edge, 3, 9, 3);
    imshow("canny边缘检测", edge);//运行canny算子
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
