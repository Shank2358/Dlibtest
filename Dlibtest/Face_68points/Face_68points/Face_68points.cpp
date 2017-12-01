// Face_68points.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <dlib/image_processing/frontal_face_detector.h>  
//���������ı�ǵ�
#include <dlib\opencv.h>
#include <opencv2\opencv.hpp>
#include <dlib\image_processing\frontal_face_detector.h>
#include <dlib\image_processing\render_face_detections.h>
#include <dlib\image_processing.h>
#include <dlib\gui_widgets.h>

//����dlib����
using namespace dlib;

using namespace std;

int main() {

	try {
		//���Ƚ��л�ȡ����ͷ
		cv::VideoCapture cap(0);

		if (!cap.isOpened()) {
			//�������ͷû�п���
			cerr << "Unable to connect to camera" << endl;
			return 1;
		}
		//Load face detection and pos estimation models ����������Ҫ������ʶ�����̬����ģ��
		frontal_face_detector detector = get_frontal_face_detector();
		shape_predictor pos_modle;
		//���ļ��е�ģ�ͷ�����pos_modle��
		deserialize("shape_predictor_68_face_landmarks.dat") >> pos_modle;

		//Grab and process frames until the main window is closed by the user
		//����ǰÿһ֡��ͼƬ
		while (cv::waitKey(30) != 27)
		{

			//Grab a frame ��ȡһ֡
			cv::Mat temp;
			//������ͷ��ȡ�ĵ�ǰ֡ͼƬ���뵽 �м��ļ���
			cap >> temp;
			//����ת��ΪRGB����ͼƬ
			cv_image<bgr_pixel> cimg(temp);
			//��ʼ��������ʶ��
			std::vector<rectangle> faces = detector(cimg);
			//����ÿһ������pos���� Find the pose of each face
			std::vector<full_object_detection> shapes;
			unsigned faceNumber = faces.size();
			//����������������뼯��֮��
			for (unsigned i = 0; i < faceNumber; i++)
				shapes.push_back(pos_modle(cimg, faces[i]));
			if (!shapes.empty()) {
				int faceNumber = shapes.size();
				for (int j = 0; j < faceNumber; j++)
				{
					for (int i = 0; i < 68; i++)
					{
						//����������ֵ�ĵ�
						cv::circle(temp, cvPoint(shapes[j].part(i).x(), shapes[j].part(i).y()), 3, cv::Scalar(0, 0, 255), -1);
						//��ʾ����
						cv::putText(temp, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 255));

					}
				}
			}
			//Display it all on the screen  չʾÿһ֡��ͼƬ
			cv::imshow("Dlib���", temp);
		}

	}
	catch (serialization_error &e) {
		cout << "You need dlib's default face landmarking file to run this example.(����Ҫ���landmark��bat�ļ����ſ��������ʵ��)" << endl;
		cout << endl << e.what() << endl;
	}
	catch (exception &e) {
		cout << e.what() << endl;

	}
}
