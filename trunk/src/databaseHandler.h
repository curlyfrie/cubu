#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxFidMain.h"
#include "ofxSQLiteHeaders.h"
#include "cubu.h"

class databaseHandler{
	
public:
	
	databaseHandler();
	~databaseHandler();
	
	int roomID;
	int roomNr;

	void setupDB();	
	void saveAlarm(int hour, int minute);	
	
private:
	
	// the actual database
	ofxSQLite* sqlite;
	
	//the mothership
	cubu* mothercubu;
	
};

#endif
