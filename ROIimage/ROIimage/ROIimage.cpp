// ROIimage.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();


int main() {
    system("color 6F");
    if (ROI_AddImage()&& LinearBlending()&& ROI_LinearBlending())
    {
        cout << endl << "\n运行成功，得出了需要的图像";
    }

    waitKey(0);
    return 0;
}

bool ROI_AddImage()
{
    Mat srcImage1 = imread("kobe.jpg");
    Mat logoImage = imread("logo.jpg");
    if (!srcImage1.data) { printf("读取srcImage1错误~！\n"); return false; }
    if (!logoImage.data) { printf("读取logoImage错误~！\n"); return false; }

    Mat imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));

    //加载掩膜（必须是灰度图）
    Mat mask = imread("logo.jpg", 0);
    //将掩膜拷贝到ROI
    logoImage.copyTo(imageROI, mask);
    namedWindow("<1>利用ROI实现图像叠加示例窗口");
    imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);
    return true;

}

bool LinearBlending()
{
    double alphaValue = 0.5;
    double betaValue;
    Mat srcImage2, srcImage3, dstImage;
    srcImage2 = imread("1.jpg");
    srcImage3 = imread("2.jpg");

    if (!srcImage2.data) { printf("读取srcImage2错误！ \n"); return false; }
    if (!srcImage3.data) { printf("读取srcImage3错误！ \n"); return false; }

    betaValue = (1.0 - alphaValue);
    addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

    namedWindow("<2>线性混合示例窗口【原图】");
    imshow("<2>线性混合示例窗口【原图】", srcImage2);

    namedWindow("<3>线性混合示例窗口【效果图】");
    imshow("<3>线性混合示例窗口【效果图】", dstImage);

    return true;
}

bool ROI_LinearBlending()
{
    Mat srcImage4 = imread("kobe.jpg", 1);
    Mat logoImage = imread("logo.jpg");

    if (!srcImage4.data) { printf("读取srcImage4错误~！ \n"); return false; }
    if (!logoImage.data) { printf("读取logoImage错误~！ \n"); return false; }

    Mat imageROI;
    imageROI = srcImage4(Rect(200, 250, logoImage.cols, logoImage.rows));

    addWeighted(imageROI, 0.5, logoImage, 0.3, 0.0, imageROI);

    namedWindow("<4>区域线性图像混合示例窗口");
    imshow("<4>区域线性图像混合示例窗口", srcImage4);

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
