//
// Created by AlanKing on 3/8/2019.
//

#ifndef PARSER_DEV_PARSEROOT_H
#define PARSER_DEV_PARSEROOT_H

#include "../utils/utils.h"
#include "ParseComponent.h"

class ParseRoot {
private:
    Document &m_document;
public:
    explicit ParseRoot(Document &t_document) : m_document{t_document} {}

    void parse(shared_ptr<MosdexRoot> m_mosdex) {
        for (Value::ConstMemberIterator itr = m_document.MemberBegin();
             itr != m_document.MemberEnd(); ++itr) {
            string memberName(itr->name.GetString());
            string memberNode = "/" + memberName;
            spdlog::debug("Type of member {} is {}",
                          memberNode.c_str(), kTypeNames[itr->value.GetType()]);

            ParseComponent(m_document).parse(m_mosdex, memberNode);

        }

    }
};


#endif //PARSER_DEV_PARSEROOT_H
