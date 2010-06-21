/*
 *  dbhandler.cpp
 *
 *  Created by Patrick Stipsits on 16.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "dbhandler.h"

dbhandler::dbhandler()
// setup connection to database
{
	sqlite = new ofxSQLite("cubu.db");
	
//CREATING TERMINAL
	cout << "creating table 'terminal'...";	
	if (SQLITE_OK != sqlite->simpleQuery(""\
										 "CREATE TABLE IF NOT EXISTS terminal( " \
										 " id INTEGER PRIMARY KEY AUTOINCREMENT" \
										 ",zimmer STRING" \
										 ",telefonnummer INTEGER" \
										 ");"
										 )) {
		cout << "ERROR CREATE TABLE terminal\n";
	}
	else
		cout << "...successful" << endl;
	
//CREATING TERMINAL	
	cout << "creating table 'alarm'...";	
	if (SQLITE_OK != sqlite->simpleQuery(""\
										 "CREATE TABLE IF NOT EXISTS alarm( " \
										 " id INTEGER PRIMARY KEY AUTOINCREMENT" \
										 ",terminal_id REFERENCES terminal(id)" \
										 ",time INTEGER" \
										 ",active INTEGER" \
										 ");"
										 )) {
		cout << "ERROR CREATE TABLE " << endl;
		
	}
	else
		cout << "...successful" << endl;
	
	
/*
	cout << "creating table...";	
	if (SQLITE_OK != sqlite->simpleQuery(""\
										 "CREATE TABLE IF NOT EXISTS room( " \
										 " id INTEGER PRIMARY KEY AUTOINCREMENT" \
										 ",number INTEGER" \
										 ",alarm_hour INTEGER" \
										 ",alarm_minute INTEGER" \
										 ",alarm_set BOOLEAN" \
										 ");"
										 )) {
		cout << "ERROR CREATE TABLE\n";
	}
	else
		cout << "...successful" << endl;
	
	*/
	
	// insert this client
	//sqlite->insert("room").use("number",ofToString(roomNr)).use("alarm_hour","1").use("alarm_minute","1").use("alarm_set","FALSE").execute();
	
	
	
}


