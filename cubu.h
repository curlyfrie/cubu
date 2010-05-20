#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxCvMain.h"
#include "ofxFidMain.h"


class cubu : public ofBaseApp{

	public:
	
		cubu();
		~cubu();
	
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
	
private:
	int side_food;
	int side_alarm;
	int side_temperature;
	int side_roomservice;
	int side_activities;
	int side_fun;
	int active_side;
	string stringtodraw;
	
	int fiducial_threshold;
	float font_size;

};

#endif
