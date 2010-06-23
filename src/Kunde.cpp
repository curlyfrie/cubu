/*
 *  Kunde.cpp
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Kunde.h"



Kunde::Kunde(int _id, std::string _vn, std::string _nn,std::string _adresse, std::string _kknr)
{
	
	id = _id;
	vorname = _vn;
	nachname = _nn;
	adresse = _adresse;
	
	kreditkartennummer = _kknr;
	
}
void Kunde::printKunde(){
	std::cout << vorname << " " << nachname<<std::endl << adresse;
}
std::string Kunde::getVorname(){
	return vorname;
}
std::string Kunde::getNachname(){
	return nachname;
}
std::string Kunde::getAdresse(){
	return adresse;
}
std::string Kunde::getKreditkartennummer(){
	return kreditkartennummer;
}

int Kunde::getId(){
	return id;
}
