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


void Display::draw(std::string pguiname, vector<cubuButton*> * button, vector<cubuString*> * string){
	
	guiname = pguiname;
	
	if(guiname == "roomservice1"){
		button->push_back(new cubuButton(500,700,"deinemutter"));
		button->push_back(new cubuButton(700,700,"button2"));
		button->push_back(new cubuButton(900,700,"button3"));

		string->push_back(new cubuString("TEST", 100, 100,"verdana.ttf", 32));
		string->push_back(new cubuString("TEST", 300, 100,"brit.ttf", 32));
		string->push_back(new cubuString("AAAA", 100, 300));
	}


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