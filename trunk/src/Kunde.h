/*
 *  Kunde.h
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#include <iostream>

class Kunde {
	
	
private:
	int id;
	std::string vorname;
	std::string nachname;
	std::string adresse;
	std::string kreditkartennummer;
	
	
public:
	
	Kunde(int id, std::string vorname,std::string nachname,std::string adresse,std::string kreditkartennummer);
	std::string getVorname();
	std::string getNachname();
	std::string getAdresse();
	std::string getKreditkartennummer();
	int getId();
	
	~Kunde();
	
	
};