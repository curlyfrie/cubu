/*
 *  Bestellung.h
 *  cubu
 *
 *  Created by Alexander Fried on 26.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include <iostream>
#include <string>
#include "Speise.h"

class Bestellung {
	
	
private:
	Speise * speise;
	int anzahl;
	float sumpreis;
public:
	
	Bestellung( Speise * speise, int _anzahl, float _sumpreis );
	void printFaq();
	std::string getQuestion();
	std::string getAnswer();
	int getId();
	void getSpeise(Speise * speise2);
	int getAnzahl();
	float getSumpreis();
	
	~Bestellung();
	
	
};