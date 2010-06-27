/*
 *  Terminal.cpp
 *
 *
 */

#include "Terminal.h"

Terminal::Terminal(int _terminal_id, std::string name, std::string telnumber)
{

	name = name;
	telnumber = telnumber;
	terminal_id = _terminal_id;
	
	
}


int Terminal::getId(){
	cout << "terminal id " << terminal_id << endl;
	return terminal_id;
}


