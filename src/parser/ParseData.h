//
// Created by AlanKing on 3/12/2019.
//

#ifndef PARSER_DEV_PARSEDATA_H
#define PARSER_DEV_PARSEDATA_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"

class ParseData {

private:
    Document &m_document;
    typedef enum {
        Section, Table, TableComponent, Schema, Rows, End
    } State;

    State m_state{State::Section};
    string currentDataMemberInProcess{};

public:
    explicit ParseData(Document &t_document) : m_document{t_document} {}

    void parse(shared_ptr<MosdexRoot> t_mosdex, const string &t_node);
    void parseTable(shared_ptr<MosdexRoot> t_mosdex, string name, string node);

};

void ParseData::parse(shared_ptr<MosdexRoot> t_mosdex, const string &t_node) {

    // Get pointer to node
    Value *vNode = Pointer(t_node.c_str()).Get(m_document);

    for (Value::ConstMemberIterator itr = vNode->MemberBegin(); itr != vNode->MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        string memberNode = t_node + "/" + memberName;

        spdlog::debug("Type of node {} is {}", memberNode.c_str(), kTypeNames[itr->value.GetType()]);

        // State machine
        switch (m_state) {
            case State::Section: {
                spdlog::debug("Parsing Data Section {}", memberName);

                // Get the type of the data section
                transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);

                // Process the section by type
                if (memberName == "TABLE") {
                    m_state = State::Table;
                    parse(t_mosdex, memberNode);
                }

                // data section is parsed, so reset state to section and continue
                m_state = State::Section;
                break;
            }
            case State::Table: {
                spdlog::debug("Parsing Table {}", memberName);

                // store table name and initialize table in Mosdex
                currentDataMemberInProcess = memberName;
                t_mosdex->initializeTable(currentDataMemberInProcess);

                // parse table components
                m_state = State::TableComponent;
                parse(t_mosdex, memberNode);

                // components are parsed, so create Table
                t_mosdex->createTable(currentDataMemberInProcess);
                currentDataMemberInProcess.clear();

                // Table instance completed, resume parsing table section
                m_state = State::Table;
                break;
            }
            case State::TableComponent: {
                spdlog::debug("Parsing Table Component {} for table {}", memberName, currentDataMemberInProcess);
                transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);
                if (memberName == "ROWS") {
                    parseRows()
                }
                if (memberName == "SCHEMA") {
                    parse(t_mosdex, memberNode, State::Schema);
                }
                break;
            }
            case State::Schema: {
                spdlog::debug("Parsing Table {} schema entry {}", currentDataMemberInProcess, memberName);
                transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);
                if (memberName == "FIELDS") {
                    parseFields()
                }
                if (memberName == "TYPES") {
                    parseTypes()
                }
                break;
            }
                string sql = "CREATE TABLE " + currentDataMemberInProcess + " (";
                \
                              "ID INT PRIMARY KEY     NOT NULL," \
                              "NAME           TEXT    NOT NULL," \
                              "AGE            INT     NOT NULL," \
                              "ADDRESS        CHAR(50)," \
                              "SALARY         REAL );";

            }

        }
    }
}

#endif //PARSER_DEV_PARSEDATA_H
