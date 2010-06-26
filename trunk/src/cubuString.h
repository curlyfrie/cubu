/*
 *  cubuString.h
 *  cubu
 *
 *	Strings to draw in GUI
 */

#include <iostream>
#include "ofMain.h"

class cubuString {
	
public:
	float x;
	float y;

	int color;

	std::string text;

	ofTrueTypeFont font;

	
	cubuString();
	cubuString(std::string ptext, float px, float py, std::string pfont, int psize, int pcolor);
	cubuString(std::string ptext, float px, float py, std::string pfont, int psize);
	cubuString(std::string ptext, float px, float py);
	cubuString(std::string ptext);
	~cubuString();
	
private:
	void setDefaultValues();
};