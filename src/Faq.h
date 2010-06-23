/*
 *  Faq.h
 *  cubu
 *
 *  Created by Alexander Fried on 23.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>

class Faq {

	
private:
	int id;
	std::string question;
	std::string answer;
public:

	Faq(int id, std::string question, std::string answer);
	void printFaq();
	std::string getQuestion();
	std::string getAnswer();
	int getId();
	
	~Faq();
	
	
};