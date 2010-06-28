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
#include "Wellness.h"
#include "Dienstleistung.h"

class DBHandler {

public:
	DBHandler();
	~DBHandler();
	void setAlarm(int terminal_id, int hour, int minute);
	std::string getAlarm(int terminal_id);
	void deleteAlarm(int terminal_id);
	
	void setTemperatur(int terminal_id, float temperatur);
	float getTemperatur(int terminal_id);
	
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
	
	vector<Dienstleistung*>  getDienstleistungen();
	
	vector<Wellness*>  getWellness();
	vector<Wellness*>  getWellness(int typ);
	
	Service * getService(int service_id);
	vector<int> getServiceIDsOfTerminal( int terminal_id);
	Kunde * getKunde(int kunde_id);
	Kunde * getKunde(Terminal * Terminal);
	Speise * getSpeise(int speise_id);
	Wellness * getWell(int wellness_id);
	Dienstleistung * getDienstleistung(int dienstleistung_id);

	void insertTerminalService(int terminal_id, int service_id);
	void insertTerminalService(Terminal * terminal, Service * service);
	void insertTerminalSpeise(int terminal_id, int speise_id, int anzahl, float sumpreis);
	
	vector<Bestellung *>  getBestellungen(Terminal * terminal);
private:
	MYSQL *connection;
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int query_state;

	
};