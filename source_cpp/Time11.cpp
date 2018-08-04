#include "Time11.h"

Time11::Time11(QObject *parent)
: QObject(parent)
{

}

Time11::~Time11()
{
}


void Time11::run()
{
	int Value = 0;
	while (Value < 100)
	{
		for (long j = 0; j < 1000000000000; j++)
		{
			long i = 10000000000000000;
			while (i--);
		}
		++Value;
		emit notify(Value);
		//emit progress_signal(Value);
	}
}

//void Time11::main_slot(Mat &img, int method)
//{
//	cv::imshow("src", img);
//	cv::waitKey();
//}