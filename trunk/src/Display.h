/*
 *  Display.h
 *  cubu
 *
 *  Created by Patrick Stipsits on 25.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "cubuButton.h"
#include "cubuString.h" 
#include <vector>
#include "ofMain.h"
#include <iostream>

using namespace std;

class Display {

private:
	ofTrueTypeFont buttonlabel;
	
public:
	
	std::string guiname;

	Display();
	//~Display();
	void draw(std::string pguiname, vector<cubuButton*> * button, vector<cubuString*> * string);
	void click(int x, int y);
};