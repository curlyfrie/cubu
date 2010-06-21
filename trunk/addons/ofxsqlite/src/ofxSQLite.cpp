#include "ofxSQLite.h"
#include "ofxSQLiteInsert.h"
#include "ofxSQLiteUpdate.h"
#include "ofxSQLiteDelete.h"
#include "ofxSQLiteSelect.h"

ofxSQLite::ofxSQLite(std::string sDB):db_name(sDB) {
	db_file = ofToDataPath(db_name);
	if (SQLITE_OK != sqlite3_open(db_file.c_str(), &db)) {
		cout << sqlite3_errmsg(db);
		exit(1);
	}
}

int ofxSQLite::simpleQuery(const char* pSQL) {
	sqlite3_stmt* statement;
	if (SQLITE_OK != sqlite3_prepare_v2(db, pSQL,-1, &statement, 0)) {
		return sqlite3_errcode(db);
	}
	while(SQLITE_ROW == sqlite3_step(statement));
	return sqlite3_finalize(statement);
}

ofxSQLiteInsert ofxSQLite::insert(std::string sTable) {
	return ofxSQLiteInsert(db, sTable);
}
ofxSQLiteUpdate ofxSQLite::update(std::string sTable) {
	return ofxSQLiteUpdate(db, sTable);
}

ofxSQLiteDelete ofxSQLite::remove(std::string sTable) {
	return ofxSQLiteDelete(db, sTable);
}

ofxSQLiteSelect	ofxSQLite::select(std::string sFields) {
	ofxSQLiteSelect select = ofxSQLiteSelect(db);
	select.select(sFields);
	return select;
}

const char* ofxSQLite::getError() {
	return sqlite3_errmsg(db);
}

int ofxSQLite::lastInsertID() {
	return sqlite3_last_insert_rowid(db);
}
