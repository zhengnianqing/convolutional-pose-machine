#include "pose_re.h"
#include"QFileDialog"
#include"QMessageBox"
#include "iostream"
#include"QThread.h"
#include"Param.h"
#include"Base.h"
#include"Image_Deal.h"
#include <string>
//#include <QtCore>
#include <QMetaType>

//#include "ThreadFromQThread.h"
Mat QImage2cvMat(QImage image);
QImage cvMat2QImage(const cv::Mat& mat);


Pose_Re::Pose_Re(QWidget *parent)
	: QMainWindow(parent)
{
	this->setFixedSize(1200, 720);
	ui.setupUi(this);
	
	ui.label->setFrameStyle(QFrame::Panel | QFrame::Sunken); //设置外观  
	ui.label->setGeometry(QRect(50, 50, 700, 500));
	ui.label->setText("Premary");
	ui.progressBar->setGeometry(QRect(50, 600, 750, 30));
	ui.textBrowser->setGeometry(QRect(900, 50, 250, 481));
	Innit_menue();
	InitToolBar();
	ui.progressBar->setRange(0, 100);
	ui.progressBar->setValue(0);
	
	value = 3;
	qRegisterMetaType< cv::Mat >("cv::Mat");
	connect(fileOpenAction, &QAction::triggered, this, &Pose_Re::Open_Picture);//槽函数，触发消息
	//connect(this, SIGNAL(stop_time(int)), this, SLOT(receive_message(int)));
	thread_1 = NULL;
	timer = new QTimer(this);
	//关联定时器计满信号和相应的槽函数。
	
	//func1 = NULL;
	connect(timer, &QTimer::timeout, this, &Pose_Re::receive_message);
	//timer->start(1000);
	
	//m_heart.setInterval(100);
	//全局线程的创建
	//
	//connect(m_thread, &ThreadFromQThread::progress
	//	, this, &Widget::progress);
	//connect(m_thread, &QThread::finished
	//	, this, &Widget::onQThreadFinished);
}

Pose_Re::~Pose_Re()
{
  
}
void Pose_Re::testFunction()
{
	/*value++;
	ui.progressBar->setValue(value);
	if (value == 100)
		value = 0;*/
}
void Pose_Re::receive_message()
{
	ui.progressBar->setValue(value);
	value++;
	if (value == 100)
		value = 0;
}

void Pose_Re::Begin_Test()
{
	if (Image.empty())
	{
		QMessageBox::information(this, tr("Error!"), tr("Open Image first!!"));
		return;
	}
	QMessageBox::information(this, tr("Good"), tr("Good"));
	//ui.textBrowser->setPlainText("");
	ui.textBrowser->append("*********Detect persons*********");
	if (Image.channels() == 3 || Image.channels() == 1)
	{
		timer->start(100);
		//if (thread_1==NULL)
		thread_1 = new xiancheng(this);
		connect(this, SIGNAL(send_image(cv::Mat)), thread_1, SLOT(receive_image(cv::Mat)));
		connect(thread_1, SIGNAL(transmit(cv::Mat,int)),this,SLOT(shuaxin(cv::Mat,int)));
		emit send_image(Image);
		if (!thread_1->isRunning())
		thread_1->start();
	}
}

void Pose_Re::shuaxin(cv::Mat return_Image,int num)
{
	Image = return_Image;
	QString num1 = QString::number(num, 10);
	ui.textBrowser->append("People numbers:" + num1);
	QImage im = cvMat2QImage(return_Image);
	im = im.scaled(ui.label->width(), ui.label->height());
	ui.label->setPixmap(QPixmap::fromImage(im));
	thread_1->quit();
	
	if (thread_1 != NULL)
		delete thread_1;
	value = 0;
	//_sleep(3);
	timer->stop();
}

void Pose_Re::Stop_Systeam()
{
	exit(0);
}

void Pose_Re::Save_Result()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save  "), "", tr("Config Files (*.png)"));
	//qDebug() << fileName;
	if (fileName.isNull())
		return;
	string str = fileName.toStdString();
	imwrite(str, Image);
}

void Pose_Re::Open_Picture()
{
	QString filename11;
	filename11 = QFileDialog::getOpenFileName(this,
		tr("选择图像"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	filename = filename11;
	if (filename11.isEmpty())
		return;
	else
	{
		string path = filename.toStdString();
		Mat Image_1= imread(path);
		Image = Image_1;
		if (Image_1.empty())   //加载图像
		{
			QMessageBox::information(this,
				tr("打开图像失败"),
				tr("打开图像失败!"));
			return;
		}
		float room = (float)480/(float)Image_1.rows;
		float room_1 = (float)800/(float)Image_1.cols;
		room = (room < room_1) ? room : room_1;
		int weizhi = 360-Image_1.rows*room*0.5-30;
		int weizhi_1 = 450 - Image_1.cols*room*0.5;
		weizhi = (weizhi>50) ? weizhi : 50;
		ui.label->setGeometry(QRect(weizhi_1,weizhi, 700, 500));
		QImage qimg= cvMat2QImage(Image_1);
		qimg = qimg.scaled(Image_1.cols*room, Image_1.rows*room);
		ui.label->resize(Image_1.cols*room, Image_1.rows*room);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
		ui.textBrowser->setGeometry(QRect(900, weizhi, 250, 481));
	}
	ui.textBrowser->setPlainText("");
	ui.textBrowser->append("********Image*******");
	QString str_cols =QString::number(Image.cols, 10);
	QString str_rows = QString::number(Image.rows, 10);
	ui.textBrowser->append("Image_height:  "+str_rows);
	ui.textBrowser->append("Image_width:  "+str_cols);
}

void Pose_Re::Innit_menue()
{
	//创建菜单栏菜单的思路就是先创建action然后创建菜单然后将菜单加到Menuebar中
	fileMenu = new QMenu(tr("File"), this);
	fileOpenAction = new QAction("&Open...", this);//下拉菜单相当于action
	fileOpenAction->setShortcuts(QKeySequence::Open);
	fileOpenAction->setStatusTip(tr("Open an existing file"));
	//fileSaveAction = new QAction("&Save...", this);
	fileMenu->addAction(fileOpenAction);
	//fileMenu->addAction(fileSaveAction);
	/* 初始化Edit菜单 */
	//editCutAction=editMenu->addAction("&Cut");
	/* 将菜单添加到菜单栏上 */
	QMenuBar *menuBar = this->menuBar();
	menuBar->addMenu(fileMenu);
}


void Pose_Re::InitToolBar()
{
	/* 初始化FileToolBar */
	fileToolBar = new QToolBar(this);
	fileToolBar->addAction(fileOpenAction);
	fileToolBar->addAction(fileSaveAction);
	/*初始化EditToolBar */
	/* 将工具添加到工具栏上 */
	addToolBar(Qt::TopToolBarArea, fileToolBar);
}

Mat QImage2cvMat(QImage image)
{
	cv::Mat mat;
	cout << image.format()<<endl;
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
	    mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}
QImage cvMat2QImage(const cv::Mat& mat)
{
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
			image.setColor(i, qRgb(i, i, i));
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	else if (mat.type() == CV_8UC3)
	{
		const uchar *pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		const uchar *pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		//qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}
