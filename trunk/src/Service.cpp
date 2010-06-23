/*
 *  Service.cpp
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Service.h"

Service::Service(int _id, std::string _name, std::string _beschreibung)
{
	
	id = _id;
	name = _name;
	beschreibung = _beschreibung;
	
}
 
std::string Service::getName(){
	return name;
}

std::string Service::getBeschreibung(){
	return beschreibung;
}
int Service::getId(){
	return id;
}
