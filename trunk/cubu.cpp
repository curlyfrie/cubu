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
	
	// define no. of marker for sides
	side_alarm = 1;
	side_activities = 2;
	side_food = 3;
	side_roomservice = 4;
	side_fun = 5;
	side_temperature = 6;
	
	active_side = -1;
	
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

			//cout << "markerID == " << fiducialID;


			switch (fiducialID)
			{
				case 1:
					stringtodraw = "Marker 1 is visible";
					break;
				case 2:
					stringtodraw = "Marker 2 is visible";
					//cout << stringtodraw;
					break;
				case 3:
					stringtodraw = "Marker 3 is visible";
					break;
				case 4:
					stringtodraw = "Marker 4 is visible";
					break;
				case 5:
					stringtodraw = "Marker 5 is visible";
					break;
				case 6:
					stringtodraw = "Marker 6 is visible";
					break;
					
					
			}

			int fid_pos = fiducial.getX();
			//if(fid_pos < 0 ) return;
			
		}
		else{
			stringtodraw = "NO MARKER VISIBLE";
		}
		
	}

}

//--------------------------------------------------------------
void cubu::draw(){
		
	//draw font
	ofSetColor(0x3366aa);
	
	franklinBook.drawString(stringtodraw, 100,310);
	
	// draw fiducial window
	
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

//--------------------------------------------------------------
void cubu::keyPressed(int key){
	cout << "key key key!";
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

