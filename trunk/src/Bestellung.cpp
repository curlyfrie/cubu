/*
 *  Bestellung.cpp
 *  cubu
 *
 *  Created by Alexander Fried on 26.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Bestellung.h"


Bestellung::Bestellung(int _speise_id, int _anzahl, float _sumpreis)
{
	
	speise_id = _speise_id;
	anzahl = _anzahl;
	sumpreis = _sumpreis;

	
	
}


int Bestellung::getSpeiseId()
{
	
	return speise_id;
}

int Bestellung::getAnzahl()
{

	return anzahl;
}
float Bestellung::getSumpreis()
{

	return sumpreis;
}