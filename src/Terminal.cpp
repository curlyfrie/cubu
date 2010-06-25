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
	return terminal_id;
}


