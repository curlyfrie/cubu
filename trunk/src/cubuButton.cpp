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
	menuid = 0;
	setDefaultValues();
}

cubuButton::cubuButton(int px, int py, std::string plabel){
	
	x = px;
	y = py;
	label = plabel;
	
	setDefaultValues();
	
}

cubuButton::cubuButton(int px, int py, std::string plabel, int pmenuid){
	
	x = px;
	y = py;
	label = plabel;
	menuid = pmenuid;
	setDefaultValues();
	
}

int cubuButton::getMenuid() {
	return menuid;
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
	
	
	bool returnvalue = false;
	
	if(x <= clickx && clickx <= x + width)
		returnvalue = true;
	else
		return false;
	
	if(y <= clicky && clicky <= y + height)
		returnvalue = true;
	else
		return false;
	
	// make button selected if click has hit
	selected = returnvalue;
	
	return returnvalue;
		
}