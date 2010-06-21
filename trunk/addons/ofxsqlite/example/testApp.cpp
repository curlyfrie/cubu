#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
testApp::testApp(){
	sqlite = new ofxSQLite("test.db");
	sqlite->simpleQuery(""\
		"CREATE TABLE IF NOT EXISTS scores (" \
			" id INTEGER PRIMARY KEY AUTOINCREMENT" \
			" ,time TEXT" \
			", score INTEGER" \
		");"
	);

	sqlite->simpleQuery(""\
		"CREATE TABLE IF NOT EXISTS stats ("\
			"id INTEGER PRIMARY KEY AUTOINCREMENT" \
			", time TEXT" \
		");"
	);

	sqlite->simpleQuery(""\
		"CREATE TABLE IF NOT EXISTS game_runs( " \
			" id INTEGER PRIMARY KEY AUTOINCREMENT" \
			",start_time TEXT" \
			", end_time TEXT" \
		");"
	);

	if (SQLITE_OK != sqlite->simpleQuery(""\
		"CREATE TABLE IF NOT EXISTS game_run_data( " \
			" gid INTEGER PRIMARY KEY AUTOINCREMENT" \
			",runid INTEGER" \
			",gdata TEXT" \
		");"
	)) {
		cout << "ERROR CREATE TABLE\n";
	}

	// insert
	sqlite->insert("game_runs")
		.use("start_time", "today")
		.use("end_time","tomorrow")
	.execute();

	// lastInsertID
	int last_run_id = sqlite->lastInsertID();
	sqlite->insert("game_run_data")
		.use("runid",last_run_id)
		.use("gdata", "MyData")
	.execute();
	cout << "insert into game_run_data error:" << sqlite->getError() << endl;;


	// insert
	sqlite->insert("scores")
		.use("score", 5999)
		.use(
			"time"
			,ofToString(ofGetDay())
			 +"-" +ofToString(ofGetMonth())
			 +"-" +ofToString(ofGetYear())
			 +" " +ofToString(ofGetHours())
			 +":" +ofToString(ofGetMinutes())
			 +":" +ofToString(ofGetSeconds())
	).execute();

	// get last inserted row id
	cout << "inserted row id: " << sqlite->lastInsertID() << endl;


	ofxSQLiteSelect sel = sqlite->select("id, time").from("scores");
	sel.execute().begin();

	while(sel.hasNext()) {
		int id = sel.getInt();
		std::string name = sel.getString();
		cout << id << ", " << name << endl;
		sel.next();
	}

	// select
	sel = sqlite->select("id, start_time")
		.from("game_runs")
		.join("game_run_data", "runid = id", "runid, gdata")
		.where("runid", 3)
		.orWhere("runid",13)
		.orWhere("runid", last_run_id)
		//.limit(5)
		.order("runid", " DESC ")
		.execute().begin();

	while(sel.hasNext()) {
		int runid = sel.getInt();
		string gdata = sel.getString();
		cout << "runid: " << runid << ", gdata: " << gdata << endl;
		sel.next();
	}

	// update
	sqlite->update("game_runs")
		.use("end_time", "past")
		.where("id", last_run_id)
		.execute();


	// delete
	sqlite->remove("game_runs")
		.where("id",last_run_id)
		.execute();
}roxl

//--------------------------------------------------------------
void testApp::setup(){
}

//--------------------------------------------------------------
void testApp::update(){
}


//--------------------------------------------------------------
void testApp::draw(){
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

