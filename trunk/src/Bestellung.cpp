/*
 *  Bestellung.cpp
 *  cubu
 *
 *  Created by Alexander Fried on 26.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Bestellung.h"


Bestellung::Bestellung(Speise * speise, int _anzahl, float _sumpreis)
{
	
	speise = speise;
	anzahl = _anzahl;
	sumpreis = _sumpreis;

	
	
}
void Bestellung::getSpeise(Speise * speise2)
{
	
	speise2 = speise;
}

int Bestellung::getAnzahl()
{

	return anzahl;
}
float Bestellung::getSumpreis()
{

	return sumpreis;
}