/*
 *  Faq.cpp
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Faq.h"

Faq::Faq(int _id, std::string _question, std::string _answer)
{
	
	id = _id;
	question = _question;
	answer = _answer;
	
	
}

void Faq::printFaq(){
	std::cout << question;
}
