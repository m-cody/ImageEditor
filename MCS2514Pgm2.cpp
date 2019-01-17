/*
	MCS2514Pgm2.cpp : main project file.  
	Author:  Mary Cody
	Completion Date: 

	This file should interface with the supplied windows GUI interface to allow images to be resampled to smaller sizes and be tinted.
	Please read the included Project Specification for more detailed descriptions of the project.

	In this assignment, we will be laying the foundation for a larger photo-mosiac project.  
	We will be finding the average color in a larger block of pixels (aka re-sampling).  
	This technique is often used to generate smaller versions of big images.  (think of a thumbnail of the original image)  
	
	In this assignment we will be writing a program that can:

	1.)Allow simple loading and saving of images.
	2.)Break a loaded image up into blocks of a given width and height and find the average color in that block.
	3.)Create a new image from the process in 2 that will consist of 1 pixel per every block analyzed in the first image.
	4.)Apply a red, green, or blue tint to an image by increasing the appropriate RGB values to every pixel in the image.
	5.)Invert the individual RGB color components of an image.
	

	The functions in this file should be completed as follows:

bool loadImageFromFile(string filename)
		INPUTS: a string containing a path to a file to open.  This value is returned from the 
		user's selection in the open file dialog.
		OUTPUTS: a boolean indicating whether or not the image could be opened correctly.

void saveImageToFile(string filename)
		INPUTS: a string containing a path to save the current image out to.
		OUTPUTS: NONE

image* displayImage()
		INPUTS: NONE
		OUTPUTS: This function should return a pointer to the image object that is currently being viewed on the screen.  
		If a user has loaded an image correctly, you should return a pointer to an image object containing the base image.  
		If a user has used the shrink button (aka averageRegions function) or performed any of the red/green/blue filters, 
		you should of course return a pointer to an image object that reflects these changes.

void averageRegions(int blockWidth, int blockHeight)
		INPUTS: Integers indicating the width and height of the blocks?to be averaged
		OUTPUTS: NONE
		When this function is called, you should create a new image that will consist of 1 pixel for every block of size 
		blockWidth by blockHeight pixels in the original image, with each pixel being the average color of the pixels in that 
		region in the original image.
		Please note that it may be easier if you split this into 2 functions and call your helper function from within this one.  
		The second function could then just calculate the average value of a block of pixels given to it, and return that 
		to the original function to be used.  However, this implementation is up to you!  Complete it as you see fit.

void increaseRedValues(int value)
		INPUTS: An integer indicating the amount to increase the red component of each pixel.
		OUTPUTS: NONE
		When this function is called, you should take the current image and increase the red component of each 
		pixel in the image by the amount specified.  Please note that an RGB value has a maximum of 255 and a minimum of 0.

void increaseGreenValues(int value)
		INPUTS: An integer indicating the amount to increase the green component of each pixel.
		OUTPUTS: NONE
		When this function is called, you should take the current image and increase the green component of each pixel 
		in the image by the amount specified.  Please note that an RGB value has a maximum of 255 and a minimum of 0.

void increaseBlueValues(int value)
		INPUTS: An integer indicating the amount to increase the blue component of each pixel.
		OUTPUTS: NONE
		When this function is called, you should take the current image and increase the blue component of each pixel
		in the image by the amount specified.  Please note that an RGB value has a maximum of 255 and a minimum of 0.
		
void grayImage( )
		INPUTS: NONE
		OUTPUTS: NONE
		When this function is called you should convert the current image to gray image.
		For each pixel, you calculate the average of aver = (R+G+B)/3, then replace the 
		pixel value using (aver,aver,aver) for R, G, B values. 

void addNoise()
		INPUTS: NONE
		OUTPUTS: NONE
		When this function is called you should randomly replace 10% of the pixels with noises in the current image. To create
		the noise, you should also randomly generate the R,G,B values for the noise pixel.

Bonuse function (30 points)
		void deNoise()
		INPUTS: NONE
		OUTPUTS: NONE
		When this function is called you should denoise the image to remove the noise.
		In order to remove the noise, you need to travel every single pixel. For every pixel,
		you calculate the average pixel from its neighbor (you can use a n*n block for its 
		neighbor, n can be changed). Then replace the pixel by average neighbor pixel.

*/

#include "stdafx.h"  //needed for the Windows display
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

#include "globals.h"  //some global variables are included here
#include "pixel.h"  //includes the pixel class for storing individual pixels
#include "image.h"	//includes the image class we will be using.

image edit;
//declare your global variables here!


//load the image from a file and return the result
bool loadImageFromFile(string filename)
{
	return edit.loadImage(filename);
}

//save an image to a file
void saveImageToFile(string filename)
{
	edit.saveImage(filename);
	return;
}

//return a pointer to your image object!
image* displayImage()
{
	return &edit;
}

