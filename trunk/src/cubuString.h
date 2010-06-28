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
	void appendString(std::string text2);
	std::string str_replace (std::string rep, std::string wit, std::string in);

	~cubuString();
	
private:
	void setDefaultValues();


};