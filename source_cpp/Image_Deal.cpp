#include"Image_Deal.h"
#include"iostream"
#include"fstream"
#include"Param.h"
#include"caffe.h"
#include"math.h"

using namespace caffe;  // NOLINT(build/namespaces)
Cordinate Predeal(Mat src,Mat&dist)//图像的大小是8的倍数
{
	Cordinate PP = { 0, 0 };
	if (src.rows % 8 == 0 && src.cols % 8 == 0)
	{
		dist = src;
		return PP;
	}
	int _rows = src.rows /8;
	int _cols = src.cols /8;  
	if (src.rows % 8 != 0)   //计算出来图像的填充后的尺寸
	{
		_rows = _rows * 8 + 8;
		PP.y = _rows - src.rows;
	}
	else
		_rows = src.rows;
	if (src.cols % 8 != 0)
	{
		_cols = _cols * 8 + 8;
		PP.x = _cols - src.cols;
	}
	else
		_cols = src.cols;

	Mat M(_rows, _cols, CV_8UC3, Scalar(0,0,0));
	for (int i = 0; i < _rows; i++)  //进行128的填充
	{
		uchar *P = M.ptr<uchar>(_rows);
		for (int j = 0; j < _cols; j++)
		{
			Vec3b &p1 = M.at<Vec3b>(i, j);
			p1[0] = 128;
			p1[1] = 128;
			p1[2] = 128;
			if (i < src.rows&&j < src.cols)
			{
				Vec3b &p = src.at<Vec3b>(i, j);
				p1[0] = p[0];
				p1[1] = p[1]; 
				p1[2] = p[2];
			}
		}
	}
	cout <<M.rows << " " << M.cols << endl;
	dist = M;
	return PP;//返回图像在x或者y方向上填补的像素个数
}
std::vector<cv::Mat> Get_Single(std::vector<Cordinate> zuobiao,cv::Mat dist)
{
	std::vector<cv::Mat> mt;
	for (int kk = 0; kk < zuobiao.size(); kk++)
	{
		cv::Mat Center(cv::Size(boxsize_1, boxsize_1), CV_8UC3, Scalar(128, 128, 128));
		for (int i = 0; i < boxsize_1; i++)
		{
			for (int j = 0; j < boxsize_1; j++)
			{
				int x_1 = j - boxsize_1 / 2 + zuobiao[kk].x;
				int y_1 = i - boxsize_1 / 2 + zuobiao[kk].y;  //进行相应的坐标位移
				if (x_1 >= 0 && x_1 < dist.cols&&y_1 >= 0 && y_1 < dist.rows)
				{
					cv::Vec3b &p = dist.at<Vec3b>(y_1, x_1);
					Vec3b &p1 = Center.at<Vec3b>(i, j);
					p1[0] = p[0]; p1[1] = p[1]; p1[2] = p[2];
				}
			}
		}
		//imshow("Img",Center);
		//cvWaitKey(0);
		mt.push_back(Center.clone());
	}
	return mt;
}


Prece  Pre_Process(cv::Mat&img1)
{
	Prece infor;  
	cv::Mat img = img1;
	double Scale = boxsize_1 / (double)img.rows;
	Mat Dst;
	cv::resize(img, Dst, Size(Scale*img.cols, Scale*img.rows), (0, 0), (0, 0), cv::INTER_LINEAR);  //将图像的行缩放到368，列同比例缩放
	Mat dist;
	Cordinate tianbu=Predeal(Dst, dist);//为了适应网络的尺寸需要，将图像进行填充到8的倍数，填充的值128  
	img1 = dist;
	infor.scale = Scale;  //
	infor.Pad = tianbu;
	cout << img1.rows << " "<<img1.cols << endl;
	return infor;
}

Stage_infor Get_Person(cv::Mat dist)
{
	string model_file = "_trained_person_MPI/pose_deploy_copy_4sg_resize.prototxt";;
	string trained_file = "_trained_person_MPI/pose_iter_70000.caffemodel";
	string mean_file = "_trained_person_MPI/mean.binaryproto";
	string label_file = "_trained_person_MPI/label_1.txt";
	Classifier classifier(model_file, trained_file, mean_file, label_file);  //建立模型，加载网络以及模型文件
	cout << dist.rows << " " << dist.cols << endl;
	CHECK(!dist.empty()) << "Unable to decode image ";
	Stage_infor infor;
	Mat img1 = dist.clone();
	std::vector<Point> predictions = classifier.Classify(img1, 1);
	std::vector<Cordinate> zuobiao = classifier.Get_Person(); //获取图像中人体的位置坐标。
	std::vector<cv::Mat> Img_Single = Get_Single(zuobiao, img1);//获取以每个人为图像中心的图像组
	infor.Cor = zuobiao;
	infor.All_Person = Img_Single;
	return infor;
}

