#include "common.h"
#include "watershed.h"

cv::Mat watershed(cv::Mat &input_img)
{
	cv::Mat gray_img;
	cv::cvtColor(input_img, gray_img, CV_BGR2GRAY);
	
	//È¡±ß½çµã
	cv::Canny(gray_img, gray_img, 80, 150);
	//imshow("canny", gray_img);

	std::vector<std::vector<cv::Point>> countours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(gray_img, countours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());
	
	cv::Mat marks = cv::Mat::zeros(input_img.size(), CV_32S);

	int index = 0;
	int compCount = 0;
	for (; index >= 0; index = hierarchy[index][0], compCount++)
	{
		drawContours(marks, countours, index, cv::Scalar::all(compCount + 1), 1, 8, hierarchy);
	}

	//Watershed
	cv::watershed(input_img, marks);

	cv::Mat output_img = input_img.clone();
	int cnt1, cnt2;
	int m = output_img.rows;
	int n = output_img.cols;
	for (cnt1 = 0; cnt1 < m; ++cnt1)
	{
		for (cnt2 = 0; cnt2 < n; ++cnt2)
		{
			if (marks.at<int>(cnt1,cnt2) == -1)
			{
				output_img.at<cv::Vec3b>(cnt1, cnt2) = cv::Vec3b(255, 255, 255);
			}
		}
	}

	return output_img;
}