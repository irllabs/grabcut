/*
 *  grabcut.h
 *  HandDetectionDemo
 *
 *  Created by Kris Kitani on 3/21/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static void wevents( int e, int x, int y, int flags, void* ptr );


class GrabCut
{
public:
	
	GrabCut();
	
	void	run(Mat img, Mat &msk);
	void	show();
	Mat		getFG();
	Mat		getBinMask();
	
	void	events( int e, int x, int y, int flags);
	
	
	Mat _gcut;
	int _mode;
	Mat _src;
	Mat _bin;
	Mat _tmp;
	Mat _mask;
	Mat _fgd;
	Mat _bgd;
	Mat _dsp;
	
	Point _pt;
	Point lstart;
	Point rstart;
	bool ldrag;
	bool rdrag;
	//int lab;
	
	string _name;
	
	
};

GrabCut::GrabCut()
{
	_mode=GC_FGD;
}	

void GrabCut::run(Mat img, Mat &msk)
{
	cout << "run grabcut" << endl;
	
	_src	= img;
	_mask	= Mat::ones(_src.size(),CV_8UC1)*GC_PR_BGD;
	_bin	= Mat::zeros(_src.size(),CV_8UC1);
	

	cout << "GC_BGD " << GC_BGD <<endl;				// 0
	cout << "GC_FGD " << GC_FGD <<endl;				// 1
	cout << "GC_PR_BGD " << GC_PR_BGD <<endl;		// 2
	cout << "GC_PR_FGD " << GC_PR_FGD <<endl;		// 3
	
	
	
	
	_name = "graphcut";
	namedWindow(_name);
	
	setMouseCallback(_name, wevents,this);
	
	Rect roi(0,0,_src.cols,_src.rows);
	_dsp = Mat::zeros(_src.rows*2,_src.cols*2,CV_8UC3);
	_src.copyTo(_dsp(roi));
	//_dsp(roi) = _src.clone();
	
	cout << "loop" << endl;
	while(1)
	{
		imshow(_name,_dsp);
		char c = waitKey(1);				// 
		
		if(c=='d')							// done
		{			
			msk = _bin*1.0;					// output
			break;
		}
		else if(c=='f') _mode = GC_FGD;		// forground mode
		else if(c=='b') _mode = GC_BGD;		// background mode
		else if(c=='r')						// reset
		{
			_src.copyTo(_dsp(roi));			// 
			_mask	= GC_PR_BGD;
			_gcut	= GC_PR_BGD;
			show();
		}
	}
	
	destroyWindow(_name);
}


void GrabCut::show()
{

	Scalar fg_color(255,0,0);
	Scalar bg_color(0,255,0);
	cv::Mat scribbled_src = _src.clone();
	const float alpha = 0.7f;
		
	for(int y=0; y < _gcut.rows; y++){
		for(int x=0; x < _gcut.cols; x++){
			if(_gcut.at<uchar>(y, x) == cv::GC_FGD) {
				cv::circle(scribbled_src, cv::Point(x, y), 2, fg_color, -1);
			} 
			else if(_gcut.at<uchar>(y, x) == cv::GC_BGD) {
				cv::circle(scribbled_src, cv::Point(x, y), 2, bg_color, -1);
			} 
			else if(_gcut.at<uchar>(y, x) == cv::GC_PR_BGD) {
				cv::Vec3b& pix = scribbled_src.at<cv::Vec3b>(y, x);
				pix[0] = (uchar)(pix[0] * alpha + bg_color[0] * (1-alpha));
				pix[1] = (uchar)(pix[1] * alpha + bg_color[1] * (1-alpha));
				pix[2] = (uchar)(pix[2] * alpha + bg_color[2] * (1-alpha));
			} 
			else if(_gcut.at<uchar>(y, x) == cv::GC_PR_FGD) {
				cv::Vec3b& pix = scribbled_src.at<cv::Vec3b>(y, x);
				pix[0] = (uchar)(pix[0] * alpha + fg_color[0] * (1-alpha));
				pix[1] = (uchar)(pix[1] * alpha + fg_color[1] * (1-alpha));
				pix[2] = (uchar)(pix[2] * alpha + fg_color[2] * (1-alpha));
			}
		}
	}
	
	Rect roi;
	
	Mat scrb;
	roi = Rect(_src.cols,0,_src.cols,_src.rows);
	scribbled_src.copyTo(_dsp(roi));
	
	
	Mat fg = getFG();
	roi = Rect(_src.cols,_src.rows,_src.cols,_src.rows);
	fg.copyTo(_dsp(roi));
	
	Mat msk = getBinMask();
	cvtColor(msk,msk,COLOR_GRAY2BGR);
	roi = Rect(0,_src.rows,_src.cols,_src.rows);
	msk.copyTo(_dsp(roi));
	
	imshow(_name,_dsp);
	
	
	waitKey(1);
}


Mat GrabCut::getFG()
{
	Mat fg = cv::Mat::zeros(_src.size(), _src.type());
	Mat mask = getBinMask();
	_src.copyTo(fg, mask);
	return fg;
}

Mat GrabCut::getBinMask()
{
	
	Mat binmask(_gcut.size(), CV_8U);
	binmask = _gcut & GC_FGD;
	binmask = binmask * 255;
	
	
	Mat tmp;
	binmask.copyTo(tmp);
	
	vector<vector<Point> > co;
	vector<Vec4i> hi;
	
	binmask *= 0;
	findContours(tmp,co,hi,RETR_EXTERNAL,CHAIN_APPROX_NONE);
	
	for(int i=0;i<co.size();i++){
		if(contourArea(Mat(co[i])) < 50) continue;
		drawContours(binmask, co,i, CV_RGB(255,255,255), CV_FILLED, CV_AA);
	}
	
	binmask.copyTo(_bin);
	
	return binmask;
}


void GrabCut::events( int e, int x, int y, int flags)
{

	_pt = Point(x,y);
	int c;
	switch(e) {
		case EVENT_LBUTTONDOWN:
			ldrag = true;
			lstart = _pt;
			break;
		case EVENT_LBUTTONUP:
			ldrag = false;
			_tmp = _mask & GC_FGD;
			c = countNonZero(_tmp);
			
			if(c>0)
			{
				_mask.copyTo(_gcut);
				cv::grabCut(_src,_gcut,Rect(), _bgd, _fgd, 1, cv::GC_INIT_WITH_MASK);
				show();
			}
			break;
		case EVENT_MOUSEMOVE:
			
			if(ldrag) 
			{
				line(_mask,lstart, _pt, Scalar(_mode), 1);
				
				if(_mode==GC_FGD)		line(_dsp,lstart, _pt,CV_RGB(255,0,0), 1);
				else if(_mode==GC_BGD)	line(_dsp,lstart, _pt,CV_RGB(0,255,0), 1);
				
				lstart = _pt;
				//cout << _pt << endl;
			}
			break;
		default:
			break;
	};
	
	//cout << "eventout" << endl;
}

static void wevents( int e, int x, int y, int flags, void* ptr )
{
	GrabCut *mptr =  (GrabCut*)ptr;
	
	if(mptr != NULL) mptr->events(e,x,y,flags);
	
}