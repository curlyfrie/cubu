/*
 *  cubuButton.cpp
 *  cubu
 *
 *  Created by Patrick Stipsits on 18.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "cubuButton.h"

cubuButton::cubuButton()
{
	id = -1;
	
	x = 1;
	y = 1;
	
	// set color of button
	//	color.a = 1;
	color.r = 123;
	color.g = 123;
	color.b = 123;
	
	// set shape of button
	shape = ofRectangle::ofRectangle();
	shape.width = 100;
	shape.height = 40;
	
}


cubuButton::cubuButton(int px, int py)
{
	id = -1;
	
	x = px;
	y = py;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	
	// set color of button
//	color.a = 1;
	color.r = 123;
	color.g = 123;
	color.b = 123;

	// set shape of button
	shape = ofRectangle::ofRectangle();
	shape.width = 100;
	shape.height = 40;

}