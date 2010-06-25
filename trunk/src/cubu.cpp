#include "cubu.h"

cubu::cubu()
{
	//setup() seems to be enough
}

cubu::~cubu()
{
	// exit should do the same stuff
}
//--------------------------------------------------------------
void cubu::setup(){
	showFaq = false;
	
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
	side_food = 0;
	side_roomservice = 3;
	side_fun = 5;
	side_temperature = 2;
	
	// reset helpers
	active_side = -1;
	prev_side = -1;
	previous_angle = -1;
	current_angle = -1;


	alarmset = false;
	buttonset = -1;
	time = 0;
	
	
	// define threshold to find fiducial
	fiducial_threshold =135;
	
	// set fontsize
	font_size = 32;
	
	// load font
	franklinBook.loadFont("frabk.ttf",font_size);
	buttonlabel.loadFont("frabk.ttf", 12);
	
	// setup fiducials
	vidGrabber.listDevices();
	//vidGrabber.setDeviceID(<#int _deviceID#>);
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);


	//Datenbank starten
	setupMYSQLDB();
}
//--------------------------------------------------------------
void cubu::setupGUI()
// prepares the gui to be drawn
{

	buttonset = -1;

	if(active_side == -1){
		//gui.setPage("empty");

		
	}
	else{
		
		//empty the list of buttons
		
		
		if(active_side == side_fun){
			// do cool stuff here
			buttons.clear();
		}
		else if (active_side == side_activities) {
			// do cool stuff here
			buttons.clear();
		}
		else if (active_side == side_alarm) {
			// do cool stuff here
			buttons.clear();
		}
		else if (active_side == side_food) {
			// do cool stuff here
			buttons.clear();
		}
		else if (active_side == side_roomservice) {

			Display* display;
			display = new Display();
			display->drawRoomservice(&buttons);
			
		}
		else if (active_side == side_temperature) {
			// do cool stuff here
			

		
			/*
			buttons.clear();
			buttons.push_back(new cubuButton(500,700,"button1"));
			buttons.push_back(new cubuButton(700,700,"button2"));
			buttons.push_back(new cubuButton(900,700,"button3"));
			 */
		}
		else
			buttons.clear();
	}
		
}




void cubu::setupMYSQLDB(){
		
	dbhandler = new DBHandler();
	dbhandler->getTerminals();
	faqs  = dbhandler->getFaqs();
	speisen = dbhandler->getSpeisen();
	kunden = dbhandler->getKunden2();
	//terminal mit id 1 wird geladen
	terminal = dbhandler->getTerminal(1);
	
	//int kundenid = dbhandler->getKundenId(roomID);
	
	//map<int, Kunde*>::iterator kundenIt = kunden.find(kundenid);
	
	//mittels der zeile kann in die db terminal, speise eingefŸgt werden
//	dbhandler->insertTerminalSpeise(terminal, speisen.at(0));
	
	
	//Kunde * k = kundenIt->second;
	
}

