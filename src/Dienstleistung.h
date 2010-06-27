/*
 *  Dienstleistung.h
 *  cubu
 *
 *  Created by Elias on 27.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#ifndef DIENSTLEISTUNG_H
#define DIENSTLEISTUNG_H
#include <iostream>


class Dienstleistung {
	
	
private:
	int dienstleistung_id;
	
	std::string name;
	std::string beschreibung;
	int prioritaet;
	std::string datum;
	std::string kontakt;
public:
	
	Dienstleistung(int dienstleistung_id, std::string name, std::string beschreibung, std::string kontakt, int prioritaet, std::string datum);
	std::string getName();
	std::string getBeschreibung();
	float getPreis();
	int getId();
	std::string getKontakt();
	
	~Dienstleistung();
	
	
};
#endif