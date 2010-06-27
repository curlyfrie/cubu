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

	//Datenbank starten
	setupMYSQLDB();

	
	//ID of this room: WARNING, HARD CODED!
	terminalID = 1;


	alarm_hour = 6;
	showFaq = false;
	selected_button = 0;

	buttons.clear();
	strings.clear();
	pics.clear();
	
	setupGUI();

	//	show fiducial window YES or NO
	//	can be switched with 'f'
	showFiducialWindow = false;
	
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


	if(dbhandler->getAlarm(terminalID) != "")
		alarmset = true;
	else
		alarmset = false;

	

	temperature = 20;
	
	time = 0;
	
	// define threshold to find fiducial
	fiducial_threshold =135;
	
	// set fontsize
	font_size = 32;
	
	// load font
	franklinBook.loadFont("frabk.ttf",font_size);
	buttonlabel.loadFont("frabk.ttf", 12);
	font.loadFont("bankg.ttf",32);
	
	// setup fiducials
	vidGrabber.listDevices();
	//vidGrabber.setDeviceID(<#int _deviceID#>);
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);

}
//--------------------------------------------------------------
void cubu::setupGUI()
// prepares the gui to be drawn
{

	buttons.clear();
	strings.clear();
	pics.clear();

	Display *display =new Display();

	if(active_side == -1){
		//gui.setPage("empty");
		alarm_hour = 6;

	}
	else{
		
		if(active_side == side_fun){

			display->draw("fun1", &buttons, &strings, &pics);

		}
		else if (active_side == side_activities) {
			// do cool stuff here
			display->draw("activities1", &buttons, &strings, &pics);
		}
		else if (active_side == side_alarm) {
			// do cool stuff here

			display->draw("alarm1", &buttons, &strings, &pics);
		}
		else if (active_side == side_food) {
			// do cool stuff here

			display->draw("food1", &buttons, &strings, &pics);
		}
		else if (active_side == side_roomservice) {

			display->draw("roomservice1", &buttons, &strings, &pics);

			
		}
		else if (active_side == side_temperature) {
			// do cool stuff here

			display->draw("temperature1", &buttons, &strings, &pics);
			

		
			/*
			buttons.clear();
			buttons.push_back(new cubuButton(500,700,"button1"));
			buttons.push_back(new cubuButton(700,700,"button2"));
			buttons.push_back(new cubuButton(900,700,"button3"));
			 */
		}
	
	}
		
}




