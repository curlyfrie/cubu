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

	returnVector.push_back(new cubuButton(500,700,"button1"));
	returnVector.push_back(new cubuButton(700,700,"button2"));
	returnVector.push_back(new cubuButton(900,700,"button3"));
	
	return returnVector;
	/*
	// draw the buttons
	ofSetColor(233, 0, 0);
	cubuButton* currentbutton;
	for(int i = 0; i < buttonVector.size(); i++){
		currentbutton = buttonVector.at(i);
		ofFill();
		if(currentbutton->selected)
			ofSetColor(238,0,0);
		else if(currentbutton->selected)
			ofSetColor(100,0,0);
		else
			ofSetColor(105,105,105);
		ofRect(currentbutton->x, currentbutton->y, currentbutton->width, currentbutton->height);
		ofSetColor(255, 255, 255);
		buttonlabel.drawString(currentbutton->label, currentbutton->x+currentbutton->height/2, currentbutton->y+currentbutton->width/4);
	}
	*/
	

}

void Display::drawRoomservice( vector<cubuButton*> * todraw){

}

void Display::click(int x, int y){
//check if any button was hit and call the corresponding action

	
}