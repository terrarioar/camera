#pragma once

#include <QtWidgets/QMainWindow>
#include <QtGui/QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ui_four.h"
#include "video.h"
#include <QThread>
#include <QDebug>

using namespace std;
using namespace cv;

class videothread;//负责读取摄像头信息，接受子线程传来的摄像头图像
class four;//负责创建ui，显示图像



class four : public QMainWindow
{
	Q_OBJECT

public:
	four(QWidget* parent = Q_NULLPTR);//设置为顶层窗口

private:
	Ui::fourClass ui;
	/* 为了在graphview中显示图片，需要创建QGraphicsScene变量
	 * 这里只显示两个摄像头的视频，因此只创建两个QGraphicsScene变量；多个graphview控件不能使用同一个QGraphicsScene变量，否则会显示不正常
	 * 网上有些示例代码是在成员方法中创建这个变量，但是由于在显示视频时，需要循环执行显示图像的代码，不断地new会导致程序崩溃
	 */
	QGraphicsScene* scene_1 = new QGraphicsScene;
	QGraphicsScene* scene_2 = new QGraphicsScene;
	bool reset = false;

public slots:
	void show_image_1(QImage dstImage);  //分别在两个graphview中显示图像
	void show_image_2(QImage dstImage);
	void on_rstpushbutton_clicked();
	void on_flippushbutton_clicked();
	void on_openpushbutton_clicked();
	void on_closepushbutton_clicked();

signals:
	int signal_flip_1();
	int signal_flip_2();
	int signal_openrecord_1();
	int signal_openrecord_2();
	int signal_endrecord_1();
	int signal_endrecord_2();
};



class videothread : public QThread
{
	Q_OBJECT

public:
	videothread(int cam, int order);
	~videothread();
	void run();   //qt多线程类需要重载run函数
	/*
	 * 多线程类中的run函数类似于主线程的main函数，
	 * 例如创建多线程类对象：videothread th1;   th1.start()之后便自动开始执行run函数
	 */

private:
	int cam;     //打开摄像头的索引
	int order;	
	VideoWriter* writer;
	bool record_flag = false;
	bool flip_flag = false;

public slots:
	void flipmat();
	void openrecord();
	void endrecord();

signals:
	/* 使用多线程可以同时读取两个摄像头的图像
	 * 但是在进行显示的时候需要操控UI界面中的控件，然而这一操作必须在主线程里执行
	 * 换言之，子线程不能对UI界面的控件进行修改
	 * 解决办法是当子线程读取图像以后，向主线程发送信号，并且将图像数据传送过去，然后由主线程中的槽函数执行显示图像的函数
	 */
	int signal_tomainthread(QImage dstImage);

};



QImage cvMat2QImage(const Mat& mat);   //opencv的Mat数据类型转换为qt的QImage数据类型
