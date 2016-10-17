# Grabcut
Labeling tool for machine vision based segmentation tools


# Instructions

## Dependencies
### IDE
This project is ported to work in Apple's [Xcode]

Grabcut uses Xcode 7.3.1 or later which can be installed from the Mac App Store [here](https://developer.apple.com/xcode/downloads/).

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
To install the Grabcut project, complete the following steps.

1. Clone this repository: `https://github.com/cmuartfab/grabcut.git`

2. Double click `grabcut.xcodeproj` to open it in Xcode

3. Navigate to the /usr/local/lib directory and **select all** of the *libopencv.dylib* files and drag and drop them into the lib folder in the Xcode project

4. You should see all the `libopencv.dylib` files in the Grabcut project lib folder. 
5. In Xcode, click on `grabcut.xcodeproj` to open the build settings.
6. Under *targets* on the left column, select grabcut.
7. Make sure `Library Search Paths` points to where OpenCV is installed on your machine.
	* If you used Homebrew, it should be in `usr/local/Cellar`

## Running the Xcode project

1. Clone the repository
2. Double click on grabcut.xcodeproj to open the project in Xcode
3. Update the following line (Line 15) in grabcut/main.cpp:

```
string root = "/xxx/dataset/";	//Update this line to the absolute path of dataset location
```

Modify root to the absolute path where the dataset (images) is stored

4. To label and generate masks for new images, add new images to 'dataset/img/ASAP/' and name them using the following convention '00000xxx.jpg', using the next unused number from the images

5. Use the following key controls to select modes when generating the masks:

..* 'b' - Background Mode: Use your mouse to click and draw the background outline around the foreground object (Green)
..* 'f' - Foreground Mode: Use your mouse to click and draw a few lines on the foreground object (Red)
..* 'd' - Done: Indicate to move on to the next image
..* 'r' - Reset: Indicate to start over

The image below shows an example of the background (green) and foreground (red) lines and the mask generated, as well as the mask applied to the image:

![alt tag](https://raw.githubusercontent.com/cmuartfab/grabcut/blob/master/instructions_grabcut_controls.png)