cv::Mat Gauss_Img()//生成一个服从高斯分布的图像
{
	cv::Mat img(Size(boxsize_1,boxsize_1),CV_32FC1,Scalar(0));
	for (int i = 0; i < boxsize_1; i++)
	{
		float *P = img.ptr<float>(i);
		for (int j = 0; j < boxsize_1; j++)
		{
			float dist_1 = (i - 368/2.0)*(i-368/2.0) + (j -368/2.0)*(j - 368/2.0);
			float exponent = dist_1/2.0/21.0/21.0;
			P[j] = expf(-exponent);
		}
	}
	//cv::Mat img2;
	//img.convertTo(img2, CV_8U);
	imshow("Gauss", img);
	cvWaitKey(0);
	//cv::Mat img1(Size(boxsize_1,boxsize_1),CV_32FC1);
	//img1 = img * 256;
	//img1.convertTo(img1, CV_8U);//仅仅是为了显示
	return img;
}
void lianjie(Point A, Point B, cv::Mat img)
{
	;
}
float dist(Point A,Point B)
{
	return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}
void huaxian(Point dd, Point ee,Mat img_pre,Scalar bb)
{
	float dd1 = dist(dd,ee);
	float dd2 = dd1 / 10;
	if (dd2 <=4)
		dd2 = 4;
	else if (dd2>=7)
		dd2 = 7;
	float angle = atan2(dd.y-ee.y,dd.x-ee.x)*180/3.1416;
	ellipse(img_pre, Point((dd.x + ee.x) / 2, (dd.y + ee.y) / 2), Size(dd1*0.6,dd2),angle, 0, 360, bb,-1);
}
void Produce_Img(std::vector<cv::Mat>Img_1, cv::Mat&img_pre, std::vector<Cordinate> Cor, Prece  Xinxi)
{
	//cv::Mat mt(Size(boxsize_1,boxsize_1),CV_32FC3,Scalar(128,128,128));
	string model_file = "_trained_MPI/pose_deploy_resize.prototxt";
	string trained_file = "_trained_MPI/pose_iter_320000.caffemodel";
	string mean_file = "_trained_MPI/mean.binaryproto";
	string label_file = "_trained_MPI/label_2.txt";
	Classifier classifier(model_file, trained_file, mean_file, label_file);   //加载第二阶段网络模型
	std::vector<Point> predictions;
	for (int kk = 0; kk < Img_1.size(); kk++)
	{
		predictions = classifier.Classify(Img_1[kk], 2);  //网络第二阶段预测位置
		for (int j = 0; j < predictions.size(); j++)
		{
			cv::circle(Img_1[kk], predictions[j], 3, CV_RGB(255,0, 255), -1);//换算到原图中的关节点的坐标
			predictions[j].x = predictions[j].x + Cor[kk].x - boxsize_1 / 2;
		    predictions[j].y = predictions[j].y + Cor[kk].y - boxsize_1 / 2;
			cv::circle(img_pre,predictions[j], 3, CV_RGB(255, 0, 255), -1); //在原预处理后的图像中，人体关节点的标注
		}
		 //在原预处理后的图像中，人体骨架直线标注出来
		huaxian(predictions[0],predictions[1],img_pre,Scalar(0,0,255));
		huaxian(predictions[2], predictions[3], img_pre,Scalar(0,170,255));
		huaxian(predictions[3], predictions[4], img_pre,Scalar(0,255,170));
		huaxian(predictions[5], predictions[6], img_pre,Scalar(0,255,0));
		huaxian(predictions[6], predictions[7], img_pre, Scalar(170, 255, 0));
		huaxian(predictions[8], predictions[9], img_pre,Scalar(255,170,0));
		huaxian(predictions[9], predictions[10], img_pre, Scalar(255, 0, 0));
		huaxian(predictions[11], predictions[12], img_pre, Scalar(255, 0, 170));
		huaxian(predictions[12], predictions[13], img_pre, Scalar(170, 0, 255));
	}
	cv::Mat Huifu;
	cv::resize(img_pre, img_pre, Size(1 / Xinxi.scale*img_pre.cols, 1 / Xinxi.scale*img_pre.rows), (0, 0), (0, 0), cv::INTER_CUBIC);  //标注后的图像在三次插值回去
	//imshow("img_1", img_pre);
	//imwrite("im.jpg",img_pre);
	//return img_pre;
}

int Test(cv::Mat&image,Prece&Xinxi,Stage_infor&infor)
{
	Xinxi = Pre_Process(image);  //图像的预处理
	infor = Get_Person(image);//获取人的原始位置坐标,以及将每个人得中心移动到图像的中心得到的图像组。
	if (infor.All_Person.size() == 0)
		return 0;
	else
		return 1;
	//Mat Gauss = Gauss_Img();  //生成一个服从高斯分布的图像 
	//Produce_Img(infor.All_Person, image, infor.Cor, Xinxi);//将每个人的中心图像，以及相应的位置偏移第二阶段
	return 1;
}

int Test_2(cv::Mat&image,Prece&Xinxi,Stage_infor&infor)
{
	Produce_Img(infor.All_Person, image, infor.Cor, Xinxi);//将每个人的中心图像，以及相应的位置偏移第二阶段
	return 1;
}