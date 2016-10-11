#include <iostream>
#include <iomanip>
#include <sstream>
#include <opencv2/opencv.hpp>
#include "grabcut.hpp"

using namespace std;
using namespace cv;

int main (int argc, char * const argv[]) {
    
	// assumes a continous video sequence in the form of jpegs
	// assumes a certain directory path from root
	
	string root = "/Users/Harsha/Documents/dataset/";
	string basename = "ASAP";
	string img_prefix = root + "img/" + basename + "/";
	string msk_prefix = root + "mask/"+ basename + "/";
	
	stringstream ss;
	
	ss.str("");
	ss << "mkdir -p " + root + "/mask/" + basename;
	system(ss.str().c_str());
	
	GrabCut gb;
	
	vector<int> q(2,100);
	q[0]=1;
	
	int f = 100;		// starting frame of the video
	while(1)
	{
		f+=1;			// use every 1 frame
		
		ss.str("");
		ss << img_prefix << setw(8) << setfill('0') << f << ".jpg";
		cout <<"Opening: " << ss.str() << endl;
		
		Mat img = imread(ss.str());
        if(!img.data) {cout <<"no image data " << ss.str() << endl; continue;} // break
		
		Mat mask;
		gb.run(img,mask);
		
		ss.str("");
		ss << msk_prefix << setw(8) << setfill('0') << f << ".jpg";
		imwrite(ss.str(),mask,q);
		
	}
	
	
	
	
    return 0;
}
