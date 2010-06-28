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
	int speise_id;
	int anzahl;
	float sumpreis;

public:
	
	Bestellung(int speise_id, int _anzahl, float _sumpreis );
	void printFaq();
	std::string getQuestion();
	std::string getAnswer();
	int getId();
	int getSpeiseId();
	int getAnzahl();
	float getSumpreis();
	
	~Bestellung();
	
	
};