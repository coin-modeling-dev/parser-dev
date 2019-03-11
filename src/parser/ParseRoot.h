//
// Created by AlanKing on 3/8/2019.
//

#ifndef PARSER_DEV_PARSEROOT_H
#define PARSER_DEV_PARSEROOT_H

#include "../utils/utils.h"
#include "ParseComponent.h"

using namespace rapidjson;


void parseRoot(Document &m_document, shared_ptr<MosdexRoot> m_mosdex, string t_component) {
    for (Value::ConstMemberIterator itr = m_document.MemberBegin();
         itr != m_document.MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);
        spdlog::debug("Type of member {} is {}",
                      memberName.c_str(), kTypeNames[itr->value.GetType()]);

    }

}


#endif //PARSER_DEV_PARSEROOT_H
