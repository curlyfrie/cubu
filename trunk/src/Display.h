/*
 *  Display.h
 *  cubu
 *
 *  Created by Patrick Stipsits on 25.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "cubuButton.h" 
#include <vector>
#include "ofMain.h"

using namespace std;

class Display {

private:
	
	vector<cubuButton*> buttonVector;
	ofTrueTypeFont buttonlabel;
	
public:
	
	
	Display();
	//~Display();
	
	vector<cubuButton*> drawRoomservice();
	void drawRoomservice( vector<cubuButton*> * todraw);
	void click(int x, int y);
};