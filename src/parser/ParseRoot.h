//
// Created by AlanKing on 3/8/2019.
//

#ifndef PARSER_DEV_PARSEROOT_H
#define PARSER_DEV_PARSEROOT_H

#include "../utils/utils.h"
#include "ParseComponent.h"


void parseRoot(shared_ptr<MosdexRoot> m_mosdex) {
    Document &t_document = m_mosdex->getM_document();
    for (Value::ConstMemberIterator itr = t_document.MemberBegin();
         itr != t_document.MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        string memberNode = "/" + memberName;
        spdlog::debug("Type of member {} is {}",
                      memberNode.c_str(), kTypeNames[itr->value.GetType()]);

        ParseComponent().parse(m_mosdex, memberNode);

    }

}


#endif //PARSER_DEV_PARSEROOT_H