//--------------------------------------------------------------
void cubu::update(){

	//cout << active_side << endl;
	
	// update fiducial
	vidGrabber.grabFrame();

	if(vidGrabber.isFrameNew())
	{
		
		// updateGUI if cube side has changed
		if(prev_side != active_side)
			setupGUI();

		prev_side = active_side;


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
			time  = 0;
			
			ofxFiducial fiducial = fidfinder.fiducialsList.front();
			fiducialID =  fiducial.getId();

			// get rotation of marker
			std::stringstream stream;

			if(fiducial.getAngleDeg() != 360)
				current_angle = fiducial.getAngleDeg();
			
			//.. and print it (debugging)
			stream << current_angle;
			rotation = "current angle: " + stream.str();
			


			// check wich side is active
			if(fiducialID == side_activities){
				active_side = side_activities;
			}
			else if(fiducialID == side_alarm){
				active_side = side_alarm;

//Aufruf der alarm action die alles weiter handelt

			/*	
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
					stringtodraw = " is set to: " + stream3.str()  + "h:" +  stream2.str() + "min";
				}
				*/

			}
			else if(fiducialID == side_fun){
				active_side = side_fun;
			}
			else if(fiducialID == side_food){
				active_side = side_food;
			}
			else if(fiducialID == side_roomservice){
				active_side = side_roomservice;
			}
			else if(fiducialID == side_temperature){
				active_side = side_temperature;
			}
						
			
			//Button Selection via rotation
			if(buttons.size()>0){
			
				// update index of selected button
				int previous = selected_button;
				selected_button = selected_button + getRotDirection();
				
				
				// revert selection if index exceeds no of buttons
				if(selected_button < 0 || selected_button > buttons.size()-1)
					selected_button = previous;
					
				for (int i = 0; i< buttons.size(); i++)
				{	
					if(i == selected_button)
						buttons.at(i)->select(true);
					else
						buttons.at(i)->select(false);
				}				
			}

		}
		else{
			
			//wenn kein marker aktiv: time erhoehen
			time++;
			
			//überbrückung kurzes nicht erkennens des markers
			if (time > 10){
				active_side = -1;
				time = 0;
			}
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
	stringtodraw =  " " + stream3.str()  + "h:" +  stream2.str() + "min";
	
	//cout << "set alarm to" << alarm_hour << "." << alarm_minute << endl;
	//cout << "set Alarm:" << stringtodraw << endl;
	
}
//--------------------------------------------------------------
void cubu::saveAlarmtoDB(){

	
}
//--------------------------------------------------------------
void cubu::getAlarmfromDB(){

	
}

//--------------------------------------------------------------
int cubu::getRotDirection()
// returns -1 if (marker)rotation is CW, +1 if rotation is CCW and 0 if nothing has changed
{
	int direction;
	
	// do nothing if difference is to small 
	int gap = current_angle - previous_angle;
	if(abs(gap) < sensitivity)
		return 0;
	
	if(gap >= 0){

		if (gap <= 180){
			//CW
			direction = -1;
		}
		else{
			//CCW
			direction = 1;
		}
	}
	else{

		if (gap > -180){
			//CCW
			direction = 1;
		}
		else{
			//CW
			direction = -1;
		}
	}
		

//	cout << "ROTATION: cur: " << current_angle << " prev: " << previous_angle << " gap: " <<gap << "  " << direction << endl;

	// set the new angle
	previous_angle = current_angle;
	
	return direction;
}
//--------------------------------------------------------------
void cubu::draw(){
	
	//set Background Color
	//ofBackground(126, 169, 203);

	//draw font
	//ofSetColor(0x3366aa);
	
	
	//draw GUI
	drawGUI();


	
	//franklinBook.drawString(rotation, 100, 100);
	



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
	}
	
}
//--------------------------------------------------------------
void cubu::drawGUI(){
// draws the gui


	
	if(active_side == -1 && showFaq == true)
		drawFaq();
	else {
		showFaq = false;
	}

		
	if(active_side != -1){
		if(active_side == side_food) {
			franklinBook.drawString("Food", 100,200);	
			drawFood();
		}
		if(active_side == side_alarm){	
			franklinBook.drawString("Alarm", 100,200);
			drawAlarm();
		}
		if(active_side == side_roomservice)	
			franklinBook.drawString("Room Service", 100,200);	

		if(active_side == side_temperature){	
			franklinBook.drawString("Air Condition", 100,200);	


		}
		if(active_side == side_activities)	
			franklinBook.drawString("Activities", 100,200);	

		if(active_side == side_fun)	
			franklinBook.drawString("Fun!", 100,200);	

	}
	
	
	cubuButton* currentbutton;
	for(int i = 0; i < buttons.size(); i++){
		currentbutton = buttons.at(i);
		ofFill();
		if(currentbutton->selected && buttonset == i)
			ofSetColor(238,0,0);
		else if(currentbutton->selected)
			ofSetColor(100,0,0);
		else
			ofSetColor(105,105,105);
		ofRect(currentbutton->x, currentbutton->y, currentbutton->width, currentbutton->height);
		ofSetColor(255, 255, 255);
		buttonlabel.drawString(currentbutton->label, currentbutton->x+currentbutton->height/2, currentbutton->y+currentbutton->width/4);
	}
	
}

void cubu::drawFaq(){
	
	for(int i = 0; i < faqs.size(); i++)
	{
		franklinBook.drawString(faqs.at(i)->getQuestion(), 100,100 + i *100);
		franklinBook.drawString(faqs.at(i)->getAnswer(), 150,150 + i *100);

	}
	
}

void cubu::drawFood(){
	
	for(int i = 0; i < speisen.size(); i++)
		buttons.push_back(new cubuButton(400,200,speisen.at(i)->getName()));
	
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
		case 'h':

			showFaq  = !showFaq; break;
			
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
	
	//ACTION - Aufruf statt hier..
	/////////////////////////////////
	
	if(button == 0){
		int temp = -1;
		// check if any button was hit
		for(int i = 0; i < buttons.size(); i ++){
			if(buttons.at(i)->click(x,y) == true){
				cout << "you have hit button: " << i << endl; 
				buttons.at(i)->select(true);
				temp = i;
				break;
			}
				
		}
		// if selection was made: deselect every other button 
		if(temp != -1){
			for(int i = 0; i < buttons.size(); i++){
				if(i != temp)
					buttons.at(i)->select(false);
			}
		}
	}
	if (button==1) {
		if(active_side == side_alarm && !alarmset){
			alarmset = true;
			
			
			dbhandler->setAlarm(roomID, alarm_hour, alarm_minute);
			//saveAlarmtoDB();
		}
		else if (active_side == side_alarm && alarmset) {
			alarmset = false;
		}

		if(buttonset < 0){
			buttonset = selected_button;
		}
		else
			buttonset = -1;
		
	}
}

//--------------------------------------------------------------
void cubu::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void cubu::windowResized(int w, int h){

}