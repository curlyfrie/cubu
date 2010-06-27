#include "DBHandler.h"
#include <sstream>
#include <string>
#include "time.h"

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
Terminal * DBHandler::getTerminal(int terminal_id)
{

	std::stringstream terminalidstr;
	terminalidstr << terminal_id;
	
	std::string query =  "SELECT * FROM terminal where terminal_id = " + terminalidstr.str();

	query_state = mysql_query(connection,query.c_str());
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	int id;
	std::string zimmer;
	std::string telnr;
	
	
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
				
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0)
				id = atoi(row[i]);
			
			if(i== 1)
				zimmer = row[i];
			
			if(i== 2)
				telnr = row[i];
			
		}
	}

	Terminal * terminal = new Terminal(terminal_id, zimmer, telnr);
	return terminal;
		
	
}



Kunde * DBHandler::getKunde(int kunde_id)
{
	
	std::stringstream kundeidstr;
	kundeidstr << kunde_id;
	
	std::string query =  "SELECT * FROM kunde where kunde_id = " + kundeidstr.str();
	
	query_state = mysql_query(connection,query.c_str());
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	int id;
	std::string vorname;
	std::string nachname;
	std::string adresse;
	std::string kreditkartennummer;
	
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0)
				id = atoi(row[i]);
			
			if(i== 1)
				vorname = row[i];
			
			if(i== 2)
				nachname = row[i];
			if(i== 3)
				adresse = row[i];
			if(i== 4)
				kreditkartennummer = row[i];
			
		}
	}
	
	Kunde * kunde = new Kunde(kunde_id,vorname, nachname, adresse, kreditkartennummer);
	return kunde;
	
	
}


Speise * DBHandler::getSpeise(int speise_id)
{
	
	std::stringstream speiseidstr;
	speiseidstr << speise_id;
	
	std::string query =  "SELECT * FROM speise where speise_id = " + speiseidstr.str();
	
	query_state = mysql_query(connection,query.c_str());
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	int id;
	std::string name;
	std::string beschreibung;
	std::string bild;
	int typ;
	float preis;
	
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0)
				id = atoi(row[i]);
			
			if(i== 1)
				name = row[i];
			
			if(i== 2)
				beschreibung = row[i];
			if(i== 3)
				preis = atof(row[i]);
			if(i== 4)
				bild = row[i];
		  	if(i== 5)
				typ = atoi(row[i]);
			
			
		}
	}
	
	Speise * speise = new Speise(speise_id, name, beschreibung, preis, bild, typ);
	return speise;
	
	
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


void DBHandler::deleteAlarm(int terminal_id)
{
	
	std::string idString;
	std::stringstream out;
	out << terminal_id;
	idString = out.str();
	
	std::string query = "DELETE FROM alarm where terminal_id = " + idString;
	mysql_query(connection,query.c_str());	
}

