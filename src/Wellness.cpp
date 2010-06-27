/*
 *  Wellness.cpp
 *  cubu
 *
 *  Created by Elias on 27.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Wellness.h"


Wellness::Wellness(int _wellness_id, std::string _name, std::string _beschreibung, float _preis, int _typ, int _prioritaet, std::string _datum)
{
	
	wellness_id = _wellness_id;
	name = _name;
	beschreibung = _beschreibung;
	preis = _preis;
	prioritaet = _prioritaet;
	datum = _datum;
	typ = _typ;
	
	
}

Wellness::Wellness(int _wellness_id, std::string _name, std::string _beschreibung, float _preis, int _typ)
{
	wellness_id = _wellness_id;
	name = _name;
	beschreibung = _beschreibung;
	preis = _preis;
	typ = _typ;
}


std::string Wellness::getName(){
	return name;
}


std::string Wellness::getBeschreibung(){
	return beschreibung;
}
float Wellness::getPreis(){
	return preis;
}

int Wellness::getId(){
	return wellness_id;
}

int Wellness::getTyp(){
	return typ;
}
