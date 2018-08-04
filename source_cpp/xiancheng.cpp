#include "xiancheng.h"

xiancheng::xiancheng(QObject *parent)
	: QThread(parent)
{

}

xiancheng::~xiancheng()
{

}

void xiancheng::receive_image(cv::Mat img)
{
	Image = img;
}
void xiancheng::run()
{
	Prece xinxi;
	Stage_infor infor;
	if (Image.empty())
		return;
	int Rool = Test(Image, xinxi, infor);
	QString str;
	if (!Rool)
	{
		QString num = QString::number(0, 10);
		str = "Person Numbers    : " + num;
		return;
	}
	else
	{
		QString num = QString::number(infor.All_Person.size(), 10);
		QString str = "Person Numbers    : " + num;
		//ui.textBrowser->append(str);
	}
	//ui.textBrowser->append("*********Recognise person pose*********");
	Rool = Test_2(Image, xinxi, infor);
	//imshow("Image", Image);
	cv::Mat image = Image.clone();
	//cvWaitKey(0);
	if (Rool)
	emit transmit(image,infor.All_Person.size());
}