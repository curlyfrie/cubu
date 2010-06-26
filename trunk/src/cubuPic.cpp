/*
 *  cubuPic.cpp
 */

#include "cubuPic.h"

cubuPic::cubuPic(){

}

cubuPic::cubuPic(std::string pimg, float px, float py){
	x = px;
	y = py;
	img = pimg;	
	pic.loadImage(pimg);

}