/*
 *  cubuButton.h
 *  cubu
 *
 * this thing should be a button in cubu's GUI
 * and it works!
 *
 */

class cubuButton {
	
public:
	int x;
	int y;
	int width;
	int height;
	
	bool selected;
	
	void select(bool value);
	
	cubuButton();
	cubuButton(int px, int py);
	~cubuButton();
	
private:
	void setDefaultValues();
};