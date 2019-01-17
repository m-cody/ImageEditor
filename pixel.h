//A POD class (Plain Old Data Class) to hold one pixel's worth of data.  (Assuming the pixel is 24bpp and RGB)
//Note:  Not having getters and setters for the members of a class is only acceptable if you are using it as a Plain Old Data Class.
//If your class has any constructors, destructors, static members, virtual functions, derivations, or anything that is not a public
//data member...then you should follow the conventions we have practiced in class.  We are using a POD class in this case because it
//simplifies the usage of the pixel object as well as keeps it's memory footprint tiny (as we will have MANY of these classes loaded
//into memory at a given time.)

#ifndef PIXEL_H
#define PIXEL_H

class pixel
{
public:
	unsigned char red;		//the red component
	unsigned char green;	//the green component
	unsigned char blue;		//the blue component
};

#endif