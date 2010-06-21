/*
 *  cubuButton.h
 *  cubu
 *
 *  Created by Patrick Stipsits on 18.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "ofMain.h"
#include "ofxSimpleGuiToo.h"

class cubuButton {
	
private:
	
	/*
	ofColor activeColor;
	ofColor inactiveColor;
	*/
	
	int x;
	int y;
	
public:
	
	// id: use to select from list
	int id;
	
	// true if current button is selected and marked
	bool isSelected;
	
	cubuButton();
	cubuButton(int px, int py);
	~cubuButton();
	 
	
	//color of the button
	ofColor color;
	
	
	//shape of the button
	ofRectangle shape;
	
};
