#ifndef OFXSQLITESELECTH
#define OFXSQLITESELECTH

#include <vector>
#include <string>
#include "lib/sqlite/sqlite3.h"
#include "ofxSQLiteFieldValues.h"
#include "ofxSQLiteWhere.h"

struct Join {
	std::string table;
	std::string condition;
	std::string fields;
};

struct Order {
	std::string field;
	std::string order;
};

class ofxSQLiteSelect {
	public:
		ofxSQLiteSelect(sqlite3* pSQLite);

		// create select query
		ofxSQLiteSelect& select(std::string sFields);
		ofxSQLiteSelect& from(std::string sFrom);
		ofxSQLiteSelect& join(std::string sTable, std::string sOnField, std::string sFields);

		// where clause..
		template<typename T>
		ofxSQLiteSelect& where(std::string sField, T mValue) {
			return where(sField, mValue, wheres.WHERE);
		}
		template<typename T>
		ofxSQLiteSelect& orWhere(std::string sField, T mValue) {
			return where(sField, mValue, wheres.WHERE_OR);
		}
		template<typename T>
		ofxSQLiteSelect& andWhere(std::string sField, T mValue) {
			return where(sField, mValue, wheres.WHERE_AND);
		}
		template<typename T>
		ofxSQLiteSelect& where(std::string sField, T mValue, int nType) {
			wheres.where(sField, mValue, nType);
			return *this;
		}

		ofxSQLiteSelect& limit(int nCount, int nOffset);
		ofxSQLiteSelect& limit(int nCount);

		ofxSQLiteSelect& order(std::string sField);
		ofxSQLiteSelect& order(std::string sField, std::string sOrder);

		// execution
		ofxSQLiteSelect& execute();
		std::string getLiteralQuery();

		// iterating
		ofxSQLiteSelect& begin();
		int next();
		bool hasNext();

		// fetching values.
		std::string getString();
		int getInt();

	private:
		std::vector<Join> joins;
		ofxSQLiteWhere wheres;
		std::vector<Order> orders;

		ofxSQLiteFieldValues where_values;
		std::string fields;
		std::string from_table;
		sqlite3* sqlite;
		sqlite3_stmt* statement;
		int limit_offset;
		int limit_count;
		int col_index;
		int last_result;
};

#endif
