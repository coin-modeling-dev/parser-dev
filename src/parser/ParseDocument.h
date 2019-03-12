//
// Created by AlanKing on 3/8/2019.
//

#ifndef PARSER_DEV_PARSEROOT_H
#define PARSER_DEV_PARSEROOT_H

#include "../utils/utils.h"
#include "ParseSection.h"

class ParseDocument {
private:
    Document &m_document;
public:
    explicit ParseDocument(Document &t_document) : m_document{t_document} {
        spdlog::debug("Entering ParseDocument");
    }

    void parse(shared_ptr<MosdexRoot> m_mosdex) {
        for (Value::ConstMemberIterator itr = m_document.MemberBegin();
             itr != m_document.MemberEnd(); ++itr) {
            string memberName(itr->name.GetString());
            string memberNode = "/" + memberName;
            spdlog::debug("Type of member {} is {}",
                          memberNode.c_str(), kTypeNames[itr->value.GetType()]);

            ParseSection(m_document).parse(m_mosdex, memberNode);

        }

    }
};


#endif //PARSER_DEV_PARSEROOT_H