void DBHandler::insertTerminalSpeise(int terminal_id, int speise_id, int anzahl, float sumpreis)
{
	std::stringstream terminalstr;
	std::stringstream speisestr;
	std::stringstream anzahlstr;
	std::stringstream anzstr;
	std::stringstream sumpreisstr;
	
	terminalstr << terminal_id;
	speisestr << speise_id;
	anzahlstr << anzahl;
	sumpreisstr << sumpreis;

	std::string query = "SELECT anzahl FROM terminalspeise where terminal_id = " + terminalstr.str() + " and speise_id = " + speisestr.str();
	query_state = mysql_query(connection,query.c_str() );
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}

	unsigned int num_fields;

	result = mysql_store_result(connection);
	
	num_fields = mysql_num_rows(result);

	int anz;
	
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		
		for(int i = 0; i < num_fields; i++)
		{
			if(i== 0){
				anz = atoi(row[i]);
			}
		}
	}
	
	mysql_free_result(result);

	if(num_fields > 0){
		cout << "anz " << anz << endl;
		anz++;
		cout << "anz " << anz << endl;
		anzstr << anz;

		std::string query1 = "update terminalspeise set anzahl = " + anzstr.str() + ", datum = now() where terminal_id = " + terminalstr.str() + " and speise_id = " + speisestr.str();
	
		query_state = mysql_query(connection,query1.c_str());	

		if (query_state !=0) {
			cout << mysql_error(connection) << endl;
		}

	}
	else
	{
		std::string query1 = "insert into terminalspeise (terminal_id, speise_id, datum, anzahl, sumpreis) values ('" + terminalstr.str() + "',' " + speisestr.str() + "' , now(), '"+ anzahlstr.str()+ "', '"+sumpreisstr.str()+"')";
		query_state = mysql_query(connection,query1.c_str());
		if (query_state !=0) {
			cout << mysql_error(connection) << endl;
		}
	}

}
void DBHandler::insertTerminalService(Terminal* terminal, Service * service)
{
	int terminal_id = terminal->getId();
	int service_id = service->getId();
	std::stringstream terminalstr;
	std::stringstream servicestr;
	
	terminalstr << terminal_id;
	servicestr << service_id;

	std::string query = "insert into terminalservice(terminal_id, service_id) values ('" + terminalstr.str() + "',' " + servicestr.str() + "' , now(), ')";
	mysql_query(connection,query.c_str());
}
vector<Bestellung *> DBHandler::getBestellungen(Terminal * terminal)
{
	int terminal_id = terminal->getId();
	std::stringstream terminalstr;
	terminalstr << terminal_id;

	vector<Bestellung *> bestellungen;
	std::string query = "SELECT s.speise_id, s.name, s.beschreibung, s.preis, s.bild, s.typ, sum(ts.anzahl) as anzahl, ts.sumpreis FROM terminalspeise ts, speise s WHERE ts.terminal_id = " + terminalstr.str()  + " GROUP BY s.speise_id, ts.terminal_id";
	cout << query << endl;
	query_state = mysql_query(connection, query.c_str());
	
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	
	int speise_id;
	std::string name;
	std::string beschreibung;
	std::string bild;
	int typ;
	int anzahl;
	float preis;
	float sumpreis;
	
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		
		for( i = 0; i < num_fields; i++)
		{
			
		if(i==0)
			speise_id = atoi(row[i]);
			if(i==1)
				name = row[i];
			if(i==2)
				beschreibung = row[i]; 
			if(i==3)
				preis = atof(row[i]);
			if(i==4)
				bild = row[i];
			if(i==5)
				typ = atoi(row[i]);
			if(i==6)
				anzahl = atoi(row[i]); 
			if(i==7)
				sumpreis = atof(row[i]);
			
		}
		Speise * speise = new Speise(speise_id, name, beschreibung, preis, bild, typ);
	bestellungen.push_back(new Bestellung(speise_id,anzahl, sumpreis ) );
	}
	
	mysql_free_result(result);

	return bestellungen;	
	
}


Kunde * DBHandler::getKunde(Terminal * terminal)
{
	int terminal_id = terminal->getId();
	std::stringstream terminalstr;
	terminalstr << terminal_id;
	
	Kunde * kunde;
	std::string query = "SELECT t.kunde_id FROM terminalkunde t NATURAL JOIN kunde WHERE t.terminal_id = " + terminalstr.str();
	query_state = mysql_query(connection, query.c_str());
	
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	
	int kunde_id;
	
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0){
				kunde_id = atoi(row[i]);
			}
		}
	}
	
	kunde = getKunde(kunde_id);
	
	mysql_free_result(result);
	return kunde;	
	
}


Service * DBHandler::getService(int service_id)
{
	
	std::stringstream serviceidstr;
	serviceidstr << service_id;
	
	std::string query =  "SELECT * FROM service where service_id = " + serviceidstr.str();
	
	query_state = mysql_query(connection,query.c_str());
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	int id;
	std::string name;
	std::string beschreibung;
	
	
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0)
				id = atoi(row[i]);
			
			if(i== 1)
				name = row[i];
			
			if(i== 2)
				beschreibung = row[i];
			
			
		}
	}
	
	Service  * service = new Service(service_id, name, beschreibung);
	return service;
	
}


void DBHandler::setAlarm(int terminal_id, int hour, int minute)
{
	cout << "IMSET" << endl;

	
	std::stringstream hstr;
	hstr << hour;
	std::stringstream mstr;
	mstr << minute;

	query_state = mysql_query(connection, "SELECT * FROM alarm WHERE terminal_id = 0");
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_rows(result);
	
	mysql_free_result(result);

	if(num_fields > 0){
	
		cout << "=========>>>>00000===========" << endl;
		std::string query1 = "update alarm set time = '2010-06-24 "+hstr.str() +":"+ mstr.str() +":00' where terminal_id = 0";
		mysql_query(connection,query1.c_str());	

	}
	else
	{
		std::string query1 = "insert into alarm (terminal_id, time, active) values (0,'2010-06-24 "+hstr.str() +":"+ mstr.str() +":00', true  )";
		mysql_query(connection,query1.c_str());	
	}

}

float DBHandler::getTemperatur(int terminal_id){
	//returnvalue
	float temperatur;
	
	std::stringstream terminalstream;
	terminalstream << terminal_id;
	
	std:string query = "SELECT * FROM temperatur WHERE terminal_id = " + terminalstream.str();

	//ask mighty database
	query_state = mysql_query(connection,query.c_str() );
	
	temperatur = 20;
	
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	
	result = mysql_store_result(connection);
	
	while ( ( row = mysql_fetch_row(result)) ) {
		temperatur = atof(row[1]);
	}
	
	return temperatur;	
}


