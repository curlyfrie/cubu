/*
 *  CubuButton.cpp
 *  cubu
 *
 *  Created by Patrick Stipsits on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "cubuButton.h"

cubuButton::cubuButton(){
	
	x = 0;
	y = 0;
	label = "";
	
	setDefaultValues();
}

cubuButton::cubuButton(int px, int py, std::string plabel){
	
	x = px;
	y = py;
	label = plabel;
	
	setDefaultValues();
	
}

void cubuButton::setDefaultValues(){
	
	selected = false;
	height = 30;
	width = 80;
}

void cubuButton::select(bool value){
	selected = value;
}

bool cubuButton::click(int clickx, int clicky){
// return true if click was on this button
// if so: set select on true
	
	/*

	
	bool returnvalue = false;
	//cout << "deine mutter";
	//cout << "x+height" << x + height << endl;
	//cout << "y+width" << y + width << endl;
	
	
	if(x < clickx && clickx < x + height)
		returnvalue = true;
	else
		returnvalue = false;
	
	if(y < clicky && clicky < y + width)
		returnvalue = true;
	else
		returnvalue = false;
	
	// make button selected if click has hit
	selected = returnvalue;
	
	return returnvalue;
		*/
	
	
	if(clickx < x)
		return true;
	else 
		return false;
}