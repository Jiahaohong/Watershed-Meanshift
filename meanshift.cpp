#include "common.h"
#include "meanshift.h"

cv::Mat meanshift(cv::Mat &input_img)
{
	int spatialRad = 50;
	int colorRad = 50;
	int maxPyrLevel = 1;
	
	cv::Mat meanshift_img = cv::Mat::zeros(input_img.size(), CV_8UC3);
	cv::pyrMeanShiftFiltering(input_img, meanshift_img, spatialRad, colorRad, maxPyrLevel);

	cv::Mat gray_img = cv::Mat::zeros(input_img.size(), CV_8UC3);
	cv::cvtColor(meanshift_img, gray_img, CV_BGR2GRAY);

	cv::Mat canny_img = cv::Mat::zeros(input_img.size(), CV_8UC1);
	cv::Canny(gray_img, canny_img, 80, 150);
	//imshow("canny", canny_img);

	cv::Mat output_img = input_img.clone();
	int cnt1, cnt2;
	int m = output_img.rows;
	int n = output_img.cols;
	for (cnt1 = 0; cnt1 < m; ++cnt1)
	{
		for (cnt2 = 0; cnt2 < n; ++cnt2)
		{
			
			if (canny_img.at<uchar>(cnt1, cnt2) == 255)
			{
				output_img.at<cv::Vec3b>(cnt1, cnt2) = cv::Vec3b(255, 255, 255);
			}
		}
	}
	
	return output_img;
}