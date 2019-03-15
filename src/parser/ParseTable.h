//
// Created by AlanKing on 3/15/2019.
//

#ifndef PARSER_DEV_PARSETABLE_H
#define PARSER_DEV_PARSETABLE_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"
#include "../mosdex/MosdexTable.h"

class ParseTable {

public:

    explicit ParseTable(Document &m_document) : m_document(m_document) {
        spdlog::debug("Entering ParseTable");
    }

    void parse(shared_ptr<MosdexRoot> t_mosdex, const string &t_node) {
        // Parse all the tables

        Value *vNode = Pointer(t_node.c_str()).Get(m_document);

        for (Value::ConstMemberIterator itr = vNode->MemberBegin(); itr != vNode->MemberEnd(); ++itr) {
            string memberName(itr->name.GetString());
            string memberNode = t_node + "/" + memberName;
            parseTable(t_mosdex, memberName, memberNode);
        }
    }

private:

    Document &m_document;

    void parseTable(shared_ptr<MosdexRoot> t_mosdex, const string &tableName, const string &t_node);

    void parseRows(shared_ptr<MosdexTable> t_mosdex, const string &node);

    void parseSchema(shared_ptr<MosdexTable> t_mosdex, const string &node);

};

void ParseTable::parseTable(shared_ptr<MosdexRoot> t_mosdex, const string &tableName, const string &t_node) {

    spdlog::debug("Parsing Table {}", tableName);

    // store table name and initialize table in Mosdex
    auto mosdexTable = t_mosdex->initializeTable(tableName);

    // Loop over table object and execute code for each section
    Value *vNode = Pointer(t_node.c_str()).Get(m_document);
    for (Value::ConstMemberIterator itr = vNode->MemberBegin(); itr != vNode->MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        string memberNode = t_node + "/" + memberName;
        transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);

        if (memberName == "ROWS") {
            parseRows(mosdexTable, memberNode);
        }
        if (memberName == "SCHEMA") {
            parseSchema(mosdexTable, memberNode);
        }
    }
}

/*
    string sql = "CREATE TABLE " + currentDataMemberInProcess + " (";
    \
                  "ID INT PRIMARY KEY     NOT NULL," \
                  "NAME           TEXT    NOT NULL," \
                  "AGE            INT     NOT NULL," \
                  "ADDRESS        CHAR(50)," \
                  "SALARY         REAL );";
*/

void ParseTable::parseRows(shared_ptr<MosdexTable> t_mosdex, const string &node) {
    spdlog::debug("Parsing rows for table {}", t_mosdex->getM_tableName());
    Value *rowNode = Pointer(node.c_str()).Get(m_document);

    assert(rowNode->IsArray());
}

void ParseTable::parseSchema(shared_ptr<MosdexTable> t_mosdex, const string &node) {
    spdlog::debug("Parsing Schema for table {}", t_mosdex->getM_tableName());

    Value *schemaNode = Pointer(node.c_str()).Get(m_document);
    for (Value::ConstMemberIterator itr = schemaNode->MemberBegin(); itr != schemaNode->MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        string memberNode = node + "/" + memberName;
        transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);

        if (memberName == "TYPES") {
            spdlog::debug("Parsing TYPES for table {}", t_mosdex->getM_tableName());
        }
        if (memberName == "FIELDS") {
            spdlog::debug("Parsing FIELDS for table {}", t_mosdex->getM_tableName());
        }
    }

}

#endif //PARSER_DEV_PARSETABLE_H
