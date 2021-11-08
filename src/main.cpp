#include<iostream>
#include "manager.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <chrono>
#include <map>
#include <cmath>
#include <time.h>
using namespace cv;
using namespace std;



int main(){
	bool is_first = true;
	char* yolo_engine = "/home/tthd/workspace/project/yolofiresmoke-simple/resources/firesmoke-s.engine";
	float conf_thre = 0.3;
	Trtyolosort yosort(yolo_engine);
	VideoCapture capture;
	cv::Mat frame;
  frame = capture.open("/home/tthd/workspace/project/yolofiresmoke-simple/resources/141798581-1-192.mp4");
	if (!capture.isOpened()){
		std::cout<<"can not open"<<std::endl;
		return -1 ;
	}
	capture.read(frame);
	std::vector<DetectBox> det;
	auto start_draw_time = std::chrono::system_clock::now();
	
	clock_t start_draw,end_draw;
	start_draw = clock();
	int i = 0;

	while(capture.read(frame)){
		if (i%1==0){
		//std::cout<<"origin img size:"<<frame.cols<<" "<<frame.rows<<std::endl;
		auto start = std::chrono::system_clock::now();
		yosort.TrtDetect(frame,conf_thre,det);
  
		auto end = std::chrono::system_clock::now();
		int delay_infer = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout  << "delay_infer:" << delay_infer << "ms" << std::endl;
		}
		i++;
	}
	capture.release();
	return 0;
	
}
