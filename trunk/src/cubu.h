
#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxCvMain.h"
#include "ofxFidMain.h"
#include "DBHandler.h"
#include "CubuButton.h" 
#include <vector>


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
		ofTrueTypeFont buttonlabel;
	
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
	void drawGUI();
	void drawFaq();
	
	void setupGUI();
	
private:
	

	int selected_button;
	vector<cubuButton*> buttons;

	float font_size;
	
	int side_food;
	int side_alarm;
	int side_temperature;
	int	side_roomservice;
	int side_activities;
	int side_fun;
	int active_side;
	int prev_side;
	
	//variables for every side
	string rotation;	
	int previous_angle;
	int current_angle;
	string stringtodraw;
	int sensitivity;
	
	//alarm variables & fnc
	bool alarmset;
	int buttonset;
	int alarm_minute;
	int alarm_hour;
	void setAlarm();
	void saveAlarmtoDB();
	void getAlarmfromDB();
	
	//fiducial variables
	int fiducial_threshold;
	bool showFiducialWindow;
	
		
	vector<Faq*> faqs;
	vector<Speise*> speisen;
	map <int, Kunde*> kunden;




};

#endif
