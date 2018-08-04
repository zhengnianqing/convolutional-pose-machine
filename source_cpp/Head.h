#ifndef HEAD_H
#define HEAD_H
#include "caffe/common.hpp"  
#include "caffe/layers/input_layer.hpp"  
#include "caffe/layers/inner_product_layer.hpp"  
#include "caffe/layers/dropout_layer.hpp"  
#include "caffe/layers/conv_layer.hpp"  
#include "caffe/layers/relu_layer.hpp"  
#include "caffe/layers/pooling_layer.hpp"  
#include "caffe/layers/lrn_layer.hpp"  
#include "caffe/layers/softmax_layer.hpp"  
#include "caffe/layers/concat_layer.hpp"
#include"caffe/layers/memory_data_layer.hpp"
#include"caffe/layers/slice_layer.hpp"
namespace caffe
{

	extern INSTANTIATE_CLASS(InputLayer);
	extern INSTANTIATE_CLASS(InnerProductLayer);
	extern INSTANTIATE_CLASS(DropoutLayer);
	extern INSTANTIATE_CLASS(ConvolutionLayer);
	extern INSTANTIATE_CLASS(MemoryDataLayer);
	extern INSTANTIATE_CLASS(SliceLayer);
	//REGISTER_LAYER_CLASS(Convolution);
	extern INSTANTIATE_CLASS(ReLULayer);
	//REGISTER_LAYER_CLASS(ReLU);
	extern INSTANTIATE_CLASS(PoolingLayer);
	//REGISTER_LAYER_CLASS(Pooling);
	extern INSTANTIATE_CLASS(LRNLayer);
	//REGISTER_LAYER_CLASS(LRN);
	extern INSTANTIATE_CLASS(SoftmaxLayer);
	//REGISTER_LAYER_CLASS(Softmax);
	extern INSTANTIATE_CLASS(ConcatLayer);
	//REGISTER_LAYER_CLASS(Concat);
}
#endif