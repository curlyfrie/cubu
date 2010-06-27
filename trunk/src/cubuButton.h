/*
 *  cubuButton.h
 *  cubu
 *
 * this thing should be a button in cubu's GUI
 * and it works!
 *
 */
#include <iostream>

class cubuButton {
	
public:
	int x;
	int y;
	int width;
	int height;
	int action;
	int menuid;
	std::string label;
	bool selected;
	
	void select(bool value);
	bool click(int clickx, int clicky);
	int getMenuid();
	cubuButton();
	cubuButton(int px, int py, std::string plabel);
	cubuButton(int px, int py, std::string plabel, int menuid);
	~cubuButton();
	
private:
	
	void setDefaultValues();
};