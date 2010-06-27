/*
 *  Wellness.h
 *  cubu
 *
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef WELLNESS_H
#define WELLNESS_H
#include <iostream>


class Wellness {
	
	
private:
	int wellness_id;
	
	std::string name;
	std::string beschreibung;
	float preis;
	int prioritaet;
	int typ;
	std::string datum;
public:
	
	Wellness(int wellness_id, std::string name, std::string beschreibung, float preis, int typ, int prioritaet, std::string datum);
	Wellness(int wellness_id, std::string name, std::string beschreibung, float preis, int typ);
	
	std::string getName();
	std::string getBeschreibung();
	float getPreis();
	int getId();
	int getTyp();
	~Wellness();
	
	
};
#endif