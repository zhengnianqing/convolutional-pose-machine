#ifndef POSE_RE_H
#define POSE_RE_H

#include <QtWidgets/QMainWindow>
#include"QTimer.h"
#include "ui_pose_re.h"
#include"xiancheng.h"

#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif  // USE_OPENCV


class Pose_Re : public QMainWindow
{
	Q_OBJECT

public:
	Pose_Re(QWidget *parent = 0);
	void Innit_menue();
	void InitToolBar();
	~Pose_Re();
public slots:
   void Open_Picture();
   void Begin_Test();
   void Stop_Systeam();
   void testFunction();
   void Save_Result();
   void receive_message();
   void shuaxin(cv::Mat return_Image,int num);      
signals:
   void send_image(cv::Mat);
  // void stop_time(int flag);
private:
	QToolBar *fileToolBar;
	QMenu *fileMenu;
	QAction *fileOpenAction;
	QAction *fileSaveAction;
	
	Ui::Pose_ReClass ui;
	QString filename;
	cv::Mat Image;
	int value;
	QTimer *timer;
	//ThreadFrom *m_thread;
	xiancheng *thread_1;
	//ThreadFunction* func1;
};

#endif // POSE_RE_H
