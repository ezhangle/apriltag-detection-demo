#include "april_tag/TagDetector.h"
#include "april_tag/Tag36h11.h"

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

//https://book.openmv.cc/image/apriltag.html
//https://bitbucket.org/kaess/apriltags/src/master/AprilTags/
//http://www.tekkotsu.org/dox/structAprilTags_1_1TagDetection.html
int main(int argc, char **argv)
{
        string imgpath=argv[1];
        cv::Mat  image =cv::imread(imgpath),imagecopy;
		image.copyTo(imagecopy);

		//cv::imshow("apriltag-detection-demo",imagecopy);
        cv::cvtColor(image, image, CV_BGR2GRAY);
        
        cv::VideoCapture inputVideo;
        inputVideo.open(0);

        //while (inputVideo.grab()) {
        //   cv::Mat image;
	    //   inputVideo.retrieve(image);//抓取视频中的一张照片
		int id;

		AprilTags::TagDetector* m_tagDetector;
		AprilTags::TagCodes m_tagCodes = AprilTags::tagCodes36h11;
		m_tagDetector = new AprilTags::TagDetector(m_tagCodes);
        
		vector<AprilTags::TagDetection> detections = m_tagDetector->extractTags(image);
        
		if (detections.size()< 15)
		{
			std::cout << "error: insufficient("<<detections.size()<<") tags was detected!" << std::endl;
			//return 0;
		}
		
		std::cout<<detections.size()<<" detections"<<std::endl;
		
		vector<cv::Point2f>  imageCoords;
		for (int i = 0; i < detections.size(); i++)
		{
			id = detections[i].id;
			for (int j = 0; j < 4; j++)
			{
			imageCoords.push_back(cv::Point2f(detections[i].p[j].first, detections[i].p[j].second));
		        circle(imagecopy, cv::Point2f(detections[i].p[j].first, detections[i].p[j].second), 0.5,Scalar(0,255,0), -1);
                        putText(imagecopy, to_string(j),cv::Point2f(detections[i].p[j].first, detections[i].p[j].second), FONT_HERSHEY_COMPLEX, 0.2, cv::Scalar(225, 0, 0), 0.5, 8, 0);
			}
                         

                        putText(imagecopy, to_string(id),cv::Point2f(detections[i].cxy.first, detections[i].cxy.second) , FONT_HERSHEY_COMPLEX, 0.2, cv::Scalar(0, 0, 255), 0.5, 8, 0);


		}

		namedWindow("apriltag-detection-demo",WINDOW_NORMAL);
		cv::imshow("apriltag-detection-demo",imagecopy);

	       cv::waitKey();
      // }
       return 0;
   
}

