#include "stdafx.h"
#include <iostream>
#include "image.h"

image::image() 
{
	pixels = NULL;
	width = 0;
	height = 0;
}

image::image(string filename) 
{
	pixels = NULL;
	width = 0;
	height = 0;
	loadImage(filename);
}

image::~image()
{
	if(pixels)
	{
		for(int i=0; i<height; i++)
			delete [] pixels[i];
		delete [] pixels;
		pixels = NULL;
		width = 0;
		height = 0;
	}
}

int image::getWidth()
{
	return width;
}

int image::getHeight()
{
	return height;
}

pixel** image::getPixels()
{
	return pixels;
}

void image::createNewImage(int width, int height)
{
	if(this->pixels)
	{
		for(int i=0; i<this->height; i++)
			delete [] this->pixels[i];
		delete [] this->pixels;
		this->pixels = NULL;
		this->width = 0;
		this->height = 0;
	}

	this->width = width;
	this->height = height;
	
	pixels = new pixel*[height];
	for (int j = 0; j < height; j++)
		pixels[j] = new pixel[width];
}

void image::viewImage(CImage* myImage)
{
	pixelsToCImage(myImage);
	return;
}

bool image::loadImage(string filename)
{
	if(pixels)
	{
		for(int i=0; i<height; i++)
			delete [] pixels[i];
		delete [] pixels;
		pixels = NULL;
		width = 0;
		height = 0;
	}
	
	CImage myImage;
	CString cs(filename.c_str());
	myImage.Load(cs);
	
	if(myImage.IsNull())
	{
		cout << "The requested image could not be loaded." << endl;
		return false;
	}
	if(myImage.GetBPP() != 24) 
	{
		cout << "The input image must be stored in the 8 bit RGB (24 bpp) colorspace." << endl;
		return false;
	}

	width = myImage.GetWidth();
	height = myImage.GetHeight();

	pixels = new pixel*[height];
	uchar* imageBuf = (uchar*)myImage.GetBits();
	int scanline = myImage.GetPitch();

	for (int j = 0; j < height; j++) 
	{
		pixels[j] = new pixel[width];	
		for (int i = 0; i < width; i++) 
		{
			pixels[j][i].red = imageBuf[j*scanline+i*3+2];
			pixels[j][i].green = imageBuf[j*scanline+i*3+1];
			pixels[j][i].blue = imageBuf[j*scanline+i*3];
		}
	}
	return true;
}

void image::pixelsToCImage(CImage* myImage)
{
	myImage->Create(width, height, 24, 0);
	if (myImage->IsNull()) {
		cout << "An error occured when creating a new image!" << endl;
		return;
	}

	uchar* imageBuf = (uchar*)myImage->GetBits();
	int scanline = myImage->GetPitch();
	for (int j = 0; j < height; j++) 
		for (int i = 0; i < width; i++) 
		{
			imageBuf[j*scanline+i*3] = pixels[j][i].blue;
			imageBuf[j*scanline+i*3+1] = pixels[j][i].green;
			imageBuf[j*scanline+i*3+2] = pixels[j][i].red;
		}
}

void image::saveImage(string filename) 
{
	if(!pixels)
	{
		cout << "No image data has been created to save! (The pixel buffer is empty)" << endl;
		return;
	}

	CImage myImage;
	pixelsToCImage(&myImage);

	CString cs(filename.c_str());
	myImage.Save(cs);

	return;
}