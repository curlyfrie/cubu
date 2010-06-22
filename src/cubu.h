
#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxCvMain.h"
#include "ofxFidMain.h"
#include "ofxSQLiteHeaders.h"
#include "DBHandler.h"



class cubu : public ofBaseApp{

	public:
	
		cubu();
		~cubu();
	
		int roomID;
		int roomNr;

	
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
	
		ofTrueTypeFont franklinBook;
	
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
	void setupDB();
	void drawGUI();
	
	void setupGUI();
	
private:
	
	ofxSQLite* sqlite;

	vector <int> buttons;
	int selected_button;
	vector<string> buttons2;
	
	float font_size;
	
	int side_food;
	int side_alarm;
	int side_temperature;
	int	side_roomservice;
	int side_activities;
	int side_fun;
	int active_side;
	
	//variables for every side
	string rotation;	
	int previous_angle;
	int current_angle;
	string stringtodraw;
	int sensitivity;
	
	//alarm variables & fnc
	bool alarmset;
	int alarm_minute;
	int alarm_hour;
	void setAlarm();
	void saveAlarmtoDB();
	void getAlarmfromDB();
	
	//fiducial variables
	int fiducial_threshold;
	bool showFiducialWindow;
	
	// button variables...this is going to be looooong
	// and maybe not even necessary....
	bool button_ok;
	bool button_cancel;
	bool button_cleanup;
	bool button_towel;

};

#endif
