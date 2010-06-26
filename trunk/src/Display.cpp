/*
 *  Display.cpp
 *  cubu
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "cubu.h"

Display::Display() {

}

Display::~Display()
{
	// exit should do the same stuff
}

void Display::draw(std::string pguiname, vector<cubuButton*> * button, vector<cubuString*> * string){
	
	guiname = pguiname;
	
	if(guiname == "roomservice1"){
		button->push_back(new cubuButton(400,150,"Do not Disturb"));
		button->push_back(new cubuButton(400,200,"Towels"));
		button->push_back(new cubuButton(400,250,"Clean Up"));

	//	string->push_back(new cubuString("TEST", 100, 100,"verdana.ttf", 32));
	//	string->push_back(new cubuString("TEST", 300, 100,"brit.ttf", 32));
	//	string->push_back(new cubuString("AAAA", 100, 300));
	}

	else if (guiname == "alarm1") {
	
	}
	else if (guiname == "activities1") {
		button->push_back(new cubuButton(400,150,"Wellness"));
		button->push_back(new cubuButton(400,200,"Beauty"));
		button->push_back(new cubuButton(400,250,"Sports"));
	
	}
	else if (guiname == "fun1") {
		
	
	}
	else if (guiname == "food1") {
		button->push_back(new cubuButton(400,150,"Drinks"));
		button->push_back(new cubuButton(400,200,"Wine"));
		button->push_back(new cubuButton(400,250,"Menu"));
	
	}	
	else if (guiname == "Drinks") {
		button->clear();
		string->push_back(new cubuString("Drinks", 100, 100,"verdana.ttf", 32));
	
	}
	else if (guiname == "Wine") {
		button->clear();
		string->push_back(new cubuString("The Wine List", 100, 100,"verdana.ttf", 32));
	
	}
	else if (guiname == "Menu") {
		button->clear();
		string->push_back(new cubuString("The Menu", 100, 100,"verdana.ttf", 32));
		
	
	}
	else if (guiname == "temperature1") {
		
	
	}
	else {
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