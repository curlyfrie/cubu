
#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxCvMain.h"
#include "ofxFidMain.h"
#include <vector>
#include <iostream>
#include "ofImage.h"


#include "DBHandler.h"
#include "cubuButton.h"
#include "cubuString.h" 
#include "cubuPic.h" 
#include "Display.h"

#include "ofEvents.h"


class cubu : public ofBaseApp{

	public:
	
		cubu();
		~cubu();
	
		int terminalID;
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
		
		void drawGUI();
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
		vector<cubuPic*> pics;


		float font_size;
		

		//variables for every side
		string rotation;	
		int previous_angle;
		int current_angle;
		string stringtodraw;
		string stringtodraw2;
		int sensitivity;
		
		//alarm variables & fnc
		bool alarmset;
		int time;
		
		float temperature;
		int alarm_minute;
		int alarm_hour;

		void setAlarm();
		void setTemp();
		
		//fiducial variables
		int fiducial_threshold;
		bool showFiducialWindow;
		
		bool showFaq;
			
		vector<Faq*> faqs;
		vector<Speise*> speisen;
		vector<Bestellung*> bestellungen;
		string guiname;

		map <int, Kunde*> kunden;
		Speise * speise;
		Kunde * kunde;

};

#endif
