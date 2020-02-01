// videocanny.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    VideoCapture capture(0);
    Mat edges;
    while (1)
    {
        Mat frame;
        capture >> frame;//读取当前帧
        cvtColor(frame, edges, COLOR_BGR2GRAY);//将原图像转换为灰度图像
        blur(edges, edges, Size(7, 7));//使用3*3内核来降噪
        Canny(edges, edges, 0, 30, 3);
        imshow("被canny后的视频", edges);
        if(waitKey(30)>=0) break;
    }
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
