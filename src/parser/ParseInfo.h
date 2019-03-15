//
// Created by AlanKing on 3/11/2019.
//

#ifndef PARSER_DEV_PARSEINFO_H
#define PARSER_DEV_PARSEINFO_H

#include "../utils/utils.h"


class ParseInfo {
private:
    Document &m_document;
public:
    explicit ParseInfo(Document &t_document) : m_document{t_document} {
        spdlog::debug("Entering ParseInfo");
    }

    void parse(shared_ptr<MosdexRoot> t_mosdex, string t_component);
};

void ParseInfo::parse(shared_ptr<MosdexRoot> t_mosdex, string t_component) {
    // Get pointer to problem node
    Value *problemNode = Pointer(t_component.c_str()).Get(m_document);

    for (Value::ConstMemberIterator itr = problemNode->MemberBegin(); itr != problemNode->MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        string memberNode = t_component + "/" + memberName;

        // Handle members that are strings
        if (kTypeNames[itr->value.GetType()] == "String" ) {
            t_mosdex->setInfoValue(memberName, itr->value.GetString());
            if (memberName == "Type") {
                t_mosdex->setM_problemType(itr->value.GetString());
            }
        }

    }

}

#endif //PARSER_DEV_PARSEINFO_H
