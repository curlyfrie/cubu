

#include "ofMain.h"

#include <iostream>


class Terminal {
private:
	int id;
	std::string name;
	std::string telnumber;
	
public:
	Terminal(int id, std::string name, std::string telnumber);
	
	int getId();
	~Terminal();

	
};



	
	
