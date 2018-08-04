#include"caffe.h"
#include"iostream"

Classifier::Classifier(const string& model_file,
	const string& trained_file,
	const string& mean_file,
	const string& label_file) {
#ifdef CPU_ONLY
	Caffe::set_mode(Caffe::CPU);
#else
	Caffe::set_mode(Caffe::GPU);
#endif

	/* Load the network. */
	net_.reset(new Net<float>(model_file, TEST));
	net_->CopyTrainedLayersFrom(trained_file);

	CHECK_EQ(net_->num_inputs(), 1) << "Network should have exactly one input.";
	CHECK_EQ(net_->num_outputs(), 1) << "Network should have exactly one output.";

	Blob<float>* input_layer = net_->input_blobs()[0];
	num_channels_ = input_layer->channels(); //��ȡ������ͼ���ͨ����

	input_geometry_ = cv::Size(input_layer->width(), input_layer->height());

	/* Load the binaryproto mean file. */
	SetMean(mean_file);

	/* Load labels. */
	std::ifstream labels(label_file.c_str());
	CHECK(labels) << "Unable to open labels file " << label_file;
	string line;
	while (std::getline(labels, line))
		labels_.push_back(string(line));

	Blob<float>* output_layer = net_->output_blobs()[0];
	CHECK_EQ(labels_.size(), output_layer->channels())
		<< "Number of labels is different from the output layer dimension.";
	Stage_one = Mat();
	One_show = Mat();
}

static bool PairCompare(const std::pair<float, int>& lhs,
	const std::pair<float, int>& rhs) {
	return lhs.first > rhs.first;
}

/* Return the indices of the top N values of vector v. */
static std::vector<int> Argmax(const std::vector<float>& v, int N) {
	std::vector<std::pair<float, int> > pairs;
	for (size_t i = 0; i < v.size(); ++i)
		pairs.push_back(std::make_pair(v[i], static_cast<int>(i)));
	std::partial_sort(pairs.begin(), pairs.begin() + N, pairs.end(), PairCompare);

	std::vector<int> result;
	for (int i = 0; i < N; ++i)
		result.push_back(pairs[i].second);
	return result;
}

/* Return the top N predictions. */
std::vector<Point> Classifier::Classify(const cv::Mat& img, int stage) {
	std::vector<Point> output = Predict(img, stage);
	/*N = std::min<int>(labels_.size(), N);
	std::vector<int> maxN = Argmax(output, N);
	std::vector<Prediction> predictions;
	for (int i = 0; i < N; ++i) {
	int idx = maxN[i];
	predictions.push_back(std::make_pair(labels_[idx], output[idx]));
	}
	*/
	return output;
}

std::vector<Cordinate>Classifier::Get_Person()  //�ҳ�ͼ������ֵλ�ã���λ�þ������������λ��
{
	int rows_ = Stage_one.rows;
	int cols_ = Stage_one.cols;
	std::vector<Cordinate> Person;
	for (int i = 0; i < rows_; i++)
	{
		float *P = Stage_one.ptr<float>(i);
		for (int j = 0; j < cols_; j++)
		if (i >= 1 && i <= rows_ - 2 && j >= 1 && j <= cols_ - 2)
		{
			float *P = Stage_one.ptr<float>(i);
			float *P_top1 = Stage_one.ptr<float>(i - 1);
			float *P_bot2 = Stage_one.ptr<float>(i + 1);
			if (P[j]>P[j - 1] && P[j]>P[j + 1] && P[j]>P_top1[j] && P[j]>P_top1[j - 1])
			{
				if (P[j] >P_top1[j + 1] && P[j] >P_bot2[j] && P[j] >P_bot2[j - 1] && P[j] >P_bot2[j + 1])  //��λ�õ�ֵ�����Ǿֲ����ֵ�����Ҹô���ֵ�������0.5
				{
					if (P[j] >0.5)
					{
						Cordinate Cor = { j, i };
						cout << "cordinate" << j << " " << i << endl;
						Person.push_back(Cor);//�����еķ���������ֵ�洢������
					}
				}
			}
		}
	}
	/*for (int k = 0; k < Person.size(); k++)
	{
		uchar *P =Stage_one.ptr<uchar>(Person[k].y);
		P[Person[k].x] = 0;
	}*/
	return Person;
}

/* Load the mean file in binaryproto format. */
void Classifier::SetMean(const string& mean_file) {
	//BlobProto blob_proto;
	//ReadProtoFromBinaryFileOrDie(mean_file.c_str(), &blob_proto);

	/* Convert from BlobProto to Blob<float> */
	//Blob<float> mean_blob;
	//mean_blob.FromProto(blob_proto);
	//CHECK_EQ(mean_blob.channels(), num_channels_)
	//	<< "Number of channels of mean file doesn't match input layer.";

	/* The format of the mean file is planar 32-bit float BGR or grayscale. */
	//std::vector<cv::Mat> channels;
	//float* data = mean_blob.mutable_cpu_data();
	//for (int i = 0; i < num_channels_; ++i) {
		/* Extract an individual channel. */
	//	cv::Mat channel(mean_blob.height(), mean_blob.width(), CV_32FC1, data);
	//	channels.push_back(channel);
	//	data += mean_blob.height() * mean_blob.width();
	//}

	/* Merge the separate channels into a single image. */
	//cv::Mat mean;
	//cv::merge(channels, mean);

	/* Compute the global mean pixel value and create a mean image
	* filled with this value. */
	//cv::Scalar channel_mean = cv::mean(mean);
	mean_ = cv::Mat(input_geometry_,CV_32FC1,Scalar(128));
	mean_3 = cv::Mat(input_geometry_,CV_32FC3, Scalar(128, 128, 128));
	mean_4 = cv::Mat(input_geometry_,CV_32FC4,Scalar(128,128,128,128));
}