//make a new image that is a smaller resampling of the bigger image
void averageRegions(int blockWidth, int blockHeight)
{
	int imageWidth = edit.getWidth();
	int imageHeight = edit.getHeight();
	int newWidth = edit.getWidth() / blockWidth;
	int newHeight = edit.getHeight() / blockHeight;
	
	pixel** oldData = new pixel*[imageHeight];
	pixel** editData = edit.getPixels();

	for (int i = 0; i < imageHeight; i++)
	{
		oldData[i] = new pixel[imageWidth];
		for (int j = 0; j < imageWidth; j++)
		{
			oldData[i][j] = editData[i][j];
		}
	}

	edit.createNewImage(newWidth, newHeight);

	editData = edit.getPixels();

	for (int i = 0; i < newHeight; i++)
	{
		for (int j = 0; j < newWidth; j++)
		{
			int red = 0, green = 0, blue = 0;
			for (int y = 0; y < blockHeight; y++)
			{
				for (int x = 0; x < blockWidth; x++)
				{
					red += oldData[i * blockHeight + y][j * blockWidth + x].red;
					green += oldData[i * blockHeight + y][j * blockWidth + x].green;
					blue+= oldData[i * blockHeight + y][j * blockWidth + x].blue;
				}
			}
			editData[i][j].red = red / (blockHeight * blockWidth);
			editData[i][j].green = green / (blockHeight * blockWidth);
			editData[i][j].blue = blue / (blockHeight * blockWidth);
		}
	}

	for (int i = 0; i < imageHeight; i++)
	{
		delete oldData[i];
	}
	delete oldData; //no memory leak. WHOO!
}

//increase the red component of each pixel in the image
void increaseRedValues(int value)
{
	pixel** data = edit.getPixels();
	for (int i = 0; i < edit.getHeight(); i++)
	{
		for (int j = 0; j < edit.getWidth(); j++)
		{
			if (data[i][j].red > 255 - value)
			{
				data[i][j].red = 255;
			}
			else
			{
				data[i][j].red += value;
			}
		}
	}
}

//increase the green component of each pixel in the image
void increaseGreenValues(int value)
{
	pixel** data = edit.getPixels();
	for (int i = 0; i < edit.getHeight(); i++)
	{
		for (int j = 0; j < edit.getWidth(); j++)
		{
			if (data[i][j].green > 255 - value)
			{
				data[i][j].green = 255;
			}
			else
			{
				data[i][j].green += value;
			}
		}
	}
}

//increase the blue component of each pixel in the image
void increaseBlueValues(int value)
{
	pixel** data = edit.getPixels();
	for (int i = 0; i < edit.getHeight(); i++)
	{
		for (int j = 0; j < edit.getWidth(); j++)
		{
			if (data[i][j].blue > 255 - value)
			{
				data[i][j].blue = 255;
			}
			else
			{
				data[i][j].blue += value;
			}
		}
	}
}

//invert the color components of each pixel in the image
void grayImage()
{
	pixel** data = edit.getPixels();
	int pixelValue;
	for (int i = 0; i < edit.getHeight(); i++)
	{
		for (int j = 0; j < edit.getWidth(); j++)
		{
			pixelValue = data[i][j].red;
			pixelValue += data[i][j].green;
			pixelValue += data[i][j].blue;
			pixelValue /= 3;
			data[i][j].red = pixelValue;
			data[i][j].green = pixelValue;
			data[i][j].blue = pixelValue;
		}
	}
}

void addNoise()
{
	srand(time(NULL));

	int noiseTotal = (edit.getHeight() * edit.getWidth()) / 10;
	pixel** newData = edit.getPixels();

	for (int i = 0; i < noiseTotal; i++)
	{
		int x = rand() % edit.getWidth();
		int y = rand() % edit.getHeight();

		newData[y][x].red = rand() % 255;
		newData[y][x].green = rand() % 255;
		newData[y][x].blue = rand() % 255;
	}
}

void deNoise()
{
	pixel** data = edit.getPixels();
	int yStart, xStart, yEnd, xEnd;

	for (int y = 0; y < edit.getHeight() - 1; y++)
	{
		for (int x = 0; x < edit.getWidth() - 1; x++)
		{
			if (y == 0)
			{
				yStart = y;
				yEnd = y + 1;
			}
			else if (y == edit.getHeight() - 1)
			{
				yStart = y - 1;
				yEnd = y;
			}
			else
			{
				yStart = y - 1;
				yEnd = y + 1;
			}

			if (x == 0)
			{
				xStart = x;
				xEnd = x + 1;
			}
			else if (x == edit.getWidth() - 1)
			{
				xStart = x - 1;
				xEnd = x;
			}
			else
			{
				xStart = x - 1;
				xEnd = x + 1;
			}

			int red = 0, green = 0, blue = 0;
			for (int i = yStart; i <= yEnd; i++)
			{
				for (int j = xStart; j <= xEnd; j++)
				{
					red += data[i][j].red;
					green += data[i][j].green;
					blue += data[i][j].blue;
				}
			}
			data[y][x].red = red / 9;
			data[y][x].green = green / 9;
			data[y][x].blue = blue / 9;
		}
	}
}

