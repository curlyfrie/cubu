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
	
	if (guiname=="back") {
		guiname = "start";
	}
	
	if(guiname == "roomservice1"){
		
		//DYNAMIC VERSION
		string->push_back(new cubuString("Room Service"));
		pic->push_back(new cubuPic("img/backgrounds/empty.png", 20, 150));

		//available services
		vector<Service*> services =	dbhandler->getService();
		Service* current;
		
		//ONLY IDs of booked services of this terminal
		vector<int> bookedServices = dbhandler->getServiceIDsOfTerminal(terminalid);
		
		
		for(int i = 0; i < services.size(); i++){
			current = services.at(i);
			if(current->getName() == "Do not Disturb"){
				pic->push_back(new cubuPic("img/menu/disturb.png", 100, 180));			
				button->push_back(new cubuButton(140,510,"Do not Disturb",current->getId()));
				
				for(int j = 0; j < bookedServices.size(); j++){
					if(current->getId() == bookedServices.at(j)){
						pic->push_back(new cubuPic("img/menu/selected.png", 95, 177));
						pic->push_back(new cubuPic("img/menu/disturb.png", 100, 180));			
					}
				}
			}
			if(current->getName() == "Towels"){
				pic->push_back(new cubuPic("img/menu/towels.png", 400, 180));
				button->push_back(new cubuButton(465,510,"Towels",current->getId()));
				
				for(int j = 0; j < bookedServices.size(); j++){
					if(current->getId() == bookedServices.at(j)){
						pic->push_back(new cubuPic("img/menu/selected.png", 395, 177));
						pic->push_back(new cubuPic("img/menu/towels.png", 400, 180));
					}
						
				}
			}
			if(current->getName() == "Clean Up"){
				pic->push_back(new cubuPic("img/menu/cleaning.png", 700, 180));			
				button->push_back(new cubuButton(760,510,"Clean Up",current->getId()));
				
				for(int j = 0; j < bookedServices.size(); j++){
					if(current->getId() == bookedServices.at(j)){
						pic->push_back(new cubuPic("img/menu/selected.png", 695, 177));
						pic->push_back(new cubuPic("img/menu/cleaning.png", 700, 180));			
					}
						
				}
			}
		}


		
	}

	else if (guiname == "alarm1") {
		string->push_back(new cubuString("Set Alarm"));
		pic->push_back(new cubuPic("img/backgrounds/alarm.png", 20, 150));
	}
	else if (guiname == "start") {
		Kunde *k = dbhandler->getKunde(dbhandler->getKundenId(terminalid));
		string->push_back(new cubuString("Welcome "+k->getVorname()+" "+k->getNachname()));
		pic->push_back(new cubuPic("img/backgrounds/start.png", 20, 150));
		
		pic->push_back(new cubuPic("img/wilson.png", 870, 30));
		button->push_back(new cubuButton(920,160,"FAQ"));
		
		//bestellungen
		string->push_back(new cubuString("Your Orders:",50,310,"frabk.ttf", 20,0xFFFFFF));
		vector <Bestellung*> bestellungen = dbhandler->getBestellungen(dbhandler->getTerminal(terminalid));
		cubuString * bestellungenString = new cubuString("",60, 320, "frabk.ttf", 11,0xEFEFEF);
		for (int i = 0; i < bestellungen.size(); i++)
		{
			std::stringstream anzahlStr;
			anzahlStr << bestellungen.at(i)->getAnzahl();
			//	cout <<"\n" + anzahlStr.str() + " " + dbhandler->getSpeise(bestellungen.at(i)->getSpeiseId())->getName();
			bestellungenString->appendString("\n" + anzahlStr.str() + " " + dbhandler->getSpeise(bestellungen.at(i)->getSpeiseId())->getName());
			
		}
		string->push_back(bestellungenString);
						
		
		// services
		string->push_back(new cubuString("Services ordered:",350,310,"frabk.ttf", 20,0xFFFFFF));
		vector<int> service = dbhandler->getServiceIDsOfTerminal(terminalid);
		
		cubuString * s = new cubuString("",370, 335, "frabk.ttf", 11,0xEFEFEF);
		for (int i = 0; i < service.size(); i++)
		{
			//std::stringstream anzahlStr;
			//anzahlStr << service.at(i)->getAnzahl();
			//s->appendString("\n" + anzahlStr.str() + " " + dbhandler->getSpeise(bestellungen.at(i)->getSpeiseId())->getName());
			
			s->appendString(dbhandler->getService(service.at(i))->getName()+"\n");
			
		}
		string->push_back(s);
		
		
		
		// activities
		//string->push_back(new cubuString("Rented Activities:",700,310,"frabk.ttf", 20,0xFFFFFF));
		
		float temperature = dbhandler->getTemperatur(terminalid);
		std::stringstream out;
		out << temperature;
		string->push_back(new cubuString("Room Temperature:  "+out.str()+" C",50,620,"frabk.ttf", 14,0xFFFFFF));
		
		std::string alarm = dbhandler->getAlarm(terminalid);
		if (alarm!="") {
			string->push_back(new cubuString("Alarm Timer:  "+alarm,420,620,"frabk.ttf", 14,0xFFFFFF));
		}
		
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
	else if (guiname == "FAQ") {
		string->push_back(new cubuString("Frequently Asked Questions"));
		//pic->push_back(new cubuPic("img/backgrounds/empty.png", 20, 150));
		std::string questions="";
		vector<Faq*>  faqs = dbhandler->getFaqs();
		int y = 150;
		for (int i=0; i<faqs.size(); i++) {
			Faq * f = faqs.at(i);
			string->push_back(new cubuString(f->getQuestion(),30, y, "frabk.ttf", 14));
			y+=17;
			cubuString * cs = new cubuString(f->getAnswer(),30, y, "frabk.ttf", 12);
			string->push_back(cs);
			ofTrueTypeFont frab;
			frab.loadFont("frabk.ttf",12);
			ofRectangle rect = frab.getStringBoundingBox(cs->text, 30,y);
			y+=rect.height+15;
		}
		
		button->push_back(new cubuButton(30,690,"back"));
		
		
	}
	else if (guiname == "Wellness") {
		string->push_back(new cubuString("Wellness"));
		pic->push_back(new cubuPic("img/backgrounds/wellness.png", 20, 150));
		well = dbhandler->getWellness(0);
		int y = 180; 
		for(int i = 0; i < well.size(); i++) { 
			button->push_back(new cubuButton(400,y,well.at(i)->getName(),well.at(i)->getId()));
			y += 50;
			
		}
		
	}
	else if (guiname == "Beauty") {
		string->push_back(new cubuString("Beauty"));
		pic->push_back(new cubuPic("img/backgrounds/beauty.png", 20, 150));
		well = dbhandler->getWellness(1);
		int y = 180; 
		for(int i = 0; i < well.size(); i++) { 
			button->push_back(new cubuButton(400,y,well.at(i)->getName(),well.at(i)->getId()));
			y += 50;
			
		}
	}
	else if (guiname == "Sports") {
		string->push_back(new cubuString("Sports"));
		pic->push_back(new cubuPic("img/backgrounds/sport.png", 20, 150));
		well = dbhandler->getWellness(2);
		int y = 180; 
		for(int i = 0; i < well.size(); i++) { 
			button->push_back(new cubuButton(400,y,well.at(i)->getName(),well.at(i)->getId()));
			y += 50;
			
		}		
	}
	else if (guiname == "fun1") {
		string->push_back(new cubuString("Fun"));
		pic->push_back(new cubuPic("img/backgrounds/fun.png", 20, 150));
		dienstleistung = dbhandler->getDienstleistungen();
		
		int y = 180; 
		for(int i = 0; i < dienstleistung.size(); i++) {
			button->push_back(new cubuButton(400,y,dienstleistung.at(i)->getName(),dienstleistung.at(i)->getId()));
			y += 40;
		}
	
	}
	else if (guiname == "food1") {

		string->push_back(new cubuString("Food & Drinks"));
		pic->push_back(new cubuPic("img/backgrounds/empty.png", 20, 150));
		pic->push_back(new cubuPic("img/menu/drinks.png", 250, 180));
		pic->push_back(new cubuPic("img/menu/food.png", 550, 180));
		button->push_back(new cubuButton(320,510,"Drinks","Drinks"));
		button->push_back(new cubuButton(620,510,"Menu","Menu"));
		
		//display orders
		vector <Bestellung*> bestellungen = dbhandler->getBestellungen(dbhandler->getTerminal(terminalid));
		cout << "best: " << bestellungen.size() << endl;
		cubuString * bestellungenString = new cubuString("Offene Bestellungen:\n",10, 600, "frabk.ttf", 10);
		for (int i = 0; i < bestellungen.size(); i++)
		{
			std::stringstream anzahlStr;
			anzahlStr << bestellungen.at(i)->getAnzahl();
		//	cout <<"\n" + anzahlStr.str() + " " + dbhandler->getSpeise(bestellungen.at(i)->getSpeiseId())->getName();
			bestellungenString->appendString("\n" + anzahlStr.str() + " " + dbhandler->getSpeise(bestellungen.at(i)->getSpeiseId())->getName());
			
		}
		string->push_back(bestellungenString);
	
	} else if (guiname == "dienstleistunginfo") {
		
		cout << "test erfolgreich. congrats elias. go for president!";
		/*
		speisen = dbhandler->getDiensleistung();
		
		string->push_back(new cubuString("Drinks"));
		pic->push_back(new cubuPic("img/backgrounds/drink1.png", 20, 150));
		
		int y = 180; 
		for(int i = 0; i < speisen.size(); i++) {
			button->push_back(new cubuButton(400,y,speisen.at(i)->getName(),speisen.at(i)->getId()));
			y += 50;
			
		}*/
	}	
	else if (guiname == "Drinks") {

		speisen = dbhandler->getSpeisen(1);
		
		string->push_back(new cubuString("Drinks"));
		pic->push_back(new cubuPic("img/backgrounds/drink1.png", 20, 150));

		int y = 180; 
		for(int i = 0; i < speisen.size(); i++) {
			button->push_back(new cubuButton(400,y,speisen.at(i)->getName(),speisen.at(i)->getId(), "describe"));
			y += 50;
			
		}

	}
	else if (guiname == "Menu") {
		
		speisen = dbhandler->getSpeisen(0);
		string->push_back(new cubuString("Food"));
		pic->push_back(new cubuPic("img/backgrounds/food1.png", 20, 150));
		
		int y = 180; 
		for(int i = 0; i < speisen.size(); i++) {
			
			button->push_back(new cubuButton(400,y,speisen.at(i)->getName(),speisen.at(i)->getId(), "describe"));
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

void Display::drawDetail(std::string pguiname, vector<cubuButton*> * button, vector<cubuString*> * string, vector<cubuPic*> * pic, int id){

	button->clear();	
	string->clear();
	pic->clear();

	guiname = pguiname;

	if (guiname == "describe") {
		
		cout << "drawDetail(): decribe" << endl;
		Speise *s = dbhandler->getSpeise(id);
		string->push_back(new cubuString(s->getName()));
		pic->push_back(new cubuPic(s->getBild(), 20, 150));

		std::stringstream stream;
		stream << s->getBeschreibung();
		
		std::stringstream preis;
		preis << s->getPreis();
		string->push_back(new cubuString(stream.str(), 400, 200, "frabk.ttf", 13));
		string->push_back(new cubuString("Euro " + preis.str() , 400, 350, "frabk.ttf", 13));
		button->push_back(new cubuButton(400,400,"order", id,"food1"));
		button->push_back(new cubuButton(500,400,"back"));
	}
	else if (guiname == "describewell") {
		Wellness *w = dbhandler->getWell(id);
		pic->push_back(new cubuPic("img/backgrounds/details.png", 20, 150));
		string->push_back(new cubuString(w->getName()));
		//pic->push_back(new cubuPic(s->getBild(), 20, 150));

		std::stringstream stream;
		stream << w->getBeschreibung();
		
		std::stringstream preis;
		preis << w->getPreis();
		string->push_back(new cubuString(stream.str(), 400, 200, "frabk.ttf", 13));
		string->push_back(new cubuString("Euro " + preis.str() , 400, 350, "frabk.ttf", 13));
	//	button->push_back(new cubuButton(400,400,"order", id));
	//	button->push_back(new cubuButton(500,400,"back"));
	}
	
}

void Display::drawDienstleistungDetail(std::string pguiname,vector<cubuButton*> * button, vector<cubuString*> * string, vector<cubuPic*> * pic, int id){

	button->clear();
	string->clear();
	pic->clear();
	Dienstleistung *d = dbhandler->getDienstleistung(id);
	string->push_back(new cubuString(d->getName()));

	string->push_back(new cubuString(d->getBeschreibung()+"\n\nKontakt: \n"+d->getKontakt(),420,240,"verdana.ttf", 14, 0xFFFFFF));
	pic->push_back(new cubuPic("img/backgrounds/empty.png", 20, 180));
	pic->push_back(new cubuPic(d->getBild(), 30, 190));
	button->push_back(new cubuButton(900,570,"back"));
									  
}