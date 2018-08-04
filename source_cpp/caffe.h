#include"Head.h"
#include"shared_ptr.hpp"
#include <caffe/caffe.hpp>
#include"Base.h"

#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace caffe;  // NOLINT(build/namespaces)
using namespace cv;
using namespace std;
using std::string;

/* Pair (label, confidence) representing a prediction. */
typedef std::pair<string, float> Prediction;


class Classifier {
public:
	Classifier(const string& model_file,
		const string& trained_file,
		const string& mean_file,
		const string& label_file);

	std::vector<Point> Classify(const cv::Mat& img, int N = 5);
	std::vector<Cordinate> Get_Person();
private:
	void SetMean(const string& mean_file);

	std::vector<Point> Predict(const cv::Mat& img, int stage);

	void WrapInputLayer(std::vector<cv::Mat>* input_channels);

	void Preprocess(const cv::Mat& img,
		std::vector<cv::Mat>* input_channels,int stage);

private:
	boost::shared_ptr<Net<float> > net_;
	cv::Size input_geometry_;
	int num_channels_;
	cv::Mat mean_;
	cv::Mat mean_3;
	cv::Mat mean_4;
	std::vector<string> labels_;
	cv::Mat Stage_one; //保存的是第一阶段产生的特征图的8倍，是float类型的。
	cv::Mat One_show;
	std::vector<Cordinate> Person_Cordinate;
};
#endif