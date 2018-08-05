#ifndef GABORFEATURE_H
#define GABORFEATURE_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "gaborwavelet.h"


class Gabor
{
public:
	std::vector<cv::Mat> getFeatures(cv::Mat & inputImage);//�õ�ȫ�߶�ȫ���������
	void GaborTranform(cv::Mat &inputImage, cv::Mat &outputImage, double u, double v);//uΪ����0-7��vΪ�߶�0-4��Gaborʵ���任

private:
	double Kmax = PI ;// ԭֵPI / 2
	double f = std::sqrt(2);
	double Delt = 6 * PI;//ԭֵ2*PI
	
	GaborWavelet gWavelet;
};


#endif 