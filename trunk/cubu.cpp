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
	
	//	show fiducial window YES or NO
	//	can be switched with 'f'
	showFiducialWindow = true;
	
	// set no. of marker for sides
	side_activities = 1;
	side_alarm = 2;
	side_food = 3;
	side_roomservice = 4;
	side_fun = 5;
	side_temperature = 6;
	
	// reset helpers
	active_side = -1;
	alarmset = false;
	previous_angle = -1;
	current_angle = -1;
	
	
	// define threshold to find fiducial
	fiducial_threshold = 135;
	
	// define font size
	font_size = 20.0f;
	
	// load font
	franklinBook.loadFont("frabk.ttf",32);
	
	
	// setup fiducials
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
}

//--------------------------------------------------------------
void cubu::update(){

	ofBackground(255, 255, 255);
	
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
				stringtodraw = "Marker 5: Roomservice";
				active_side = side_roomservice;
			}
			else if(fiducialID == side_temperature){
				stringtodraw = "Marker 6: Temperature Control";
				active_side = side_temperature;
			}
				
		}
		else{
			stringtodraw = "NO MARKER VISIBLE";
			active_side = -1;
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
int cubu::getRotDirection()
// returns +1 if rotation is CW, -1 if rotation is CCW and 0 if nothing has changed
{
	int direction;
	
	// do nothing if difference is to small 
	int gap = current_angle - previous_angle;
	if(abs(gap) < 5)
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
		
	//draw font
	ofSetColor(0x3366aa);
	
	franklinBook.drawString(stringtodraw, 100,310);
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
			if(active_side == side_alarm)
				cout << "alarm is set!" << endl;
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

}

//--------------------------------------------------------------
void cubu::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void cubu::windowResized(int w, int h){

}

