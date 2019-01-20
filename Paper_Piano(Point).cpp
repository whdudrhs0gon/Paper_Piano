#include "cv.hpp"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



using namespace std;
using namespace cv;



struct ClickDetection
{
	int width, height;
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


void switchfunc(ClickDetection click)
{
	int width = click.width;
	int height = click.height;
	bool whitePressed = click.whitePressed;
	bool blackPressed = click.blackPressed;
	Point fingertip = click.finger;


	if (whitePressed == true && fingertip.x < int(width / 8) * 1)
	{
		playSound('a');
	}
	else if (whitePressed == true && fingertip.x < int(width / 8) * 2)
	{
		playSound('c');
	}
	else if (whitePressed == true && fingertip.x < int(width / 8) * 3)
	{
		playSound('e');
	}
	else if (whitePressed == true && fingertip.x < int(width / 8) * 4)
	{
		playSound('f');
	}
	else if (whitePressed == true && fingertip.x < int(width / 8) * 5)
	{
		playSound('h');
	}
	else if (whitePressed == true && fingertip.x < int(width / 8) * 6)
	{
		playSound('j');
	}
	else if (whitePressed == true && fingertip.x < int(width / 8) * 7)
	{
		playSound('l');
	}
	else if (whitePressed == true && fingertip.x < int(width / 8) * 8)
	{
		playSound('n');
	}
	else if (blackPressed == true and (fingertip.x >= int(width / 24) * 2 and fingertip.x <= int(width / 24) * 3))
	{
		playSound('b');
	}
	else if (blackPressed == true and (fingertip.x >= int(width / 24) * 5 and fingertip.x <= int(width / 24) * 6))
	{
		playSound('d');
	}
	if (blackPressed == true and (fingertip.x >= int(width / 24) * 11 and fingertip.x <= int(width / 24) * 12))
	{
		playSound('g');
	}
	if (blackPressed == true and (fingertip.x >= int(width / 24) * 14 and fingertip.x <= int(width / 24) * 15 + 10))
	{
		playSound('i');
	}
	if (blackPressed == true and (fingertip.x >= int(width / 24) * 17 and fingertip.x <= int(width / 24) * 18))
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


Point DrawFingertip(const Mat& mask, const Mat& frame) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Point finger;
	int x = 0, y = 600;
	int a = 0, b = 1000;

	findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) {
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

	circle(frame, Point(a, b), 2, Scalar(0, 0, 255), 3);   // Draw FingerTip
	if (!a) return Point(0, 0);
	else return Point(a, b);
}

void swap(Point2f *array, int i, int j) {
	Point2f temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}


void findCoordinates(const Mat& colorImage, Point2f *inputArray, Point2f *outputArray) {
	Mat gray, gaussian, edge;
	int num = 0;
	int upleft_sum_x = 0, upleft_sum_y = 0, downleft_sum_x = 0, downleft_sum_y = 0, left_count = 0;
	int upright_sum_x = 0, upright_sum_y = 0, downright_sum_x = 0, downright_sum_y = 0, right_count = 0;
	int a, b, c, d;
	a = b = c = d = 0;
	int x, y, z, w;
	x = y = z = w = 0;

	vector<Vec4i> lines;
	//Get lines
	imshow("yellow", colorImage);
	cvtColor(colorImage, gray, CV_BGR2GRAY);
	//imshow("gray", gray);
	GaussianBlur(gray, gaussian, Size(3, 3), 1.5);
	//imshow("gaussian", gaussian);
	Canny(gaussian, edge, 100, 200, 3);
	imshow("edge", edge);
	HoughLinesP(edge, lines, 1, CV_PI / 180, 70, 150, 160);

	//get the coordinates for transformation
	for (int i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		line(colorImage, Point(l[0],l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 1);     // Draw all lines
		if (l[0] < colorImage.size().width / 2)
		{
			int upy = max(l[1], l[3]);
			if (upy == l[3]) {
				upleft_sum_x += l[0];
				upleft_sum_y += l[1];
				downleft_sum_x += l[2];
				downleft_sum_y += l[3];
			}
			else {
				upleft_sum_x += l[2];
				upleft_sum_y += l[3];
				downleft_sum_x += l[0];
				downleft_sum_y += l[1];
			}
			left_count += 1;
		}
		else
		{
			int upy = max(l[1], l[3]);
			if (upy == l[3]) {
				upright_sum_x += l[0];
				upright_sum_y += l[1];
				downright_sum_x += l[2];
				downright_sum_y += l[3];
			}
			else {
				upright_sum_x += l[2];
				upright_sum_y += l[3];
				downright_sum_x += l[0];
				downright_sum_y += l[1];
			}
			right_count += 1;
		}
	}
	if (left_count != 0)
	{
		a = upleft_sum_x / left_count;
		b = upleft_sum_y / left_count;
		c = downleft_sum_x / left_count;
		d = downleft_sum_y / left_count;
	}

	if (right_count != 0)
	{
		x = upright_sum_x / right_count;
		y = upright_sum_y / right_count;
		z = downright_sum_x / right_count;
		w = downright_sum_y / right_count;
	}

	line(colorImage, Point(a, b), Point(c, d), Scalar(255, 0, 0), 3);   //Draw left line
	line(colorImage, Point(x, y), Point(z, w), Scalar(0, 0, 255), 3);   //Draw right line

	if (b > d) {
		inputArray[1] = Point(a, b);
		inputArray[2] = Point(c, d);
	}
	else {
		inputArray[2] = Point(a, b);
		inputArray[1] = Point(c, d);
	}

	if (y > w) {
		inputArray[0] = Point(x, y);
		inputArray[3] = Point(z, w);
	}
	else {
		inputArray[3] = Point(x, y);
		inputArray[0] = Point(z, w);
	}

	outputArray[0] = Point2f(0, 0);
	outputArray[1] = Point2f(480, 0);
	outputArray[2] = Point2f(480, 280);
	outputArray[3] = Point2f(0, 280);
}

Mat findColor(const Mat& frame) {
	Mat HSV, colorimg;

	cvtColor(frame, HSV, CV_BGR2HSV);
	inRange(HSV, Scalar(12, 70, 0), Scalar(47, 255, 170), HSV);

	colorimg = (HSV.size(), CV_8UC3, Scalar(0));

	add(frame, Scalar(0), colorimg, HSV);

	return colorimg;
}

int main(int argc, char** argv) {
	VideoCapture cap("piano3.mp4");
	double fps = cap.get(CAP_PROP_FPS);
	Mat frame, transform, transformed_frame, colorImage, background, foreground;

	Point2f inputArray[4], outputArray[4];
	Point fingertip;
	ClickDetection click;

	int cur_fingertip, prev_fingertip = 0;
	bool down = false;
	int whiteNum = 0, blackNum = 0;



	// Get Transformed Background Image
	cap >> frame;
	colorImage = findColor(frame);
	findCoordinates(colorImage, inputArray, outputArray);
	imshow("colorImage", colorImage);
	transform = getPerspectiveTransform(inputArray, outputArray);
	warpPerspective(frame, background, transform, Size(480, 280));
	cvtColor(background, background, CV_BGR2GRAY);

	int height = background.rows;
	click.height = height;
	int width = background.cols;
	click.width = width;
	//



	while (1) {
		cap >> frame;
		if (frame.empty()) break;

		//transformation
		transform = getPerspectiveTransform(inputArray, outputArray);
		warpPerspective(frame, transformed_frame, transform, Size(480, 280));

		foreground = FindForeground(background, transformed_frame);
		fingertip = DrawFingertip(foreground, transformed_frame);

		line(transformed_frame, Point(0, 140), Point(480, 140), Scalar(255, 0, 255), 2);  // Draw boundary line between white keys and black keys

		click.finger = fingertip;
		cur_fingertip = fingertip.y;


		if (cur_fingertip - prev_fingertip > 4)
			down = true;
		else if (cur_fingertip - prev_fingertip < 0)
			down = false;


		if (fingertip.y > 210)
		{
			whiteNum += 1;
		}
		else
		{
			whiteNum = 0;
		}

		if (whiteNum > 3 && down)
		{
			click.whitePressed = true;
		}
		else
		{
			click.whitePressed = false;
		}


		if (fingertip.y >= 90 and fingertip.y <= 140)
		{
			blackNum += 1;
		}
		else
		{
			blackNum = 0;
		}

		if (blackNum > 3 and down)
		{
			click.blackPressed = true;
		}
		else
		{
			click.blackPressed = false;
		}

		prev_fingertip = cur_fingertip;

		switchfunc(click);

		imshow("transformed_frame", transformed_frame);
		imshow("frame", frame);
		waitKey(1000 / fps);
	}
}