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
#include "Kunde.h"
#include "Speise.h"
#include "Service.h"

class DBHandler {

public:
	DBHandler();
	~DBHandler();
	void setAlarm(int terminal_id, int hour, int minute);
	void  getTerminals();
	vector<Faq*> getFaqs();
	vector<Speise*> getSpeisen();
	vector<Service*> getService();
	map <int, Kunde*> getKunden2();

	void deleteFaq(int id);
	void printFaqs();
private:
	MYSQL *connection;
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int query_state;

	
};