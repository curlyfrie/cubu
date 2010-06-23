#include "cubu.h"

cubu::cubu()
{
	//setup() seems to be enough
}

cubu::~cubu()
{
	//delete sqlite;
	// exit should do the same stuff
}
//--------------------------------------------------------------
void cubu::setup(){
	
	// 
	setupGUI();
	selected_button = 0;
	
	//nr and ID of this room: WARNING, HARD CODED!
	roomNr = 101;
	roomID = 1;	
	
	//	show fiducial window YES or NO
	//	can be switched with 'f'
	showFiducialWindow = true;
	
	//sensitivity of optical marker
	sensitivity = 5;
	
	// set no. of marker for sides
	side_activities = 4;
	side_alarm = 1;
	side_food = 3;
	side_roomservice = 2;
	side_fun = 5;
	side_temperature = 6;
	
	// reset helpers
	active_side = -1;
	alarmset = false;
	previous_angle = -1;
	current_angle = -1;
	
	//Setup Database
	//setupDB();
	
	// define threshold to find fiducial
	fiducial_threshold =135;
	
	// set fontsize
	font_size = 32;
	
	// load font
	franklinBook.loadFont("frabk.ttf",font_size);
	
	
	// setup fiducials
	vidGrabber.listDevices();
	//vidGrabber.setDeviceID(<#int _deviceID#>);
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);

	setupMYSQLDB();
}
//--------------------------------------------------------------
void cubu::setupGUI()
// prepares the gui to be drawn
{
	if(active_side == -1){
		//gui.setPage("empty");
	}
	else{
		
		//empty the list of buttons
		buttons.clear();
		
		if(active_side == side_fun){
			// do cool stuff here
		}
		else if (active_side == side_activities) {
			// do cool stuff here
		}
		else if (active_side == side_alarm) {
			// do cool stuff here
		}
		else if (active_side == side_food) {
			// do cool stuff here
		}
		else if (active_side == side_roomservice) {
			
			// insert buttons into vector
			buttons.push_back(new cubuButton(100,200));
			buttons.push_back(new cubuButton(300,200));
		}
		else if (active_side == side_temperature) {
			// do cool stuff here
		}
	}
	
	
	//buttons.push_back(15);
	
}


