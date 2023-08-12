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

class videothread;//�����ȡ����ͷ��Ϣ���������̴߳���������ͷͼ��
class four;//���𴴽�ui����ʾͼ��



class four : public QMainWindow
{
	Q_OBJECT

public:
	four(QWidget* parent = Q_NULLPTR);//����Ϊ���㴰��

private:
	Ui::fourClass ui;
	/* Ϊ����graphview����ʾͼƬ����Ҫ����QGraphicsScene����
	 * ����ֻ��ʾ��������ͷ����Ƶ�����ֻ��������QGraphicsScene���������graphview�ؼ�����ʹ��ͬһ��QGraphicsScene�������������ʾ������
	 * ������Щʾ���������ڳ�Ա�����д������������������������ʾ��Ƶʱ����Ҫѭ��ִ����ʾͼ��Ĵ��룬���ϵ�new�ᵼ�³������
	 */
	QGraphicsScene* scene_1 = new QGraphicsScene;
	QGraphicsScene* scene_2 = new QGraphicsScene;
	bool reset = false;

public slots:
	void show_image_1(QImage dstImage);  //�ֱ�������graphview����ʾͼ��
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
	void run();   //qt���߳�����Ҫ����run����
	/*
	 * ���߳����е�run�������������̵߳�main������
	 * ���紴�����߳������videothread th1;   th1.start()֮����Զ���ʼִ��run����
	 */

private:
	int cam;     //������ͷ������
	int order;	
	VideoWriter* writer;
	bool record_flag = false;
	bool flip_flag = false;

public slots:
	void flipmat();
	void openrecord();
	void endrecord();

signals:
	/* ʹ�ö��߳̿���ͬʱ��ȡ��������ͷ��ͼ��
	 * �����ڽ�����ʾ��ʱ����Ҫ�ٿ�UI�����еĿؼ���Ȼ����һ�������������߳���ִ��
	 * ����֮�����̲߳��ܶ�UI����Ŀؼ������޸�
	 * ����취�ǵ����̶߳�ȡͼ���Ժ������̷߳����źţ����ҽ�ͼ�����ݴ��͹�ȥ��Ȼ�������߳��еĲۺ���ִ����ʾͼ��ĺ���
	 */
	int signal_tomainthread(QImage dstImage);

};



QImage cvMat2QImage(const Mat& mat);   //opencv��Mat��������ת��Ϊqt��QImage��������
