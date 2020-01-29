#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

#include "FileIo.h"

using namespace std;

using namespace cv;


void ShowConsole(string str) {
	cout << str << "\n";
}

// 画像を表示
void ShowImage(Mat image) {
	imshow("ShowImage", image);
	waitKey(0);
}


int main() {	
	FileIo io;
//	io.SetRootFilePath();

	// 貼り付け元の画像
	string base_image_file_path = io.GetRootFilePath() + "\\pub_tenshiFD00_800x600.bmp";

	// 貼り付ける画像
	string paste_image_file_path = io.GetRootFilePath() + "\\sample.png";



	Mat base_image = cv::imread(base_image_file_path, 1);
	Mat paste_image = cv::imread(paste_image_file_path, -1);

	Mat black_mat = cv::Mat::zeros(base_image.rows, base_image.cols, CV_8UC4);

	ShowImage(base_image);
	ShowImage(paste_image);

	vector<Mat> no_alpha_channels;	
	Mat alpha_channel;
	Mat no_alpha_channel;

	Mat roi = black_mat(cv::Rect(0, 0, paste_image.cols, paste_image.rows));


	
	paste_image.copyTo(roi);	// ここで張り付けられた。

	ShowImage(black_mat);
	ShowImage(paste_image);

	cv::split(black_mat,no_alpha_channels);

	alpha_channel = no_alpha_channels.back();	// アルファチャンネルのみ
	no_alpha_channels.pop_back();				// 最後を削除
	cv::merge(no_alpha_channels, no_alpha_channel);	// アルファチャンネル以外をマージ

	cv::cvtColor(alpha_channel, alpha_channel, COLOR_GRAY2BGR);// チャンネルを１→３に追加

	// 透過画像処理
	int roi_size_x = base_image.rows;
	int roi_size_y = base_image.cols;

	double angle = 90;
	double scale = 0.6;
	Mat affine = cv::getRotationMatrix2D(Point(paste_image.cols / 2, paste_image.rows / 2), angle, scale);

	cv::warpAffine(no_alpha_channel, no_alpha_channel, affine, Size(roi_size_y, roi_size_x));
	cv::warpAffine(alpha_channel, alpha_channel, affine, Size(roi_size_y, roi_size_x));
	ShowImage(no_alpha_channel);
	ShowImage(alpha_channel);

	Mat roi_image(base_image, Rect(0, 0, roi_size_y, roi_size_x));
	
	no_alpha_channel.copyTo(roi_image,alpha_channel);
	
	ShowImage(roi_image);


//	Mat affine = cv::getRotationMatrix2D(Point(base_image_size_x/2, base_image_size_y/2), 30, 1.0);

//	cv::warpAffine(base_image, base_image, affine, Size(base_image_size_y, base_image_size_x));
	ShowImage(base_image);

}