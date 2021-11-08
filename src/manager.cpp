#include "manager.hpp"
#include "string"
using std::vector;
using namespace cv;
static Logger gLogger;

Trtyolosort::Trtyolosort(char *yolo_engine_path){
	yolo_engine_path_ = yolo_engine_path;
	trt_engine = yolov5_trt_create(yolo_engine_path_);
	printf("create yolov5-trt , instance = %p\n", trt_engine);
   std::string videopath = "saved.avi"; 
  int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');  	
	outputVideo.open(videopath,codec,25.0,cv::Size(1024, 576),true);
}

void Trtyolosort::showDetection(cv::Mat& img, std::vector<DetectBox>& boxes) {
    cv::Mat temp = img.clone();
    for (auto box : boxes) {
        cv::Point lt(box.x1, box.y1);
        cv::Point br(box.x2, box.y2);
        cv::rectangle(temp, lt, br, cv::Scalar(255, 0, 0), 1);
   std::string lbl;

     if (((int)box.classID) == 0) lbl = cv::format("%s","fire");
    else  lbl = cv::format("%s","smoke");
        cv::putText(temp, lbl, lt, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0,255,0));
    }
    //cv::imshow("img", temp);
    cv::resize(temp, temp, cv::Size(1024, 576), 0, 0);
    outputVideo.write(temp);
    cv::waitKey(1);
}

int Trtyolosort::TrtDetect(cv::Mat &frame,float &conf_thresh,std::vector<DetectBox> &det){
	// yolo detect
	auto ret = yolov5_trt_detect(trt_engine, frame, conf_thresh,det);
	showDetection(frame,det);
	return 1 ;
	
}