void cubu::setupMYSQLDB(){
		
	dbhandler = new DBHandler();
	dbhandler->getTerminals();
	faqs  = dbhandler->getFaqs();
	//speisen = dbhandler->getSpeisen();

	kunden = dbhandler->getKunden2();
	//terminal mit id 1 wird geladen
	terminal = dbhandler->getTerminal(1);
	

	bestellungen = dbhandler->getBestellungen(terminal);
	for(int i = 0; i < bestellungen.size(); i++)
	{
		
		cout << "bestellte Speisen " ;
		speise = dbhandler->getSpeise(bestellungen.at(i)->getSpeiseId());
		cout << speise->getName();

	}
	kunde = dbhandler->getKunde(terminal);
	
	
	//int kundenid = dbhandler->getKundenId(terminalID);
	
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

				//Aufruf der alarm action
				
				// set a new alarm
				if(!alarmset){
					setAlarm();
				}
				// alarm is already set
				else {

					//getAlarm String formatieren
					
					std::string s = dbhandler->getAlarm(terminalID);
					s.insert(2, "h");
					s.insert(6, "min");
					
					stringtodraw = " " + s + "\n\nAlarm is set";
				}
				

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
				setTemp();
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
	else if(alarm_hour >= 24){
		alarm_hour = 0;
		alarm_minute = 0;
	}
	else if(alarm_minute < 0){
		if(alarm_hour == 0)
			alarm_hour = 23;
		else
			alarm_hour -= 1;
		
		alarm_minute = 50;
	}
	else if(alarm_hour < 0)
		alarm_hour = 0;
	
	//Ausgabestring formatieren
	
	std::stringstream stream2;
	std::stringstream stream3;
	
	if(alarm_minute == 0)
		stream2 << "00";
	else
		stream2 << alarm_minute;

	if(alarm_hour < 10)
		stream3 << "0" << alarm_hour;
	else
		stream3 << alarm_hour;
	
	stringtodraw = " "+ stream3.str()  + "h:" +  stream2.str() + "min";
	
	//cout << "set alarm to" << alarm_hour << "." << alarm_minute << endl;
	//cout << "set Alarm:" << stringtodraw << endl;
	
}
void cubu::setTemp()
// set the temp
{
	// get current rotation
	int direction = getRotDirection();
	
	// smoothness is hardcoded!
	
	if(temperature > 15 && temperature < 30)
		temperature += direction*0.5;
	
	//Ausgabestring formatieren
	
	std::string s;
	for(int i=0; i<5; i++){
		
		/*stream2 << 

		s = stream2.str();
		s.insert(2, ".");
		s.insert(5, " C\n");
		cout << s << endl;
		stringtodraw += s;
		stream2.clear();
		s = "";*/

		std::stringstream stream2;
		stream2 << (temperature-1+(i*0.5))*100;
		
		s += stream2.str()+"C\n";
		
	}

	stringtodraw = s;
	//cout << "set alarm to" << alarm_hour << "." << alarm_minute << endl;
	//cout << "set Alarm:" << stringtodraw << endl;
	
}

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
	ofSetColor(255,255,255);
	ofImage img;
	img.loadImage("img/background.png");
	img.draw(0,0);
	
	//set Background Color
	//ofBackground(126, 169, 203);

	//draw font
	//ofSetColor(0x3366aa);
	
	
	//draw GUI
	drawGUI();


	// draw fiducial window
	if(showFiducialWindow)
	{
				
		
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

	

	cubuPic * currentpic;
	for(int i = 0; i < pics.size(); i++){
		currentpic = pics.at(i);
		currentpic->pic.draw(currentpic->x,currentpic->y);
	}


	cubuString * currentstring;
	for(int i = 0; i < strings.size(); i++){
		currentstring = strings.at(i);

		ofSetColor(currentstring->color);
		currentstring->font.drawString(currentstring->text, currentstring->x, currentstring->y);
	}

	cubuButton* currentbutton;
	for(int i = 0; i < buttons.size(); i++){
		currentbutton = buttons.at(i);
		ofFill();
		if(currentbutton->selected)
			ofSetColor(100,0,0);
		else
			ofSetColor(105,105,105);
		ofRectangle rect = buttonlabel.getStringBoundingBox(currentbutton->label, 0,0);
		ofRect(currentbutton->x, currentbutton->y, currentbutton->height+rect.width, currentbutton->height);
		ofSetColor(255, 255, 255);
		buttonlabel.drawString(currentbutton->label, currentbutton->x+currentbutton->height/2, currentbutton->y+currentbutton->width/4);
	}
	

	if(active_side == side_alarm)
		font.drawString(stringtodraw, 630, 270);
	else if(active_side == side_temperature)
		font.drawString(stringtodraw, 630, 270);
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
	{
		cout << "drawfood"<< speisen.at(i)->getName()<<endl;
		buttons.push_back(new cubuButton(500,200 + i * 50 ,speisen.at(i)->getName()));
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
		/*//DEBUGGIN AHEAD!
		case 'b':
			///cout << "alarm == " <<   dbhandler->getAlarm(0);
			
			break;*/
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
	
	Display *display;
	display = new Display();

	if(button == 0){
		int temp = -1;
		// check if any button was hit
		for(int i = 0; i < buttons.size(); i ++){
			if(buttons.at(i)->click(x,y) == true){
				cout << "you have hit button: " << i << endl; 
				buttons.at(i)->select(true);
				display->draw(buttons.at(selected_button)->label, &buttons, &strings, &pics);
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
					
			dbhandler->setAlarm(terminalID, alarm_hour, alarm_minute);
			//saveAlarmtoDB();
		}
		else if (active_side == side_alarm && alarmset) {
			alarmset = false;
			dbhandler->deleteAlarm(terminalID);
		}
		else{
			
			//TEST per klick GUI LADEN
			// works
			
			display->draw(buttons.at(selected_button)->label, &buttons, &strings, &pics);
		/*	Display* display;
			display = new Display();
			display->draw("roomservice1", &buttons, &strings, &pics);
			*/
		}

		
	}
}

//--------------------------------------------------------------
void cubu::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void cubu::windowResized(int w, int h){

}

void cubu::clearAll() {
	buttons.clear();
	strings.clear();
	pics.clear();

}