# Grabcut
Labeling tool for machine vision based segmentation tools


# Instructions

## Dependencies
### IDE
This project is ported to work in Apple's [Xcode]
Hand Tracker uses Xcode which can be installed from the Mac App Store [here](https://developer.apple.com/xcode/downloads/).

This project also uses the OpenCV library (Version 2.4.13 or 2.4.12) for C++. 
### Installing OpenCV on OS X
Two ways to install OpenCV on OS X: 
  1. Using [Homebrew](http://brew.sh), from the terminal: 
  ```
	brew update
	brew tap homebrew/science
	brew install opencv
	```
  	
  	* Make sure OpenCV's dependencies are also installed, you can check using `brew info opencv`
  2. Downloading [OpenCV](http://opencv.org/downloads.html) and building it using [cMake](https://cmake.org/download/)
  	* [This tutorial](http://blogs.wcode.org/2014/10/howto-install-build-and-use-opencv-macosx-10-10/) provides greater detail for setting up OpenCV with cMake and Xcode.

## Project Installation
To install the Hand Tracking project, complete the following steps.

1. Clone this repository: `git clone https://github.com/cmuartfab/handtrack.git`

2. Double click `HandTracker.xcodeproj` to open it in Xcode

3. In Xcode, right click on `HandTracker.xcodeproj` and select `add files to Hand Tracker`.
4. When the file window pops up, press `/` to open the folder option. Type in `usr/local/lib` and hit Go.
5. When in the usr/local/lib folder, **select all** of the *libopencv.dylib* files 
4. Before you click add:
	* Make sure `Add to targets: Hand Tracker` is selected.
	* Make sure `Added Folder: Create Groups` is selected.
5. Click Add. You should see all the `libopencv.dylib` files in the HandTracker project folder. 
6. In Xcode, click on `HandTracker.xcodeproj` to open the build settings.
7. Under *targets* on the left column, select HandTracker.
8. Make sure `Library Search Paths` points to where OpenCV is installed on your machine.
	* If you used Homebrew, it should be in `usr/local/Cellar`

## Running the Xcode project

1. Clone the repository
2. Download the dataset (images and masks) from https://drive.google.com/drive/folders/0B4-8y_10KGM8S25rWlRKYXdNeFU?usp=sharing
3. Update the following line (Line 15) in grabcut/main.cpp:

```
string root = "/xxx/dataset/";	//Update this line to the absolute path of dataset location
```

Modify root to the absolute path where the dataset (images) is stored

4. To label and generate masks for new images, add new images to 'dataset/img/ASAP/' and name them using the following convention '00000xxx.jpg', using the next unused number from the images

## Dependencies
1. This is an Xcode project. It can be installed from the Mac App Store. https://itunes.apple.com/us/app/xcode/id497799835?mt=12
2. The project also requires OpenCV. Install version 2.4.13 or 2.4.12. http://opencv.org/downloads.html. Place the directory in a path without any spaces.
3. You will need to tell Xcode where to find the OpenCV libraries before you will be able to build the project successfully. 
4. You will need the CMake software, and follow the instructions here: http://blogs.wcode.org/2014/10/howto-install-build-and-use-opencv-macosx-10-10/
5. Assign the search paths to the OpenCV libraries and link the libraries in Xcode. Follow instructions here: http://blogs.wcode.org/2014/10/howto-install-build-and-use-opencv-macosx-10-10/
6. Alternatively, you can install OpenCV using a different method and link the libraries in Xcode. 


