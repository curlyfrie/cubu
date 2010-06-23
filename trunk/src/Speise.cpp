/*
 *  Speise.cpp
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Speise.h"

Speise::Speise(int _id, std::string _name, std::string _beschreibung, float _preis)
{
	
	id = _id;
	name = _name;
	beschreibung = _beschreibung;
	preis = _preis;
	
}


std::string Speise::getName(){
	return name;
}

std::string Speise::getBeschreibung(){
	return beschreibung;
}
float Speise::getPreis(){
	return preis;
}

int Speise::getId(){
	return id;
}
