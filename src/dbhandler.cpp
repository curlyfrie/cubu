/*
 *  dbhandler.cpp
 *
 *  Created by Patrick Stipsits on 16.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "DBHandler.h"

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


