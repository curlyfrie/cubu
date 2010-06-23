/*
 *  dbhandler.cpp
 *
 *  Created by Patrick Stipsits on 16.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "DBHandler.h"
#include <sstream>
#include <string>
using namespace std;
DBHandler::DBHandler()
// setup connection to database
{

	mysql_init(&mysql);	//connection = mysql_real_connect(&mysql,"host","user","password","database",0,0,0);
	connection = mysql_real_connect(&mysql,"spanish-jewelry.com","d00e2d6b","9x69rLHnf4K4yQrg","d00e2d6b",0,0,0);
	if (connection == NULL) {
		cout << mysql_error(&mysql) << endl;
	}
	
	
	
}
DBHandler::~DBHandler()
// setup connection to database
{

	
}

void DBHandler::deleteFaq(int id)
{
	
	std::string idString;
	std::stringstream out;
	out << id;
	idString = out.str();
	
	std::string query = "DELETE FROM faq where faq_id = " + idString;
	 mysql_query(connection,query.c_str());	
}
/*
std::string[] DBHandler::printFaqs(){
	std::string[] output;
	query_state = mysql_query(connection, "SELECT * FROM faq");
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		for( i = 0; i < num_fields; i++)
		{
			printf("[%.*s] ", (int) lengths[i],
				   row[i] ? row[i] : "NULL");
		} 
		printf("\n");
		
	}
	mysql_free_result(result);
	
	// just a little test
	Terminal * t = new Terminal(2,'bla','1234');
	
}

*/


void DBHandler::getFaqs() {
	query_state = mysql_query(connection, "SELECT * FROM faq");
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	vector <Faq*> faqs; 
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		int id;
		std::string question;
		std::string answer;
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0)
				id = (int)row[i];
			
			if(i== 1)
				question = row[i];
			
			if(i== 2)
				answer = row[i];
			
			
			printf("[%.*s] ", (int) lengths[i],
				   row[i] ? row[i] : "NULL");
		}
		Faq * faq = new Faq(id, question, answer);
		printf("\n");
		faq->printFaq();
		faqs.push_back(faq);
		
	}
	mysql_free_result(result);
	

	
	
}

void DBHandler::getTerminals() {
	query_state = mysql_query(connection, "SELECT * FROM terminal");
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		for( i = 0; i < num_fields; i++)
		{
			printf("[%.*s] ", (int) lengths[i],
				   row[i] ? row[i] : "NULL");
		}
		printf("\n");
		
	}
	mysql_free_result(result);
	
	// just a little test
	Terminal * t = new Terminal(2,'bla','1234');
	
	
}


