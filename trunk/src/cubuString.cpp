/*
 *  CubuString.cpp
 */

#include "cubuString.h"

cubuString::cubuString(){
	
	setDefaultValues();
}

cubuString::cubuString( std::string ptext, float px, float py, std::string pfont, int psize, int pcolor){
	
	x = px;
	y = py;
	text = ptext;
	color = pcolor;
	font.loadFont(pfont,psize);

}
cubuString::cubuString( std::string ptext, float px, float py, std::string pfont, int psize){
	
	x = px;
	y = py;
	text = ptext;
	color = 0x000000;
	font.loadFont(pfont,psize);

}

cubuString::cubuString( std::string ptext, float px, float py){
	
	x = px;
	y = py;
	text = ptext;
	color = 0x000000;
	font.loadFont("frabk.ttf",100);
	
}

cubuString::cubuString( std::string ptext){
	
	x = 20;
	y = 100;
	text = ptext;
	color = 0x000000;
	font.loadFont("bankg.ttf",32);
	
}

void cubuString::appendString(std::string text2)
{
	text = text + text2;

}
void cubuString::setDefaultValues(){
	
	x = 100;
	y = 400;
	text = "TEST";
	font.loadFont("frabk.ttf",100);
}