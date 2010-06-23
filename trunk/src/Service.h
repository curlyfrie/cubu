/*
 *  Service.h
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>
class Service {
	
	
private:
	int id;
	std::string name;
	std::string beschreibung;
public:
	
	Service(int id, std::string name, std::string beschreibung);

	std::string getName();
	std::string getBeschreibung();
	int getId();
	
	~Service();
	
	
};