//--------------------------------------------------------------
void cubu::setupDB(){
//establish connection do database
	
	sqlite = new ofxSQLite("cubu2.sqlite");
	
	/*cout << "creating table...";	
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
	//convert time to timestamp
	// insert this client
	sqlite->insert("alert").use("terminal_id",ofToString(roomNr)).use("time","00:00:00").use("aktiv","FALSE").execute();


}

void cubu::setupMYSQLDB(){
		
	dbhandler = new DBHandler();
	dbhandler->getTerminals();
	faqs  = dbhandler->getFaqs();
	kunden = dbhandler->getKunden2();
	
}

//--------------------------------------------------------------
void cubu::update(){

	// updateGUI
	setupGUI();
	
	//ofBackground(255, 255, 255);
	
	// update fiducial
	vidGrabber.grabFrame();
	if(vidGrabber.isFrameNew())
	{
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		grayImage = colorImg;
		grayBg = grayImage;
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff = grayImage;
		
		grayDiff.threshold(fiducial_threshold);
		fidfinder.findFiducials( grayDiff );
		
		int fiducialID = -1;
		
		// find fiducials...
		if (fidfinder.fiducialsList.size() == 1){
			
			ofxFiducial fiducial = fidfinder.fiducialsList.front();
			fiducialID =  fiducial.getId();

			// get rotation of marker
			std::stringstream stream;
			current_angle = fiducial.getAngleDeg();
			
			//.. and print it (debugging)
			stream << current_angle;
			rotation = "current angle: " + stream.str();
			//cout << "angle == "<< current_angle << endl;
			
			
			// check wich side is active
			if(fiducialID == side_activities){
				stringtodraw = "Marker 1: Activities";
				active_side = side_activities;
			}
			else if(fiducialID == side_alarm){
				stringtodraw = "Marker 2: Alarm";
				active_side = side_alarm;
				
				// set a new alarm
				if(!alarmset){
					setAlarm();
				}
				// alarm is already set
				else {
					std::stringstream stream2;
					stream2 << alarm_minute;
					
					std::stringstream stream3;
					stream3 << alarm_hour;
					stringtodraw = stringtodraw + " is set to: " + stream3.str()  + "h:" +  stream2.str() + "min";
				}
			}
			else if(fiducialID == side_fun){
				stringtodraw = "Marker 3: Fun";
				active_side = side_fun;
			}
			else if(fiducialID == side_food){
				stringtodraw = "Marker 4: Food";
				active_side = side_food;
			}
			else if(fiducialID == side_roomservice){
				stringtodraw = "Roomservice";
				active_side = side_roomservice;
			}
			else if(fiducialID == side_temperature){
				stringtodraw = "Marker 6: Temperature Control";
				active_side = side_temperature;
			}
			
			// update index of selected button
			int previous = selected_button;
			selected_button = selected_button + getRotDirection();
			
			
			// revert selection if index exceeds no of buttons
			if(selected_button < 0 || selected_button > buttons.size()-1)
				selected_button = previous;
			
			buttons.at(selected_button)->select(true);
			
			//cout << "selected button" << selected_button << endl;
		}
		else{
			stringtodraw = "NO MARKER VISIBLE";
			active_side = -1;
			/*fiducial_threshold += 10;
			if(fiducial_threshold > 200)
				fiducial_threshold = 50;
			update();
*/
		}
		
	}

}
//--------------------------------------------------------------
void cubu::setAlarm()
// set the alarm timer form user input
{
	// get current rotation
	int direction = getRotDirection();
	
	// smoothness is hardcoded!
	alarm_minute += direction*10;
	
	if(alarm_minute >= 60){
		alarm_hour += 1;
		alarm_minute = 0;
	}
	if(alarm_hour >= 24){
		alarm_hour = 0;
		alarm_minute = 0;
	}
	if(alarm_minute < 0){
		alarm_hour -= 1;
		alarm_minute = 0;
	}
	if(alarm_hour < 0)
		alarm_hour = 0;
	
	std::stringstream stream2;
	stream2 << alarm_minute;
	
	std::stringstream stream3;
	stream3 << alarm_hour;
	stringtodraw = stringtodraw + " " + stream3.str()  + "h:" +  stream2.str() + "min";
	
	//cout << "set alarm to" << alarm_hour << "." << alarm_minute << endl;
	//cout << "set Alarm:" << stringtodraw << endl;
	
}
//--------------------------------------------------------------
void cubu::saveAlarmtoDB(){
//save current alarm time to DB
	
	//cout << "saving current alarm time to db" << ofToString(alarm_hour) << ":" << ofToString(alarm_minute) << endl;
	
	sqlite->update("room").use("alarm_hour",ofToString(alarm_hour)).use("alarm_minute", ofToString(alarm_minute)).where("number",roomNr).execute();
}
//--------------------------------------------------------------
void cubu::getAlarmfromDB(){
	//get the current alarm setting for this room

	//sqlite->update("room").use("alarm",ofToString(alarm_hour) + ofToString(alarm_minute)).where("number",roomNr).execute();
	
	cout << "selecting from DB...";
	ofxSQLiteSelect sel = sqlite->select("number,alarm_hour,alarm_minute").from("room").where("number",roomNr);
	sel.execute().begin();
	while(sel.hasNext()) {
		int number = sel.getInt();
		int alarm_hour = sel.getInt();
		int alarm_minute = sel.getInt();
		cout << "roomnumber: " << number << " alarm: " << alarm_hour << ":" << alarm_minute << endl;
		sel.next();
	}
	cout << "done" << endl;
	
}

