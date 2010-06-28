/*
 *  Speise.cpp
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Speise.h"

Speise::Speise(int _speise_id, std::string _name, std::string _beschreibung, float _preis, std::string _bild, int _typ)
{
	
	speise_id = _speise_id;
	name = _name;
	beschreibung = _beschreibung;
	preis = _preis;
	bild = _bild;
	typ = _typ;
	
}

/*Speise::Speise(int _speise_id, std::string _name, std::string _beschreibung, float _preis)
{
	
	speise_id = _speise_id;
	name = _name;
	beschreibung = _beschreibung;
	preis = _preis;
	
}
*/

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
	return speise_id;
}

std::string Speise::getBild(){
	return bild;
}

int Speise::getTyp(){
	return typ;
}
