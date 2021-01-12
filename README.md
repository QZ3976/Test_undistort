# 单目鱼眼去畸变汇总
## 前期配置
### 依赖
* opencv2中没有鱼眼模型，opencv3中才加入Fisheye camera model by Ilya Krylov
### 修改文件
* 内参
* 是否是鱼眼相机(#define Fisheye)
## 编译和运行
### 编译
~~~shell
mkdir build
cd build
cmake ..
make -j4
~~~
### 运行
~~~shell
./main ../data/XXX.jpg
~~~
## 整理

* 感觉最靠谱的办法就是用函数，在鱼眼相机里用cv::fisheye::undistortImage，在普通相机里面用这个cv::undistortImage