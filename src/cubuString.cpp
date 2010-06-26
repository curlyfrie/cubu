/*
 *  CubuString.cpp
 */

#include "cubuString.h"

cubuString::cubuString(){
	
	setDefaultValues();
}

cubuString::cubuString( std::string ptext, float px, float py, std::string pfont, int psize){
	
	x = px;
	y = py;
	text = ptext;
	font.loadFont(pfont,psize);
}

cubuString::cubuString( std::string ptext, float px, float py){
	
	x = px;
	y = py;
	text = ptext;
	font.loadFont("frabk.ttf",100);
	
}


void cubuString::setDefaultValues(){
	
	x = 100;
	y = 400;
	text = "TEST";
	font.loadFont("frabk.ttf",100);
}