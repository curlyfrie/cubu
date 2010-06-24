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


vector<Faq*> DBHandler::getFaqs() {
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
	return faqs;	
}
vector<Speise*> DBHandler::getSpeisen() {
	query_state = mysql_query(connection, "SELECT * FROM speise");
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	vector <Speise*> speisen; 
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		int id;
		std::string name;
		std::string beschreibung;
		float preis;
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0)
				id = (int)row[i];
			
			if(i== 1)
				name = row[i];
			
			if(i== 2)
				beschreibung = row[i];
			if(i == 3)
				preis = atof(row[i]);
			
		}

		speisen.push_back(new Speise(id, name,beschreibung, preis));
		
	}
	
	mysql_free_result(result);
	return speisen;	
}

vector<Service*> DBHandler::getService() {
	query_state = mysql_query(connection, "SELECT * FROM service");
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	vector <Service*> services; 
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		int id;
		std::string name;
		std::string beschreibung;
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0)
				id = (int)row[i];
			
			if(i== 1)
				name = row[i];
			
			if(i== 2)
				beschreibung = row[i];
			
		}
		
		services.push_back(new Service(id, name,beschreibung));
		
	}
	
	mysql_free_result(result);
	return services;	
}


map <int, Kunde*> DBHandler::getKunden2() {
	query_state = mysql_query(connection, "SELECT * FROM kunde");
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	//vector <Kunde*> kunden;
	map <int, Kunde*> kunden2;

	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		int id;
		std::string vorname;
		std::string nachname;
		std::string adresse;
		std::string kreditkartennummer;
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0)
				id = (int)row[i];
			
			if(i== 1)
				vorname = row[i];
			
			if(i== 2)
				nachname = row[i];
			if(i== 3)
				adresse = row[i];
			if(i== 4)
				kreditkartennummer = row[i];
			
			
			printf("[%.*s] ", (int) lengths[i],
				   row[i] ? row[i] : "NULL");
		}
		
		 Kunde  * kunde = new Kunde(id, vorname, nachname, adresse, kreditkartennummer);
		
		printf("\n");
		kunden2.insert(make_pair(1, kunde));
		for(map <int, Kunde*>::iterator it = kunden2.begin();it!=kunden2.end(); ++it)
		{
			cout << "ID " << it->first;
		}
		//kunden.push_back(kunde);
		
	}
	
	mysql_free_result(result);
	return kunden2;	
	
	
	
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