std::vector<Point> Classifier::Predict(const cv::Mat& img, int stage) {
	Blob<float>* input_layer = net_->input_blobs()[0];  //��ȡ����ĵ�һ������ָ��,
	//input_layer->Reshape(1, num_channels_,
	//input_geometry_.height, input_geometry_.width);
	if (stage==1)
	input_layer->Reshape(1,img.channels(),  //�������reshape
		img.rows, img.cols);
	else if (stage == 2)
	{
		if (img.channels()==3)
		input_layer->Reshape(1, img.channels() + 1,
			img.rows, img.cols);
		else
		input_layer->Reshape(1, img.channels(),
			img.rows, img.cols);
	}
	/* Forward dimension change to all layers. */
	net_->Reshape(); //
	
	std::vector<cv::Mat> input_channels;
	WrapInputLayer(&input_channels);
	
	Preprocess(img, &input_channels,stage);//��ͼ�����ݽ��й�һ����Ȼ��������������ݲ�

	net_->Forward();  //����ǰ�򴫲�
	
	if (stage == 1)  //���������ĵ�һ�׶Σ�ʶ����������λ�ý׶�
	{
		Blob<float>* output_layer = net_->output_blobs()[0];
		std::vector<Point>Z;
		const boost::shared_ptr<Blob<float> > feature_blob = net_->blob_by_name("Mconv7_stage4");
		cout << "feature_blob" << feature_blob->height() << " " << feature_blob->width() << " " << feature_blob->channels() << endl;
		cout << "output_layer_shape" << output_layer->shape()[2] << " " << output_layer->shape()[3] << endl;
		Mat feat(cv::Size(feature_blob->width(), feature_blob->height()), CV_32FC1);//����������ȡ����������ͼ��
		for (int i = 0; i < feat.rows; i++)
		{
			float *P = feat.ptr<float>(i);
			for (int j = 0; j < feat.cols; j++)
			{
				P[j] = output_layer->cpu_data()[i*feat.cols + j];
			}
		}
		Mat dist;
		resize(feat, dist, Size(0, 0), 8.0, 8.0, INTER_CUBIC);  //��������pooling�����Σ�ÿ�β�����2����ˣ���Ҫ�ڽ���������ͼ��Ŵ�8����Ȼ��Ѱ��λ�á�
		Stage_one = dist;
		//imshow("position", Stage_one);
		//cvWaitKey(0);
		return Z;  //���ﷵ��ֵû��ʵ������
	}
	else if (stage == 2)//���������ĵڶ��׶Σ�ʶ��ÿ������ľ���ؽ�λ��
	{
		Blob<float>* output_layer = net_->output_blobs()[0];
		const boost::shared_ptr<Blob<float> > feature_blob = net_->blob_by_name("Mconv7_stage6");
		cout << "feature_blob_Stage2  " << feature_blob->channels()<<" "<<feature_blob->height() << " " << feature_blob->width() << " " << feature_blob->channels() << endl;
		std::vector<cv::Mat> feature_map;
		std::vector<Point>Z1;
		Mat feat(cv::Size(feature_blob->width(), feature_blob->height()), CV_32FC1);
		//Mat xianshi(cv::Size(feature_blob->width() * 8, feature_blob->height() * 8), CV_32FC1);
		for (int kk = 0; kk < 15; kk++)   //14���ؽ�����ȡֵ��14���ؽڶ�Ӧ��14��ͨ��������������ͬһ����,���һ��ͨ��������һ���˵����еĹؼ�������ͼ
		{
			//string path = "str"+to_string(kk)+".txt";
			//ofstream b1(path);
			for (int i = 0; i < feat.rows; i++)
			{
				float *P = feat.ptr<float>(i);
				for (int j = 0; j < feat.cols; j++)
				{
					const float *P_blob=feature_blob->cpu_data()+feature_blob->offset(0,kk,i,j);
					P[j] = *P_blob;
					//b1 << P[j]<<" ";
				}
				//b1 << " ";
			}
			feature_map.push_back(feat.clone());
		}
		//resize(feat, xianshi, Size(0, 0), 8.0, 8.0, INTER_CUBIC);
		//imshow("img", xianshi);
		//cvWaitKey(0);
		for (int k = 0; k < feature_map.size()-1; k++)  //�ҳ�ÿ������ͼ������ֵ������ؽڵ�λ��
		{
			Mat dist(Size(feature_blob->width() * 8, feature_blob->height() * 8), CV_32FC1);
			feat = feature_map[k];
			resize(feat, dist, Size(0, 0), 8.0, 8.0, INTER_CUBIC);
			float max = -1;
			Point pp = { 0, 0 };
			for (int i = 0; i < dist.rows;i++)
			for (int j = 0; j < dist.cols; j++)
			{
				float *P = dist.ptr<float>(i);
				if (P[j]>max)
				{
					max = P[j];
					pp.x = j; pp.y = i;
				}
			}
			Z1.push_back(pp);
			//cvWaitKey();
		}
		return Z1; 
	}
}

