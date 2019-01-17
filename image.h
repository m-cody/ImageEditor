#ifndef IMAGE
#define IMAGE

#include <atlimage.h>
#include <string>
#include <cstdlib>
#include "globals.h"
#include "pixel.h"

using namespace std;

class image {
	public:
		image();			//the image constructor (initializes everything)
		image(string filename);  //a image constructor that directly loads an image from disk
		~image();			//the image destructor  (deletes the dynamically created pixel array)
		
		void createNewImage(int width, int height); //this function deletes any current image data and creates a new blank image
													//with the specified width/height and allocates the needed number of pixels
													//dynamically.
		bool loadImage(string filename);		//load an image from the specified file path.  Return true if it works, false if it is not a valid image.
												//Note that we only accept images of the RGB 8bit colorspace!
		void saveImage(string filename);	   //Save an image to the specified path
		pixel** getPixels();					//return the 2-dimensional pixels array
		int getWidth();						//return the width of the image
		int getHeight();					//return the height of the image

		void viewImage(CImage* myImage);  //This function is called by the windows GUI.  It returns the image in format the GUI understands.
		
			
	private:
		void pixelsToCImage(CImage* myImage);  //this function is called internally by the image class.
												//it converts our pixel struct array to a standard BGR uchar array with word spacing.
												//(Don't worry about what this does)
		pixel** pixels;				// pixel data array for image 
		int width, height;		// stores the image dimensions 
		
		
		

};

#endif