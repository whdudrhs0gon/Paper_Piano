#include "cv.hpp"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



using namespace std;
using namespace cv;


// The width of piano : 24cm
// The height of piano : 14cm
// The width of white(black) key : 3cm(2cm)
// The height of black key : 7cm


struct whereandclick
{
	int width = 480;
	int height = 280;
	bool whitePressed;
	bool blackPressed;
	Point finger;
};



void playSound(char key) {
	switch (key) {
	case 'a':
		cout << "C is pressed" << endl;
		PlaySound("sound_files/25.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'b':
		cout << "C# is pressed" << endl;
		PlaySound("sound_files/26.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'c':
		cout << "D is pressed" << endl;
		PlaySound("sound_files/27.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'd':
		cout << "D# is pressed" << endl;
		PlaySound("sound_files/28.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'e':
		cout << "E is pressed" << endl;
		PlaySound("sound_files/29.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'f':
		cout << "F is pressed" << endl;
		PlaySound("sound_files/30.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'g':
		cout << "F# is pressed" << endl;
		PlaySound("sound_files/31.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'h':
		cout << "G is pressed" << endl;
		PlaySound("sound_files/32.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'i':
		cout << "G# is pressed" << endl;
		PlaySound("sound_files/33.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'j':
		cout << "A is pressed" << endl;
		PlaySound("sound_files/34.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'k':
		cout << "A# is pressed" << endl;
		PlaySound("sound_files/35.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'l':
		cout << "B is pressed" << endl;
		PlaySound("sound_files/36.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;
	case 'n':
		cout << "C is pressed" << endl;
		PlaySound("sound_files/37.wav", NULL, SND_ASYNC | SND_NOSTOP);
		break;

	}
}


void switchfunc(whereandclick piano)
{
	int width = piano.width;
	int height = piano.height;
	bool whitePressed = piano.whitePressed;
	bool blackPressed = piano.blackPressed;
	Point finger = piano.finger;


	if (whitePressed == true && finger.x < int(width / 8) * 1)
	{
		playSound('a');
	}
	else if (whitePressed == true && finger.x < int(width / 8) * 2)
	{
		playSound('c');
	}
	else if (whitePressed == true && finger.x < int(width / 8) * 3)
	{
		playSound('e');
	}
	else if (whitePressed == true && finger.x < int(width / 8) * 4)
	{
		playSound('f');
	}
	else if (whitePressed == true && finger.x < int(width / 8) * 5)
	{
		playSound('h');
	}
	else if (whitePressed == true && finger.x < int(width / 8) * 6)
	{
		playSound('j');
	}
	else if (whitePressed == true && finger.x < int(width / 8) * 7)
	{
		playSound('l');
	}
	else if (whitePressed == true && finger.x < int(width / 8) * 8)
	{
		playSound('n');
	}
	else if (blackPressed == true and (finger.x >= int(width / 24) * 2 and finger.x <= int(width / 24) * 4))
	{
		playSound('b');
	}
	else if (blackPressed == true and (finger.x >= int(width / 24) * 5 and finger.x <= int(width / 24) * 7))
	{
		playSound('d');
	}
	if (blackPressed == true and (finger.x >= int(width / 24) * 11 and finger.x <= int(width / 24) * 13))
	{
		playSound('g');
	}
	if (blackPressed == true and (finger.x >= int(width / 24) * 14 and finger.x <= int(width / 24) * 16))
	{
		playSound('i');
	}
	if (blackPressed == true and (finger.x >= int(width / 24) * 17 and finger.x <= int(width / 24) * 19))
	{
		playSound('k');
	}
}





Mat FindForeground(const Mat& background, const Mat& frame) {
	Mat gray, foreground;
	cvtColor(frame, gray, CV_BGR2GRAY);
	foreground = abs(background - gray);

	for (int i = 0; i < foreground.cols; i++) {
		for (int j = 0; j < foreground.rows; j++) {
			if (foreground.at<uchar>(j, i) > 30 and foreground.at<uchar>(j, i) < 120) {
				foreground.at<uchar>(j, i) = 255;
			}
			else {
				foreground.at<uchar>(j, i) = 0;
			}
		}
	}
	erode(foreground, foreground, Mat(3, 3, CV_8U, Scalar(1)), Point(-1, -1), 2);
	dilate(foreground, foreground, Mat(3, 3, CV_8U, Scalar(1)), Point(-1, -1), 2);
	dilate(foreground, foreground, Mat(3, 3, CV_8U, Scalar(1)), Point(-1, -1), 2);

	return foreground;
}


Point DrawContours(const Mat& mask, const Mat& frame) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Point finger;
	int x = 0, y = 600;
	int a = 0, b = 1000;

	findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		boundRect[i] = boundingRect(Mat(contours[i]));
		for (int j = 0; j < contours[i].size(); j++)
		{
			if (contours[i][j].y < y and contours[i][j].y > 10)
			{
				y = contours[i][j].y; x = contours[i][j].x;
				if (b > y)
				{
					a = x, b = y;
				}
			}
		}
	}

	circle(frame, Point(a, b), 2, Scalar(255, 255, 255), 3);
	if (!a) return Point(0, 0);
	else return Point(a, b);
}

void swap(Point2f *array, int i, int j) {
	Point2f temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}


void findCoordinates(const Mat& frame, Point2f *inputArray, Point2f *outputArray) {

	Mat edge;
	Mat gray, reframe;
	int xmax = 0, xmin = 1000;


	vector<Vec4i> lines;
	int width = frame.cols;
	int height = frame.rows;


	cvtColor(frame, gray, CV_BGR2GRAY);
	threshold(gray, gray, 80, 255, THRESH_BINARY);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	morphologyEx(gray, gray, MORPH_CLOSE, element);
	GaussianBlur(gray, gray, Size(5, 5), 1.5);

	cvtColor(gray, reframe, CV_GRAY2BGR);
	floodFill(reframe, Point(width / 2, height / 2), Scalar(255, 0, 0), 0, Scalar(5, 5, 5), Scalar(5, 5, 5));



	for (int x = 0; x < reframe.cols; x++) {
		for (int y = 0; y < reframe.rows; y++) {
			if (reframe.at<Vec3b>(y, x)[0] != 255 || reframe.at<Vec3b>(y, x)[1] != 0)
				reframe.at<Vec3b>(y, x)[0] = reframe.at<Vec3b>(y, x)[1] = reframe.at<Vec3b>(y, x)[2] = 0;
		}
	}



	GaussianBlur(reframe, reframe, Size(5, 5), 1.5);
	Canny(reframe, edge, 5, 50, 3);
	HoughLinesP(edge, lines, 1, CV_PI / 180, 50, 10, 200);
	for (int i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		if ((l[0] + l[2]) / 2 < xmin  && min(l[1], l[3]) < height / 2)
		{
			xmin = (l[0] + l[2]) / 2;
			if (l[1] < l[3])
			{
				inputArray[0] = Point(l[0], l[1]);
				inputArray[3] = Point(l[2], l[3]);
			}
			else
			{
				inputArray[3] = Point(l[0], l[1]);
				inputArray[0] = Point(l[2], l[3]);
			}
		}

		if ((l[0] + l[2]) / 2 > xmax)
		{
			xmax = (l[0] + l[2]) / 2;
			if (l[1] < l[3])
			{
				inputArray[1] = Point(l[0], l[1]);
				inputArray[2] = Point(l[2], l[3]);
			}
			else
			{
				inputArray[2] = Point(l[0], l[1]);
				inputArray[1] = Point(l[2], l[3]);
			}
		}
		line(reframe, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2);


	}
	circle(reframe, inputArray[0], 3, Scalar(255, 255, 0), 3);
	circle(reframe, inputArray[1], 3, Scalar(255, 255, 0), 3);
	circle(reframe, inputArray[2], 3, Scalar(255, 255, 0), 3);
	circle(reframe, inputArray[3], 3, Scalar(255, 255, 0), 3);

	outputArray[0] = Point2f(0, 0);
	outputArray[1] = Point2f(480, 0);
	outputArray[2] = Point2f(480, 280);
	outputArray[3] = Point2f(0, 280);
}

Mat findColor(const Mat& frame) {
	Mat HSV, colorimg;

	cvtColor(frame, HSV, CV_BGR2HSV);
	inRange(HSV, Scalar(22, 0, 0), Scalar(37, 255, 255), HSV);

	colorimg = (HSV.size(), CV_8UC3, Scalar(0));

	add(frame, Scalar(0), colorimg, HSV);

	return colorimg;
}

int main(int argc, char** argv) {
	VideoCapture cap("piano1.mp4");
	Mat frame, transform, result, test;
	Point2f inputArray[4], outputArray[4];
	Point finger;
	vector<Vec4i> lines;
	int num = 0;
	double fps = cap.get(CAP_PROP_FPS);

	Mat background, foreground;
	whereandclick piano;
	int cnt = 0;
	int curr, prev = 0;
	bool down = false;

	int whiteNum = 0, blackNum = 0;
	bool whitePressed, blackPressed;

	bool start = false;

	cap >> frame;
	int height = frame.rows;
	int width = frame.cols;


	while (1) {
		cap >> frame;
		if (frame.empty()) break;

		test = frame.clone();
		putText(test, "Set the white key on the orange spot and press finger", Point(20, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 128, 255), 2);    // Press 'Space bar'
		circle(test, Point(width / 2, height / 2), 2, Scalar(0, 128, 255), 3);
		imshow("frame", test);


		if ((char)waitKey(1) == 32) {
			start = true;
			findCoordinates(frame, inputArray, outputArray);
			transform = getPerspectiveTransform(inputArray, outputArray);
			warpPerspective(frame, background, transform, Size(480, 280));
			cvtColor(background, background, CV_BGR2GRAY);
		}

		if (start) {
			//transformation
			warpPerspective(frame, result, transform, Size(480, 280));

			foreground = FindForeground(background, result);
			finger = DrawContours(foreground, result);

			piano.finger = finger;

			line(result, Point(0, 140), Point(480, 140), Scalar(255, 255, 255), 2);

			curr = finger.y;
			if (curr - prev > 4)
				down = true;
			else if (curr - prev < 0)
				down = false;

			if (finger.y > 210)
				whiteNum++;
			else
				whiteNum = 0;

			if (whiteNum > 3 && down)
			{
				whitePressed = true;
				piano.whitePressed = true;
			}
			else
			{
				whitePressed = false;
				piano.whitePressed = false;
			}
			
			if (finger.y >= 70 and finger.y <= 140 and down)
			{
				blackNum++;
			}
			else
			{
				blackNum = 0;
			}

			if (blackNum > 3)
			{
				blackPressed = true;
				piano.blackPressed = true;
			}
			else
			{
				blackPressed = false;
				piano.blackPressed = false;
			}


			line(result, Point(0, 210), Point(480, 210), Scalar(0, 0, 255), 2);
			line(result, Point(0, 70), Point(480, 70), Scalar(255, 0, 0), 2);


			prev = curr;
			switchfunc(piano);

			imshow("result", result);
		}


		waitKey(1000 / fps);
	}
}