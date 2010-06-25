/*
 *  Display.cpp
 *  cubu
 *
 *  Created by Patrick Stipsits on 25.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Display.h"

Display::Display() {

}

vector<cubuButton*> Display::drawRoomservice(){
//draw the gui for side roomservice
	
	vector<cubuButton*> returnVector;
	
	//update the vector
	buttonVector.clear();

	returnVector.push_back(new cubuButton(500,700,"deinemutter"));
	returnVector.push_back(new cubuButton(700,700,"button2"));
	returnVector.push_back(new cubuButton(900,700,"button3"));
	
	return returnVector;

}

void Display::drawRoomservice( vector<cubuButton*> * todraw){
	/*
	vector<cubuButton*>* returnVector;
	returnVector.push_back(new cubuButton(500,700,"deinemutter"));
	returnVector.push_back(new cubuButton(700,700,"button2"));
	returnVector.push_back(new cubuButton(900,700,"button3"));
	
	todraw = returnVector;
	 */
}

void Display::click(int x, int y){
//check if any button was hit and call the corresponding action

	
}