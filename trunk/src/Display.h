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
	ofTrueTypeFont verdana;
	
public:
	
	std::string guiname;

	Display();
	Display(int terminalid);
	
	~Display();

	
	void draw2(vector<cubuButton*> * todraw,int type);
	
	ofTrueTypeFont franklinBook;
	int terminalid;
	vector<cubuButton*> drawRoomservice();
	void drawRoomservice( vector<cubuButton*> * todraw);
	
	DBHandler *dbhandler;
	vector<Speise*> speisen;
	vector<Dienstleistung*> dienstleistung;

	void draw(std::string pguiname, vector<cubuButton*> * button, vector<cubuString*> * string, vector<cubuPic*> * pic);
	void drawDetail(std::string pguiname, vector<cubuButton*> * button, vector<cubuString*> * string, vector<cubuPic*> * pic, int id);
	void drawDienstleistungDetail(vector<cubuButton*> * button, vector<cubuString*> * string, vector<cubuPic*> * pic, int id);

	void click(int x, int y);
};