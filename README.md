# Grabcut
Labeling tool for machine vision based segmentation tools


# Instructions
## Running the Xcode project

1. Clone the repository, and check the project out as an existing project in Xcode
2. Download the dataset (images and masks) from https://drive.google.com/open?id=0B4-8y_10KGM8S25rWlRKYXdNeFU (Request permission if unable to download)
3. (TODO - Change to use properties file) Navigate to grabcut/main.cpp
4. Update Line 15, root to the path where the dataset (images) is stored
5. To label and generate masks for new images, add new images to 'dataset/img/ASAP/' and name them using the following convention '00000xxx.jpg', using the next unused number from the images


