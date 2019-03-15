//
// Created by AlanKing on 3/15/2019.
//

#ifndef PARSER_DEV_PARSETABLE_H
#define PARSER_DEV_PARSETABLE_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"
#include "../mosdex/MosdexTable.h"

class ParseTable {
private:
    Document &m_document;

public:

    explicit ParseTable(Document &m_document) : m_document(m_document) {}

    void parse(shared_ptr<MosdexRoot> t_mosdex, const string &t_node) {
        // Get pointer to node
        Value *vNode = Pointer(t_node.c_str()).Get(m_document);

        for (Value::ConstMemberIterator itr = vNode->MemberBegin(); itr != vNode->MemberEnd(); ++itr) {
            string memberName(itr->name.GetString());
            string memberNode = t_node + "/" + memberName;

            spdlog::debug("Type of node {} is {}", memberNode.c_str(), kTypeNames[itr->value.GetType()]);
            parseTable(t_mosdex, memberName, memberNode);
        }
    }

private:

    void parseTable(shared_ptr<MosdexRoot> t_mosdex, const string &tableName, const string &t_node);

    void parseRows(shared_ptr<MosdexRoot> t_mosdex, const string &name, const string &node);

    void parseFields(shared_ptr<MosdexRoot> t_mosdex, const string &name, const string &node);

    void parseTypes(shared_ptr<MosdexRoot> t_mosdex, const string &name, const string &node);
};

void ParseTable::parseTable(shared_ptr<MosdexRoot> t_mosdex, const string &tableName, const string &t_node) {

    spdlog::debug("Parsing Table {}", tableName);

    // store table name and initialize table in Mosdex
    t_mosdex->initializeTable(tableName);

    // Get pointer to node
    Value *vNode = Pointer(t_node.c_str()).Get(m_document);

    for (Value::ConstMemberIterator itr = vNode->MemberBegin(); itr != vNode->MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        string memberNode = t_node + "/" + memberName;

        spdlog::debug("Type of node {} is {}", memberNode.c_str(), kTypeNames[itr->value.GetType()]);

        transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);

        if (memberName == "ROWS") {
            parseRows(t_mosdex, tableName, memberNode);
        }
        if (memberName == "SCHEMA") {
            continue;
        }
        if (memberName == "TYPES") {
            parseTypes(t_mosdex, tableName, memberNode);
        }
        if (memberName == "FIELDS") {
            parseFields(t_mosdex, tableName, memberNode);
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

void ParseTable::parseRows(shared_ptr<MosdexRoot> t_mosdex, const string &name, const string &node) {
    spdlog::debug("Parsing rows for table {}", name);
    // Get Row node
    Value *rowNode = Pointer(node.c_str()).Get(m_document);

    assert(rowNode->IsArray());
}

void ParseTable::parseFields(shared_ptr<MosdexRoot> t_mosdex, const string &name, const string &node) {
    spdlog::debug("Parsing fields for table {}", name);
    // Get Row node
    Value *fieldsNode = Pointer(node.c_str()).Get(m_document);

    assert(fieldsNode->IsArray());
}

void ParseTable::parseTypes(shared_ptr<MosdexRoot> t_mosdex, const string &name, const string &node) {
    spdlog::debug("Parsing types for table {}", name);
    // Get Row node
    Value *typesNode = Pointer(node.c_str()).Get(m_document);

    assert(typesNode->IsArray());
}


#endif //PARSER_DEV_PARSETABLE_H
