# Grabcut
Labeling tool for machine vision based segmentation tools


# Instructions
## Running the Xcode project

1. Clone the repository, and check the project out as an existing project in Xcode
2. Download the dataset (images and masks) from https://drive.google.com/drive/folders/0B4-8y_10KGM8S25rWlRKYXdNeFU?usp=sharing
3. Update the following line (Line 15) in grabcut/main.cpp:

```
string root = "/xxx/dataset/";	//Update this line to the absolute path of dataset location
```
...Modify root to the absolute path where the dataset (images) is stored..

4. To label and generate masks for new images, add new images to 'dataset/img/ASAP/' and name them using the following convention '00000xxx.jpg', using the next unused number from the images

## Dependencies
1. This is an Xcode project. It can be installed from the Mac App Store. https://itunes.apple.com/us/app/xcode/id497799835?mt=12
2. The project also requires OpenCV. Install version 2.4.13 or 2.4.12. http://opencv.org/downloads.html. Place the directory in a path without any spaces.
3. You will need to tell Xcode where to find the OpenCV libraries before you will be able to build the project successfully. 
4. You will need the CMake software, and follow the instructions here: http://blogs.wcode.org/2014/10/howto-install-build-and-use-opencv-macosx-10-10/
5. Assign the search paths to the OpenCV libraries and link the libraries in Xcode. Follow instructions here: http://blogs.wcode.org/2014/10/howto-install-build-and-use-opencv-macosx-10-10/
6. Alternatively, you can install OpenCV using a different method and link the libraries in Xcode. 


