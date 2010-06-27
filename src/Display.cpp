/*
 *  Display.cpp
 *  cubu
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "cubu.h"

Display::Display()
{	dbhandler = new DBHandler();

}
Display::Display(int _terminalid) {
	dbhandler = new DBHandler();
	terminalid = _terminalid;
	
}

Display::~Display()
{
	// exit should do the same stuff
}

void Display::draw(std::string pguiname, vector<cubuButton*> * button, vector<cubuString*> * string, vector<cubuPic*> * pic){


	button->clear();	
	string->clear();
	pic->clear();

	guiname = pguiname;
	
	if(guiname == "roomservice1"){
		
		string->push_back(new cubuString("Room Service"));
		pic->push_back(new cubuPic("img/backgrounds/empty.png", 20, 150));
		pic->push_back(new cubuPic("img/menu/disturb.png", 100, 180));
		pic->push_back(new cubuPic("img/menu/towels.png", 400, 180));
		pic->push_back(new cubuPic("img/menu/cleaning.png", 700, 180));
		
		button->push_back(new cubuButton(140,510,"Do not Disturb"));
		button->push_back(new cubuButton(465,510,"Towels"));
		button->push_back(new cubuButton(760,510,"Clean Up"));

		

		//string->push_back(new cubuString("TEST", 100, 100,"verdana.ttf", 32, 0xFFFFFF));
		//string->push_back(new cubuString("TEST", 300, 100,"brit.ttf", 32));
		//string->push_back(new cubuString("AAAA", 100, 300));
	}

	else if (guiname == "alarm1") {
		string->push_back(new cubuString("Set Alarm"));
		pic->push_back(new cubuPic("img/backgrounds/alarm.png", 20, 150));
	}
	else if (guiname == "activities1") {
		string->push_back(new cubuString("Hotel Activities"));
		pic->push_back(new cubuPic("img/backgrounds/empty.png", 20, 150));
		pic->push_back(new cubuPic("img/menu/wellness.png", 100, 180));
		pic->push_back(new cubuPic("img/menu/beauty.png", 400, 180));
		pic->push_back(new cubuPic("img/menu/sports.png", 700, 180));
		button->push_back(new cubuButton(160,510,"Wellness"));
		button->push_back(new cubuButton(470,510,"Beauty"));
		button->push_back(new cubuButton(770,510,"Sports"));

	
	}
	else if (guiname == "fun1") {
		string->push_back(new cubuString("Fun"));
		pic->push_back(new cubuPic("img/backgrounds/fun.png", 20, 150));
		dienstleistung = dbhandler->getDienstleistungen();
		
		int y = 180; 
		for(int i = 0; i < dienstleistung.size(); i++) {
			button->push_back(new cubuButton(400,y,dienstleistung.at(i)->getName()));
			y += 40;
		}
	
	}
	else if (guiname == "food1") {
		string->push_back(new cubuString("Food & Drinks"));
		pic->push_back(new cubuPic("img/backgrounds/empty.png", 20, 150));
		pic->push_back(new cubuPic("img/menu/drinks.png", 250, 180));
		pic->push_back(new cubuPic("img/menu/food.png", 550, 180));
		button->push_back(new cubuButton(320,510,"Drinks"));
		button->push_back(new cubuButton(620,510,"Menu"));
		
		
		//display orders
		vector <Bestellung*> bestellungen = dbhandler->getBestellungen(dbhandler->getTerminal(terminalid));
		
		cubuString * bestellungenString = new cubuString("Offene Bestellungen:\n",10, 600, "frabk.ttf", 10);
		for (int i = 0; i < bestellungen.size(); i++)
		{
			std::stringstream anzahlStr;
			anzahlStr << bestellungen.at(i)->getAnzahl();
			cout <<"\n" + anzahlStr.str() + " " + dbhandler->getSpeise(bestellungen.at(i)->getSpeiseId())->getName();
			bestellungenString->appendString("\n" + anzahlStr.str() + " " + dbhandler->getSpeise(bestellungen.at(i)->getSpeiseId())->getName());
			
		}
		string->push_back(bestellungenString);
	
	}	
	else if (guiname == "Drinks") {

		speisen = dbhandler->getSpeisen(1);
		
		string->push_back(new cubuString("Drinks"));
		pic->push_back(new cubuPic("img/backgrounds/drink1.png", 20, 150));
	
		int y = 180; 
		for(int i = 0; i < speisen.size(); i++) {
			button->push_back(new cubuButton(400,y,speisen.at(i)->getName(),speisen.at(i)->getId()));
			y += 50;
			
		}
	}
	else if (guiname == "Menu") {
		
		speisen = dbhandler->getSpeisen(0);
		string->push_back(new cubuString("Food"));
		pic->push_back(new cubuPic("img/backgrounds/food1.png", 20, 150));
		
		int y = 180; 
		for(int i = 0; i < speisen.size(); i++) {
			
			button->push_back(new cubuButton(400,y,speisen.at(i)->getName(),speisen.at(i)->getId()));
			y += 50;
			y += 40;
		}
	
	}
	else if (guiname == "temperature1") {
		string->push_back(new cubuString("Room Temperature"));
		pic->push_back(new cubuPic("img/backgrounds/temperature.png", 20, 150));
	
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