/* Wrap the input layer of the network in separate cv::Mat objects
* (one per channel). This way we save one memcpy operation and we
* don't need to rely on cudaMemcpy2D. The last preprocessing
* operation will write the separate channels directly to the input
* layer. */

void Classifier::WrapInputLayer(std::vector<cv::Mat>* input_channels)
{
	Blob<float>* input_layer = net_->input_blobs()[0];

	int width = input_layer->width();//�����߶�
	int height = input_layer->height();//�������
	float* input_data = input_layer->mutable_cpu_data();//��ȡ���������ָ��
	for (int i = 0; i < input_layer->channels(); ++i) {
		cv::Mat channel(height, width, CV_32FC1, input_data);//��ȡ�����ͼ������
		input_channels->push_back(channel);
		input_data += width * height;
	}
}

void Classifier::Preprocess(const cv::Mat& img,
	std::vector<cv::Mat>* input_channels,int stage) {
	/* Convert the input image to the input image format of the network. */
	cv::Mat sample_resized;
	cout << "img_ch:" << img.channels() << endl;  
	if (img.channels() == 3 && num_channels_ == 1)   //ͼ��ͨ����������Ļ�������ͨ����ת����
		cv::cvtColor(img, sample_resized, cv::COLOR_BGR2GRAY);
	else if (img.channels() == 4 && num_channels_ == 1)
		cv::cvtColor(img, sample_resized, cv::COLOR_BGRA2GRAY);
	else if (img.channels() == 4 && num_channels_ == 3)
		cv::cvtColor(img, sample_resized, cv::COLOR_BGRA2BGR);
	else if (img.channels() == 1 && num_channels_ == 3)
		cv::cvtColor(img, sample_resized, cv::COLOR_GRAY2BGR);
	else
		sample_resized = img;

	//if (sample.size() != input_geometry_)
	//	cv::resize(sample, sample_resized, input_geometry_);
	//else
	cv::Mat sample_float;
	cv::Mat sample_normalized;

	if (sample_resized.channels() == 3)
	{
		sample_resized.convertTo(sample_float, CV_32FC3);  //��ͼ��ת����float��������
		if (mean_3.size() != sample_float.size())
			cv::resize(mean_3, mean_3, Size(sample_float.cols, sample_float.rows));
		cv::subtract(sample_float, mean_3, sample_normalized);  //ͼ�����ݹ�һ������������ֵ
	}
	else if (num_channels_ == 1)
	{
		sample_resized.convertTo(sample_float, CV_32FC1);
		if (mean_.size() != sample_float.size())
			cv::resize(mean_, mean_, Size(sample_float.cols, sample_float.rows));
		cv::subtract(sample_float, mean_, sample_normalized);
	}
	sample_normalized = sample_normalized*0.00390625;  //ͼ�����ݹ�һ����������
	cv::Mat img11(Size(sample_normalized.rows, sample_normalized.cols), CV_32FC4, Scalar(0, 0,0,0));
	cout << sample_normalized.channels()<<" "<< sample_normalized.rows << " " << sample_normalized.cols << endl;
	if (stage == 2)  //���������ĵڶ��׶Σ���ʶ����Ҫ���һ��ͨ����ͨ���ڵ����ݷ��Ӹ�˹�ֲ�����Ϊ������ͼ����Χ��������Ϣ��
	{
		for (int i = 0; i < sample_normalized.rows; i++)
		{
			for (int j = 0; j < sample_normalized.cols; j++)
			{
				cv::Vec4f &P = img11.at<Vec4f>(i, j);
				cv::Vec3f &PP = sample_normalized.at<cv::Vec3f>(i, j);
				float dist_1 = (i - 368 / 2.0)*(i - 368 / 2.0) + (j - 368 / 2.0)*(j - 368 / 2.0);
				float exponent = dist_1 / 2.0 / 21.0 / 21.0; //���ն�ά��̬�ֲ��������ֵ
				P[0] = PP[0];
				P[1] = PP[1];
				P[2] = PP[2];
				P[3] = expf(-exponent);
			}
		}
	}
	/* This operation will write the separate BGR planes directly to the
	* input layer of the network because it is wrapped by the cv::Mat
	* objects in input_channels. */
	if (stage==1)
	cv::split(sample_normalized, *input_channels);
	else 
	cv::split(img11,*input_channels);
	CHECK(reinterpret_cast<float*>(input_channels->at(0).data)
		== net_->input_blobs()[0]->cpu_data())   //��ͼ�����ݼ��ص����������
		<< "Input channels are not wrapping the input layer of the network.";
}

