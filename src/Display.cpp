/*
 *  Display.cpp
 *  cubu
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "cubu.h"

Display::Display() {
	dbhandler = new DBHandler();

}

Display::~Display()
{
	// exit should do the same stuff
}

void Display::draw(std::string pguiname, vector<cubuButton*> * button, vector<cubuString*> * string, vector<cubuPic*> * pic){

	guiname = pguiname;
	
	if(guiname == "roomservice1"){
		button->push_back(new cubuButton(400,150,"Do not Disturb"));
		button->push_back(new cubuButton(400,200,"Towels"));
		button->push_back(new cubuButton(400,250,"Clean Up"));

		pic->push_back(new cubuPic("img/cleaning.jpg", 500, 100));

		//string->push_back(new cubuString("TEST", 100, 100,"verdana.ttf", 32, 0xFFFFFF));
		//string->push_back(new cubuString("TEST", 300, 100,"brit.ttf", 32));
		//string->push_back(new cubuString("AAAA", 100, 300));
		string->push_back(new cubuString("Roomservice"));
	}

	else if (guiname == "alarm1") {
		string->push_back(new cubuString("Set Alarm"));
		pic->push_back(new cubuPic("img/backgrounds/alarm.png", 20, 150));
	}
	else if (guiname == "activities1") {
		button->push_back(new cubuButton(400,150,"Wellness"));
		button->push_back(new cubuButton(400,200,"Beauty"));
		button->push_back(new cubuButton(400,250,"Sports"));
	
	}
	else if (guiname == "fun1") {
		
	
	}
	else if (guiname == "food1") {
		string->push_back(new cubuString("Food & Drinks"));
		pic->push_back(new cubuPic("img/backgrounds/empty.png", 20, 150));
		pic->push_back(new cubuPic("img/menu/drinks.png", 250, 180));
		pic->push_back(new cubuPic("img/menu/food.png", 550, 180));
		button->push_back(new cubuButton(320,510,"Drinks"));
		button->push_back(new cubuButton(620,510,"Menu"));
	
	}	
	else if (guiname == "Drinks") {
		button->clear();		
		speisen = dbhandler->getSpeisen(1);
		string->push_back(new cubuString("Drinks", 100, 100,"verdana.ttf", 32));
	
		int y = 150; 
		for(int i = 0; i < speisen.size(); i++) {
			
			button->push_back(new cubuButton(400,y,speisen.at(i)->getName()));
			y += 100;
		}
	}
	else if (guiname == "Menu") {
		button->clear();
		speisen = dbhandler->getSpeisen(0);
		string->push_back(new cubuString("The Menu", 100, 100,"verdana.ttf", 32));
		int y = 150; 
		for(int i = 0; i < speisen.size(); i++) {
			
			button->push_back(new cubuButton(400,y,speisen.at(i)->getName()));
			y += 100;
		}
	
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