#include "gabor.h"
#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>



using namespace std;
using namespace cv;

//gabor�任����
#define GABOR_U 2  //uΪ����0-7
#define GABOR_V 3  //vΪ�߶�0-4

//��ⴰ�ڲ���
int windowwidth = 10;
int windowheight = 40;
uchar step = 10;


int main()
{
	char filepath[20];
	int cnt = 0;
	while (1)
	{
		//��ȡͼƬ
		sprintf(filepath,"ԭͼ//%d.jpg",cnt);
		Mat src = imread(filepath);
		if (src.empty())
			break;
		cout << "**********��" << cnt + 1 << "��ͼƬ*********" << endl;
		imshow("ԭͼ", src);


		Mat gabormat;
		Gabor gabor;
		gabor.GaborTranform(src, gabormat, GABOR_U, GABOR_V);//uΪ����0-7��vΪ�߶�0-4
		imshow("gabor�仯", gabormat);

		Mat element = getStructuringElement(MORPH_RECT, Size(1, 10));
		dilate(gabormat, gabormat, element,Point(-1,-1),4);
		erode(gabormat, gabormat, element, Point(-1, -1), 4);
		//equalizeHist(src, src);

		Mat mean;
		Mat stddev;
		meanStdDev(gabormat, mean, stddev);
		float m = mean.at<double>(0, 0);
		float std = stddev.at<double>(0, 0);

		cout << "����ͼ���ֵ��" << m << endl;
		cout << "����ͼ�񷽲" << std << endl;
		imshow("��̬ѧ����", gabormat);


		Rect window(0, 0, windowwidth, windowheight);

		for (int i = 0; i < gabormat.rows - windowheight; i+=step)
		{
			for (int j = 0; j < gabormat.cols - windowwidth; j+=step)
			{
	
				Mat roimean;
				Mat roistddev;
				meanStdDev(gabormat(window + Point(j, i)), roimean, roistddev);
				float roim = roimean.at<double>(0, 0);
				float roistd = roistddev.at<double>(0, 0);


				if (roim < m+2.5*std)
					continue;
				rectangle(src, window + Point(j, i), Scalar(255, 255, 255),1);
			}
		}
		imshow("���", src);

		waitKey();
		cnt++;
		cout << endl;

	}




	system("pause");
	return 0;

}

