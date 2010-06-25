/*
 *  Speise.h
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>

class Speise {
	
	
private:
	int speise_id;
	std::string name;
	std::string beschreibung;
	float preis;
public:
	
	Speise(int speise_id, std::string name, std::string beschreibung, float preis);
	std::string getName();
	std::string getBeschreibung();
	float getPreis();
	int getId();
	
	~Speise();
	
	
};