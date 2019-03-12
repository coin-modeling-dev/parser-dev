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
        Section, Table, TableEntry, Schema, Rows, End
    } State;

    string currentDataMemberInProcess{};

public:
    explicit ParseData(Document &t_document) : m_document{t_document} {}

    void parse(shared_ptr<MosdexRoot> t_mosdex, string t_section, State state);

};

void ParseData::parse(shared_ptr<MosdexRoot> t_mosdex, string t_section, State state = State::Section) {

    // Get pointer to problem node
    Value *problemNode = Pointer(t_section.c_str()).Get(m_document);

    for (Value::ConstMemberIterator itr = problemNode->MemberBegin(); itr != problemNode->MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        string memberNode = t_section + "/" + memberName;
        spdlog::debug("Type of member {} is {}",
                      memberNode.c_str(), kTypeNames[itr->value.GetType()]);

        // Handle different states
        switch (state) {
            case State::Section: {
                spdlog::debug("Parsing Data Section {}", memberName);
                transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);
                if (memberName == "TABLE")
                    parse(t_mosdex, memberNode, State::Table);
                break;
            }
            case State::Table: {
                spdlog::debug("Parsing Table {}", memberName);
                currentDataMemberInProcess = memberName;
                parse(t_mosdex, memberNode, State::TableEntry);
                currentDataMemberInProcess.clear();
                break;
            }
            case State::TableEntry: {
                spdlog::debug("Parsing Table Entry {} for table {}", memberName, currentDataMemberInProcess);
                transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);
                if (memberName == "ROWS") {
                    break;
                }
                if (memberName == "SCHEMA") {
                    parse(t_mosdex, memberNode, State::Schema);
                    break;
                }
            }
            case State::Schema: {
                spdlog::debug("Parsing Table {} schema entry {}", currentDataMemberInProcess, memberName);
            }

        }
    }
}

#endif //PARSER_DEV_PARSEDATA_H
