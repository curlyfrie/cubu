/*
 *  CubuString.cpp
 */

#include "cubuString.h"

cubuString::cubuString(){
	
	setDefaultValues();
}

cubuString::cubuString( std::string ptext, float px, float py, std::string pfont, int psize, int pcolor){
	
	x = px;
	y = py;

	text = ptext;
/*
	while(ptext.find("\\n") != string::npos){
		text.replace(ptext.find("\\n"),2,"\n");
	}
*/

	text = str_replace("\\n","\n",ptext);

	color = pcolor;
	font.loadFont(pfont,psize);

}
cubuString::cubuString( std::string ptext, float px, float py, std::string pfont, int psize){
	
	x = px;
	y = py;
	text = ptext;
	color = 0x000000;
	font.loadFont(pfont,psize);

}

cubuString::cubuString( std::string ptext, float px, float py){
	
	x = px;
	y = py;
	text = ptext;
	color = 0x000000;
	font.loadFont("frabk.ttf",100);
	
}

cubuString::cubuString( std::string ptext){
	
	x = 20;
	y = 100;
	text = ptext;
	color = 0x000000;
	font.loadFont("bankg.ttf",32);
	
}

void cubuString::appendString(std::string text2)
{
	text = text + text2;

}
void cubuString::setDefaultValues(){
	
	x = 100;
	y = 400;
	text = "TEST";
	font.loadFont("frabk.ttf",100);
}
std::string cubuString::str_replace (std::string rep, std::string wit,std::string in) {
  int pos;
  while (true) {
    pos = in.find(rep);
    if (pos == -1) {
      break;
    } else {
      in.erase(pos, rep.length());
      in.insert(pos, wit);
    }
  }
  return in;
}