#include "four.h"
#include "video.h"
#include <iostream>
#include <time.h>
using namespace std;


QImage cvMat2QImage(const cv::Mat& mat)//opencv��Mat��������ת��Ϊqt��QImage��������
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar* pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar* pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		pSrc = 0;
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar* pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		pSrc = 0;
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		// Copy input Mat
		const uchar* pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		pSrc = 0;
		return image.copy();
	}
	else
	{
		return QImage();
	}
}

//���߳�
four::four(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/* ��UI����Ĺ��캯���д������̶߳���ÿһ�������ʾһ���̣߳�
	 * ֮�����Ӷ��̶߳�����źź�UI���еĲۺ���
	 * ���start()�������߳�
	 */
	videothread* th1 = new videothread(1, 1);    //���������ָ�룬�����캯��ִ������Ժ�ͻ�Ѿֲ�����ɾ��
	QObject::connect(th1, SIGNAL(signal_tomainthread(QImage)),
		this, SLOT(show_image_1(QImage)));
	QObject::connect(this, SIGNAL(signal_flip_1()),
		th1, SLOT(flipmat()));
	QObject::connect(this, SIGNAL(signal_openrecord_1()),
		th1, SLOT(openrecord()));
	QObject::connect(this, SIGNAL(signal_endrecord_1()),
		th1, SLOT(endrecord()));
	th1->start();

	videothread* th2 = new videothread(2, 0);    //���������ָ�룬�����캯��ִ������Ժ�ͻ�Ѿֲ�����ɾ��
	QObject::connect(th2, SIGNAL(signal_tomainthread(QImage)),
		this, SLOT(show_image_2(QImage)));
	QObject::connect(this, SIGNAL(signal_flip_2()),
		th2, SLOT(flipmat()));
	QObject::connect(this, SIGNAL(signal_openrecord_2()),
		th2, SLOT(openrecord()));
	QObject::connect(this, SIGNAL(signal_endrecord_2()),
		th2, SLOT(endrecord()));
	th2->start();
}

void four::on_rstpushbutton_clicked()
{
	reset = !reset;
}

void four::on_flippushbutton_clicked()
{
	emit signal_flip_1();
	emit signal_flip_2();
}

void four::on_openpushbutton_clicked()
{
	emit signal_openrecord_1();
	emit signal_openrecord_2();
	ui.openpushbutton->setStyleSheet("color: rgb(255, 0, 0)");

	//������ɫ�������
}

void four::on_closepushbutton_clicked()
{
	emit signal_endrecord_1();
	emit signal_endrecord_2();
	ui.openpushbutton->setStyleSheet("color: rgb(0, 0, 0)");
}


void four::show_image_1(QImage dstImage)
{
	dstImage = dstImage.scaled(600, 340, Qt::KeepAspectRatio, Qt::SmoothTransformation);//����16:9  ����������
	scene_1->clear();   //���scene_1�����ݣ�����addPixmap�ᵼ��scene_1ռ�õ��ڴ�Խ��Խ��
	scene_1->addPixmap(QPixmap::fromImage(dstImage));//QImage->QPixmap
	if (!reset) {
		ui.graphicsView->setScene(scene_1);
		ui.graphicsView->resize(scene_1->width() + 3, scene_1->height() + 3);//������С����
		ui.graphicsView->show();
	}
	else {
		ui.graphicsView_2->setScene(scene_1);
		ui.graphicsView_2->resize(scene_1->width() + 3, scene_1->height() + 3);//������С����
		ui.graphicsView_2->show();
	}
}


void four::show_image_2(QImage dstImage)
{
	dstImage = dstImage.scaled(600, 340, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	scene_2->clear();
	scene_2->addPixmap(QPixmap::fromImage(dstImage));
	if (!reset) {
		ui.graphicsView_2->setScene(scene_2);
		ui.graphicsView_2->resize(scene_2->width() + 3, scene_2->height() + 3);
		ui.graphicsView_2->show();
	}
	else {
		ui.graphicsView->setScene(scene_2);
		ui.graphicsView->resize(scene_2->width() + 3, scene_2->height() + 3);
		ui.graphicsView->show();
	}
}

void videothread::flipmat() 
{
	flip_flag = !flip_flag;
}


void videothread::openrecord()
{
	if (record_flag == false) {

		time_t timep;
		struct tm* p;
		char name[256] = { 0 };//��ϵͳʱ����ص��ļ���
		time(&timep);//��ȡ��1970������˶����룬����time_t���͵�timep
		p = localtime(&timep);//��localtime������ת��Ϊstruct tm�ṹ��
		sprintf(name, "%d_rec-%d-%d-%d %02d-%02d-%02d.avi", cam , 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min,p->tm_sec);
		
		writer = new VideoWriter;
		writer->open( name, VideoWriter::fourcc('M', 'P', '4', '2'), 15, Size(1280, 720), true);
		qDebug() << cam << QString::fromLocal8Bit("���ڿ�ʼ¼��");
		record_flag = true;
	}
}


void videothread::endrecord()
{
	if (record_flag == true) {
		record_flag = false;
		msleep(50);
		writer->release();
		delete writer;
		qDebug() << cam << QString::fromLocal8Bit("���ڽ���¼��");
	}
}


videothread::videothread(int cam, int order)
{
	this->cam = cam;
	this->order = order;
}


videothread::~videothread()
{
}


void videothread::run()//���߳�
{
	Camera frame;
	frame.setcam(cam);    //��ȡ����ͷ������
	frame.open_camera();	//������ͷ
	if (!frame.isopened())
	{
		frame.setcam(order);    //��ȡ����ͷ������
		frame.open_camera();
	}
	while (1)     //���߳̽�����ѭ�������ϵض�ȡͼ�񲢷����ź�
	{
		Mat srcImage = frame.read_frame();
		if (flip_flag == true) flip(srcImage, srcImage, -1);
		if (record_flag == true) writer->write(srcImage);
		QImage dstImage = cvMat2QImage(srcImage);
		qDebug() << QString::fromLocal8Bit("����ͷ������") << cam << QString::fromLocal8Bit("�ֱ���") << srcImage.cols << srcImage.rows << QString::fromLocal8Bit("֡��") << frame.nFps;//�ֱ���1280*720
		emit signal_tomainthread(dstImage);
		msleep(33);//����ͷ֡��
	}
}
