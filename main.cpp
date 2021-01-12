/**
 * @file main.cpp
 * @author qiaozhi
 * @brief 单目鱼眼去畸变汇总
 * @version 0.1
 * @date 2021-01-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define Fisheye 1

const cv::Mat K_Mono = ( cv::Mat_<double> ( 3,3 ) << 4.3314243968057526e+03, 0.0, 9.6887761607704590e+02, 0.0, 4.3314243968057526e+03, 6.0268606501173008e+02, 0.0, 0.0, 1.0 );
const cv::Mat D_Mono = ( cv::Mat_<double> ( 5,1 ) << -3.6867325129092227e-01, 2.1827369075900904e+00, -8.2969570265312739e-04, -2.7807433953931783e-03, -2.0472769671254049e+01 );

const cv::Mat K_Fisheye = ( cv::Mat_<double> ( 3,3 ) << 1.2213951277776025e+03, 0.0, 9.5519121506532645e+02, 0.0, 1.2198611901155975e+03, 6.1108405173100266e+02, 0.0, 0.0, 1.0 );
const cv::Mat D_Fisheye = ( cv::Mat_<double> ( 4,1 ) << -4.0650897242570684e-02, -6.8399259515275729e-02, 3.5311546536889055e-01, -4.8494996200733836e-01 );


// 鱼眼相机去畸变
Mat Test_Fisheye_Undistort(const string &Image_Path );
// 单目相机去畸变
Mat Test_Mono_Undistort(const string &Image_Path );


int main(int argc, char**argv)
{
    if(argc != 2)
    {
        cout << endl << "Usage: ./main path_to_image" << endl;
        return 1;
    }
    
    string InputPath = string(argv[1]);
    // cout << InputPath<<endl;
#if Fisheye
    cv::Mat result = Test_Fisheye_Undistort(InputPath);
    // cv::imshow("result", result);
    // waitkey(0);
    cv::imwrite("../data/result.jpg", result);
#else
    // 单目
    cv::Mat result = Test_Mono_Undistort(InputPath);
    // cv::imshow("result", result);
    // waitkey(0);
    cv::imwrite("../data/result.jpg", result);
#endif
	return 0;
}

Mat Test_Fisheye_Undistort(const string &Image_Path){
    
    Mat Raw_Image = cv::imread(Image_Path);
    
    Mat Undistort_Image;
    Mat result;
    Mat mapx;
    Mat mapy;
    // Mat mapx = Mat(Raw_Image.size(), CV_32FC1);
    // Mat mapy = Mat(Raw_Image.size(), CV_32FC1);
    // Mat R = Mat::eye(3, 3, CV_32F); // Mat(),这个不同的值对他影响是？
    // const double alpha = 1;
    // cv::Mat New_Camera_Matrix = getOptimalNewCameraMatrix(K_Fisheye, D_Fisheye, Raw_Image.size(), alpha, Raw_Image.size(), 0);// 一般这个函数也不用,鱼眼就没有这个函数
    // 方法一
    // cv::fisheye::initUndistortRectifyMap(K_Fisheye, D_Fisheye, Mat(), K_Fisheye, Raw_Image.size(), CV_32FC1, mapx, mapy);
    // cv::remap(Raw_Image, Undistort_Image, mapx, mapy, INTER_LINEAR);
    // 方法二
    fisheye::undistortImage(Raw_Image, Undistort_Image, K_Fisheye, D_Fisheye, K_Fisheye);//New_Camera_Matrix 用了他就不对了
    cv::hconcat(Raw_Image,Undistort_Image,result);
    
    return result;

}


Mat Test_Mono_Undistort(const string &Image_Path ){    
    Mat Raw_Image = cv::imread(Image_Path);
    
    Mat Undistort_Image, result;
    Mat mapx, mapy;

    const double alpha = 1;
    cv::Mat New_Camera_Matrix = getOptimalNewCameraMatrix(K_Mono, D_Mono, Raw_Image.size(), alpha, Raw_Image.size(), 0);
    // 方法一
    // initUndistortRectifyMap(K_Mono, D_Mono, Mat(), New_Camera_Matrix, Raw_Image.size(), CV_32FC1, mapx, mapy);
    // cv::remap(Raw_Image, Undistort_Image, mapx, mapy, INTER_LINEAR);
    // 方法二
    cv::undistort(Raw_Image, Undistort_Image, K_Mono, D_Mono, K_Mono );// New_Camera_Matrix
    cv::hconcat(Raw_Image,Undistort_Image,result);
    
    return result;

}