//--------------------------------------------------------------
int cubu::getRotDirection()
// returns +1 if (marker)rotation is CW, -1 if rotation is CCW and 0 if nothing has changed
{
	int direction;
	
	// do nothing if difference is to small 
	int gap = current_angle - previous_angle;
	if(abs(gap) < sensitivity)
		return 0;
	
	// turn-direction is CW
	if(current_angle < previous_angle){
		direction = 1;
	}
	// turn-direction is CCW
 	else if(current_angle > previous_angle)
		direction = -1;
	
	// set the new angle
	previous_angle = current_angle;
	
	//cout << "direction" << direction << endl;
	return direction;
}
//--------------------------------------------------------------
void cubu::draw(){
	drawFaq();

	//set Background Color
	ofBackground(126, 169, 203);
	
	//draw GUI
	//gui.draw();
	drawGUI();
	
	//draw font
	ofSetColor(0x3366aa);
	
	if(active_side == side_alarm)
		drawAlarm();
	
	
	//franklinBook.drawString(stringtodraw, 100,310);
	franklinBook.drawString(rotation, 100, 100);
	
	// draw fiducial window
	if(showFiducialWindow)
	{
		ofSetColor(255,255,255);
		grayDiff.draw(20, 450);
		//colorImg.draw(20,430);
	
		for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++) 
		{
			fiducial->draw( 20, 430 );//draw fiducial
			fiducial->drawCorners( 20, 430 );//draw corners
			//cout << "fiducial " << fiducial->getId() << " found at ( " << fiducial->getX() << "," << fiducial->getY() << " )" << endl;
		}
		
		//cout << "rotation == " << rotation;
	}
	

}
//--------------------------------------------------------------
void cubu::drawGUI(){
// draws the gui
	
	cubuButton* currentbutton;
	for(int i = 0; i < buttons.size(); i++){
		currentbutton = buttons.at(i);
		ofFill();
		if(currentbutton->selected)
			ofSetColor(238,0,0);
		else
			ofSetColor(105,105,105);
		ofRect(currentbutton->x, currentbutton->y, currentbutton->width, currentbutton->height);
	}
	
}

void cubu::drawFaq(){
	for(int i = 0; i < faqs.size(); i++)
	{
		franklinBook.drawString(faqs.at(i)->getQuestion(), 100,100 + i *100);
		franklinBook.drawString(faqs.at(i)->getAnswer(), 150,150 + i *100);

	}
	
}

//--------------------------------------------------------------
void cubu::drawAlarm() {
//draw any cool gfx for alarm here
	
	franklinBook.drawString(stringtodraw, 100,310);
	if(alarmset)
		franklinBook.drawString("klick or press 'a' to reset", 100,350);
}

//--------------------------------------------------------------
void cubu::keyPressed(int key){
	
	switch (key){
			
		// press f to turn fiducialwindow ON or OFF
		case 'f':
			if(showFiducialWindow)
				showFiducialWindow = false;
			else
				showFiducialWindow = true;
			break;
			
		case 'a':
			if(active_side == side_alarm && !alarmset){
				alarmset = true;
			}
			else if (active_side == side_alarm && alarmset) {
				alarmset = false;
			}
			break;
		//DEBUGGIN AHEAD!
		case 'b':
			//getAlarmfromDB();
			//database = new dbhandler();
			
			/*
			cubuButton* button2;
			button2 = new cubuButton(10,14);
			cout << "button2" << endl;
			cout << "shape witdh: " << button2->shape.width << endl;
			 */
			
			
			break;
		case '-':
			fiducial_threshold-=5;
			cout<<"threshold = "<<fiducial_threshold<<endl;
			break;
		case '+':
			fiducial_threshold+=5;
			cout<<"threshold = "<<fiducial_threshold<<endl;
			break;

		default: break;
	}
}	

//--------------------------------------------------------------
void cubu::keyReleased(int key){

}

//--------------------------------------------------------------
void cubu::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void cubu::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void cubu::mousePressed(int x, int y, int button){
	if (button==2) {
	if(active_side == side_alarm && !alarmset){
		alarmset = true;
		saveAlarmtoDB();
	}
	else if (active_side == side_alarm && alarmset) {
		alarmset = false;
	}
	}
}

//--------------------------------------------------------------
void cubu::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void cubu::windowResized(int w, int h){

}

