/*
 *  cubuPic.h
 *  cubu
 *
 *	Pics to draw in GUI
 */

#include <iostream>
#include "ofImage.h"

class cubuPic {
	
public:
	float x;
	float y;

	std::string img;

	ofImage pic;

	cubuPic();
	cubuPic(std::string pimg, float px, float py);
	~cubuPic();
	
};