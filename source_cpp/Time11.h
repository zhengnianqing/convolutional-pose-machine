#pragma once

#include <QObject>
#include <opencv2/opencv.hpp>
using namespace cv;

class Time11 : public QObject
{
	Q_OBJECT

public:
	Time11(QObject *parent);
	~Time11();
	Time11(){};

	public slots:
	void run();
	//void main_slot(Mat &img, int method);

private:

signals :
	void notify(int);
    void progress_signal(int);
};
