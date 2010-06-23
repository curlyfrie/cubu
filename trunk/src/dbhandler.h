/*
 db handler should interact with database
 */

#include "ofMain.h"
#include <iostream>
#ifdef _WIN32 || _WIN64
	#include <my_global.h>
#endif

#include <mysql.h>
#include "Terminal.h"
#include "Faq.h"

class DBHandler {

public:
	DBHandler();
	~DBHandler();
	void  getTerminals();
	void  getFaqs();
	void deleteFaq(int id);
	void printFaqs();
private:
	MYSQL *connection;
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int query_state;

	
};