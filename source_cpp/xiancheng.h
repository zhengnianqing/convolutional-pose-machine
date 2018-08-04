#ifndef XIANCHENG_H
#define XIANCHENG_H
#include"Image_Deal.h"
#include <QThread.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

class xiancheng : public QThread
{
	Q_OBJECT 
	void run();
public:
	xiancheng(QObject *parent);
	~xiancheng();
signals:
	void transmit(cv::Mat img,int num);
public slots:
void receive_image(cv::Mat);
private:
	cv::Mat Image;
};

#endif // XIANCHENG_H
