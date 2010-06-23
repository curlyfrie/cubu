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
	
	setDefaultValues();
}

cubuButton::cubuButton(int px, int py){
	
	x = px;
	y = py;
	
	setDefaultValues();
	
}

void cubuButton::setDefaultValues(){
	
	selected = false;
	height = 50;
	width = 150;
}

void cubuButton::select(bool value){
	selected = value;
}