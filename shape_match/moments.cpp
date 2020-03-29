#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv){
	//Your code goes here
	Mat src, circle, sq, test;
	src = imread("template.png", 1 );
	test = imread("out.png", 1);
	const char* sw="source";
	namedWindow(sw);

	inRange(test, cv::Scalar(80,100,0), cv::Scalar(255,255,100), test);
	inRange(src, cv::Scalar(100,0,0), cv::Scalar(255,30,30), circle);
	imshow(sw,test);
	inRange(src, cv::Scalar(0,0,100), cv::Scalar(30,30,255), sq);
	//imshow(sw,sq);

	threshold(circle,circle, 128,255, THRESH_BINARY);
	
	Moments mom_c = moments(circle, false);
	double hm_c[7];
	HuMoments(mom_c, hm_c);
	Moments mom_s = moments(circle, false);
	double hm_s[7];
	HuMoments(mom_c, hm_s);
	for(int i = 0; i < 7; i++){
  		hm_c[i] = (-1) * copysign(1.0, hm_c[i]) * log10(abs(hm_c[i])); 
  		hm_s[i] = (-1) * copysign(1.0, hm_s[i]) * log10(abs(hm_s[i]));
	}

	// for (int i=0;i<7;i++){                    //HuMoments shows zero in all except hm[0]
	// 	cout << hm[i]<<" ";
	// }
	// cout << endl;

	double dist1, dist2;
	dist1 = matchShapes(test,sq, CV_CONTOURS_MATCH_I2,0);

	dist2 = matchShapes(test,circle, CV_CONTOURS_MATCH_I2,0);	

	cout <<dist1<<" "<<dist2<<endl;
	waitKey(0);
	return 0;
}
