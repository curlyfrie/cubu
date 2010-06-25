

#include "ofMain.h"

#include <iostream>


class Terminal {
private:
	int terminal_id;
	std::string name;
	std::string telnumber;
	
public:
	Terminal(int terminal_id, std::string name, std::string telnumber);
	
	int getId();
	~Terminal();

	
};



	
	
