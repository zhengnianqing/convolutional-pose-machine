#ifndef IMAGE_DEAL_H
#define IMGE_DEAL_H
#include"Image.h"
#include"Base.h"
using namespace std;
using namespace cv;
std::vector<cv::Mat> Get_Single(std::vector<Cordinate> zuobiao, cv::Mat dist);
Prece  Pre_Process(cv::Mat&img1);//ͼ��Ĵ�С��8�ı���
Stage_infor Get_Person(cv::Mat img1);
cv::Mat Gauss_Img();//����һ�����Ӹ�˹�ֲ���ͼ��
void Produce_Img(std::vector<cv::Mat>Img_1, cv::Mat&img_pre, std::vector<Cordinate> Cor, Prece  Xinxi);
int Test(cv::Mat&image, Prece&Xinxi, Stage_infor&infor);
int Test_2(cv::Mat&image, Prece&Xinxi, Stage_infor&infor);
#endif