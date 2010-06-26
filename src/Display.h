/*
 *  Display.h
 *  cubu

 */


/*
#include "ofMain.h"

#include "ofxCvMain.h"
#include "ofxFidMain.h"
#include "DBHandler.h"

#include <vector>
#include "Display.h"*/

using namespace std;

class Display {

private:
	ofTrueTypeFont buttonlabel;
	
public:
	
	std::string guiname;

	Display();
	~Display();

	
	void draw2(vector<cubuButton*> * todraw,int type);
	
	ofTrueTypeFont franklinBook;
	
	vector<cubuButton*> drawRoomservice();
	void drawRoomservice( vector<cubuButton*> * todraw);
	
	DBHandler *dbhandler;
	vector<Speise*> speisen;

	void draw(std::string pguiname, vector<cubuButton*> * button, vector<cubuString*> * string, vector<cubuPic*> * pic);

	void click(int x, int y);
};