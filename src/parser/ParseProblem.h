//
// Created by AlanKing on 3/11/2019.
//

#ifndef PARSER_DEV_PARSEPROBLEM_H
#define PARSER_DEV_PARSEPROBLEM_H

#include "../utils/utils.h"


class ParseProblem {
private:
    Document &m_document;
public:
    explicit ParseProblem(Document &t_document) : m_document{t_document} {}

    void parse(shared_ptr<MosdexRoot> t_mosdex, string t_component);
};

void ParseProblem::parse(shared_ptr<MosdexRoot> t_mosdex, string t_component) {
    // Get pointer to problem node
    Value *problemNode = Pointer(t_component.c_str()).Get(m_document);

    for (Value::ConstMemberIterator itr = problemNode->MemberBegin(); itr != problemNode->MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        string memberNode = t_component + "/" + memberName;
        spdlog::debug("Type of member {} is {}",
                      memberNode.c_str(), kTypeNames[itr->value.GetType()]);

        // Handle different members
        if (kTypeNames[itr->value.GetType()] == "String" ) {
            t_mosdex->setInfoValue(memberName, itr->value.GetString());
            if (memberName == "Type") {
                t_mosdex->setM_problemType(itr->value.GetString());
            }
        }

    }

}

#endif //PARSER_DEV_PARSEPROBLEM_H
