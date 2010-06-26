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
#include "Bestellung.h"

class DBHandler {

public:
	DBHandler();
	~DBHandler();
	void setAlarm(int terminal_id, int hour, int minute);
	std::string getAlarm(int terminal_id);
	void  getTerminals();
	Terminal * getTerminal(int terminal_id);
	vector<Faq*> getFaqs();
	vector<Speise*> getSpeisen();
	vector<Speise*> getSpeisen(int typ);
	vector<Service*> getService();
	map <int, Kunde*> getKunden2();
	int getKundenId(int terminal_id);
	void deleteFaq(int id);
	void printFaqs();
	
	Service * getService(int service_id);
	Kunde * getKunde(int kunde_id);
	Kunde * getKunde(Terminal * Terminal);
	Speise * getSpeise(int speise_id);
	void insertTerminalService(Terminal * terminal, Service * service);
	void insertTerminalSpeise(Terminal* terminal, Speise* speise, int anzahl, float sumpreis);
	
	vector<Bestellung *>  getBestellungen(Terminal * terminal);
private:
	MYSQL *connection;
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int query_state;

	
};