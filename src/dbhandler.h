/*
 db handler should interact with database
 */


#include "ofxSQLiteHeaders.h";

class dbhandler {

public:
	dbhandler();
	~dbhandler();
private:
	ofxSQLite* sqlite;

};