#ifndef BASE_H
#define BASE_H
typedef struct
{
	int x;
	int y;
}Cordinate;

typedef struct
{
	std::vector<Cordinate> Cor;
	std::vector<cv::Mat> All_Person;
}Stage_infor;
typedef struct
{
	float scale;
	Cordinate Pad;
}Prece;
#endif