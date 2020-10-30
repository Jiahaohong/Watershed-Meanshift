#include "common.h"
#include "watershed.h"
#include "meanshift.h"


int main()
{
	//¶ÁÈëÍ¼Ïñ
	cv::Mat orig_img = cv::imread("3.jpg");
	int M = orig_img.rows;
	int N = orig_img.cols;
	cv::imshow("orig img", orig_img);

	//Watershed
	cv::Mat watershed_img = watershed(orig_img);
	imshow("watershed img", watershed_img);

	//Meanshift
	cv::Mat meanshift_img = meanshift(orig_img);
	imshow("Mean Shift img", meanshift_img);

	cv::waitKey();

	return 0;
}