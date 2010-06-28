/*
 *  Speise.h
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef SPEISE_H
#define SPEISE_H
#include <iostream>


class Speise {
	
	
private:
	int speise_id;
	std::string name;
	std::string beschreibung;
	float preis;
	std::string bild;
	int typ;
public:
	
	Speise(int speise_id, std::string name, std::string beschreibung, float preis, std::string bild, int typ);
//	Speise(int speise_id, std::string name, std::string beschreibung, float preis);
	std::string getName();
	std::string getBeschreibung();
	float getPreis();
	int getId();
	std::string getBild();
	int getTyp();
	
	
	~Speise();
	
	
};
#endif