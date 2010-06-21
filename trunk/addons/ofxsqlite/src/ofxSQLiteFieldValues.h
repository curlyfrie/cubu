#ifndef OFXSQLITEFIELDVALUESH
#define OFXSQLITEFIELDVALUESH

#include <vector>
#include <string>
#include <sstream>
#include "lib/sqlite/sqlite3.h"

enum {
 	 OFX_SQLITE_TYPE_INT
	,OFX_SQLITE_TYPE_DOUBLE
	,OFX_SQLITE_TYPE_INT64
	,OFX_SQLITE_TYPE_TEXT
};

struct FieldValuePair {
	std::string field;
	std::string value_string;
	int value_int;
	double value_double;
	long value_int64;
	int index;
	int type;

	void bind(sqlite3_stmt* pStatement) {
		switch(type) {
			case OFX_SQLITE_TYPE_INT:		sqlite3_bind_int(pStatement, index, value_int);break;
			case OFX_SQLITE_TYPE_INT64:		sqlite3_bind_int64(pStatement,index, value_int64); break;
			case OFX_SQLITE_TYPE_TEXT: 		sqlite3_bind_text(pStatement, index, value_string.c_str(), value_string.size(), SQLITE_STATIC); break;
			case OFX_SQLITE_TYPE_DOUBLE:	sqlite3_bind_double(pStatement, index, value_double);break;
			default:break;
		}
	}

	std::string indexString() {
		std::stringstream ss;
		ss << index;
		return ss.str();
	}
};

class ofxSQLiteFieldValues {
	public:
		ofxSQLiteFieldValues();
		void use(std::string sField, int nValue);
		void use(std::string sField, float nValue);
		void use(std::string sField, long nValue);
		void use(std::string sField, double nValue);
		void use(std::string sField, std::string sValue);

		void bind(sqlite3_stmt* pStatement);

		FieldValuePair at(int nIndex);
		void begin();
		FieldValuePair current();
		void next();
		bool hasNext();
		int size();


	private:
		std::vector<FieldValuePair> field_values;
		int nextFieldIndex();
		int _index;
};

#endif
