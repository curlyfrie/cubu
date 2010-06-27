/*
 *  Dienstleistung.cpp
 *  cubu
 *
 *  Created by Elias on 27.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Dienstleistung.h"




Dienstleistung::Dienstleistung(int _dienstleistung_id, std::string _name, std::string _beschreibung, std::string _kontakt, int _prioritaet, std::string _datum,std::string _bild)
{
	
	dienstleistung_id = _dienstleistung_id;
	name = _name;
	beschreibung = _beschreibung;
	prioritaet = _prioritaet;
	datum = _datum;
	kontakt = _kontakt;
	bild = _bild;
	
	
}



std::string Dienstleistung::getName(){
	return name;
}


std::string Dienstleistung::getBeschreibung(){
	return beschreibung;
}


int Dienstleistung::getId(){
	return dienstleistung_id;
}

std::string Dienstleistung::getBild(){
	return bild;
}

std::string Dienstleistung::getKontakt(){
	return kontakt;
}
