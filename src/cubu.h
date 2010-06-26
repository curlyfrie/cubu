
#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxCvMain.h"
#include "ofxFidMain.h"
#include <vector>
#include <iostream>

#include "DBHandler.h"
#include "cubuButton.h"
#include "cubuString.h" 
#include "Display.h"

#include "ofEvents.h"


class cubu : public ofBaseApp{

	public:
	
		cubu();
		~cubu();
	
		int roomID;
		int roomNr;
		Terminal * terminal;
	
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
	// set no. of marker for sides

	
	void blub(ofMouseEventArgs & mouseEventArgs );
	void blub2(int a,int b, int c);
	
		ofTrueTypeFont franklinBook;
		ofTrueTypeFont buttonlabel;

		ofTrueTypeFont font;
	
		ofVideoGrabber vidGrabber;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage grayBg;
		ofxCvGrayscaleImage	grayDiff;
		ofxCvColorImage colorImg;
		ofxFiducialTracker fidfinder;

		
		DBHandler * dbhandler;
		void setupMYSQLDB();

	
	int getRotDirection();
	
	void drawAlarm();
	void drawFood();
	void drawGUI();
	void drawFaq();
	
	void setupGUI();


	
	int side_food;
	int side_alarm;
	int side_temperature;
	int	side_roomservice;
	int side_activities;
	int side_fun;
	int active_side;
	int prev_side;
	
	
private:
	
	Display *display;
	int selected_button;
	vector<cubuButton*> buttons;
	vector<cubuString*> strings;


	float font_size;
	

	//variables for every side
	string rotation;	
	int previous_angle;
	int current_angle;
	string stringtodraw;
	int sensitivity;
	
	//alarm variables & fnc
	bool alarmset;
	int buttonset;
	int time;

	int alarm_minute;
	int alarm_hour;
	void setAlarm();
	void saveAlarmtoDB();
	void getAlarmfromDB();
	
	//fiducial variables
	int fiducial_threshold;
	bool showFiducialWindow;
	
	bool showFaq;
		
	vector<Faq*> faqs;
	vector<Speise*> speisen;
	vector<Bestellung*> bestellungen;

	map <int, Kunde*> kunden;
	Speise * speise;
	Kunde * kunde;




};

#endif
