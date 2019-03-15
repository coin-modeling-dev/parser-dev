//
// Created by AlanKing on 3/12/2019.
//

#ifndef PARSER_DEV_PARSEDATA_H
#define PARSER_DEV_PARSEDATA_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"
#include "ParseTable.h"

class ParseData {

private:
    Document &m_document;

public:
    explicit ParseData(Document &t_document) : m_document{t_document} {}

    void parse(shared_ptr<MosdexRoot> t_mosdex, const string &t_node) {
        // Get pointer to node
        Value *vNode = Pointer(t_node.c_str()).Get(m_document);

        for (Value::ConstMemberIterator itr = vNode->MemberBegin(); itr != vNode->MemberEnd(); ++itr) {
            string memberName(itr->name.GetString());
            string memberNode = t_node + "/" + memberName;

            spdlog::debug("Type of node {} is {}", memberNode.c_str(), kTypeNames[itr->value.GetType()]);

            transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);

            if (memberName == "TABLE") {
                ParseTable(m_document).parse(t_mosdex, t_node);
            }

        }
    }


};


#endif //PARSER_DEV_PARSEDATA_H