void DBHandler::setTemperatur(int terminal_id,float temperatur){
	//returnvalue
	std::ostringstream temp;
	temp << temperatur;

	std::stringstream terminalstream;
	terminalstream << terminal_id;
	
	std:string query = "SELECT * FROM temperatur WHERE terminal_id = " + terminalstream.str();
	query_state = mysql_query(connection, query.c_str());
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	unsigned int num_fields;
	unsigned int i;
	result = mysql_store_result(connection);
	num_fields = mysql_num_rows(result);
	mysql_free_result(result);

	cout <<temp.str()<<endl;
	cout<<temperatur<<endl;
	
	if(num_fields > 0){
		 query = "UPDATE temperatur SET temperatur="+temp.str()+" WHERE terminal_id = " + terminalstream.str();
		query_state = mysql_query(connection, query.c_str());
	} else {
		query = "INSERT INTO temperatur (temperatur) values ("+temp.str()+") WHERE terminal_id = " + terminalstream.str();
		query_state = mysql_query(connection, query.c_str());
	}
	

	

}



std::string DBHandler::getAlarm(int terminal_id){
//get the time of alarm in this format: hh:mm
	
	//returnvalue
	std::string alarmstring;
	
	std::stringstream terminalstream;
	terminalstream << terminal_id;
	
	//complete query
	//std:string query = "SELECT * FROM alarm WHERE terminal_id =" + terminalstream.str();
	std:string query = "SELECT time(time) FROM alarm WHERE terminal_id = " + terminalstream.str();

	
	//ask mighty database
	query_state = mysql_query(connection,query.c_str() );
	
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	
	if(num_fields == 0){
		alarmstring == "";
		return alarmstring;
	}
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		// note: result is only 1 row IN THIS CASE
		alarmstring = row[0];
		alarmstring.erase(5);
	}
	mysql_free_result(result);
	return alarmstring;	

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
				id = atoi(row[i]);
			
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
		int speise_id;
		int typ;
		std::string bild;
		std::string name;
		std::string beschreibung;
		float preis;
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0){
				speise_id = atoi(row[i]);
			}
			if(i== 1)
				name = row[i];
			
			if(i== 2)
				beschreibung = row[i];
			if(i == 3)
				preis = atof(row[i]);
			if(i== 4)
				bild = row[i];
			if(i== 5)
				typ = atoi(row[i]);
			
		}
		
		speisen.push_back(new Speise(speise_id, name,beschreibung, preis, bild, typ));
		
	}
	
	mysql_free_result(result);
	return speisen;	
}

vector<Speise*> DBHandler::getSpeisen(int typ) {
	std::stringstream typstr;
	typstr << typ;
	
	std::string query =  "SELECT * FROM speise where typ =" + typstr.str();
	cout << "getsPeisen " << query << endl;
	query_state = mysql_query(connection, query.c_str());
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
		int speise_id;
		std::string name;
		std::string beschreibung;
		std::string bild;
		float preis;
		
		for( i = 0; i < num_fields; i++)
		{
			if(i== 0){
				speise_id = atoi(row[i]);
			}
			if(i== 1)
				name = row[i];
			
			if(i== 2)
				beschreibung = row[i];
			if(i == 3)
				preis = atof(row[i]);
			
			if(i== 4)
				bild = row[i];
			if(i== 5)
				typ = atoi(row[i]);
			
		}
		cout << speise_id << endl;
		speisen.push_back(new Speise(speise_id, name,beschreibung, preis, bild, typ));
		
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
				id = atoi(row[i]);
			
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
				id = atoi(row[i]);
			
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


int DBHandler::getKundenId(int terminalId) {
	cout << "+++ getting kunden data";
	query_state = mysql_query(connection, "SELECT kunde_id FROM terminalkunde where terminal_id = 1");
	if (query_state !=0) {
		cout << mysql_error(connection) << endl;
	}
	int kunden_id;
	unsigned int num_fields;
	unsigned int i;
	
	result = mysql_store_result(connection);
	
	num_fields = mysql_num_fields(result);
	while ( ( row = mysql_fetch_row(result)) ) {
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		for( i = 0; i < num_fields; i++)
		{
			kunden_id = atoi(row[i]);
			cout << num_fields << " " <<row[i]<<endl;
		}
		printf("\n");
		
	}
	mysql_free_result(result);
	
	
	return kunden_id;
	
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
	//xTerminal * t = new Terminal(2,'bla','1234');
	
	
}


