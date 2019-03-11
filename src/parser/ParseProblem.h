//
// Created by AlanKing on 3/11/2019.
//

#ifndef PARSER_DEV_PARSEPROBLEM_H
#define PARSER_DEV_PARSEPROBLEM_H

#include "../utils/utils.h"
#include "ParseComponent.h"

void parseProblem(shared_ptr<MosdexRoot> m_mosdex, string t_component) {
    Value *value = Pointer(t_component.c_str()).Get(m_mosdex->getM_document());
    for (Value::ConstMemberIterator itr = value->MemberBegin();
         itr != value->MemberEnd(); ++itr) {
        string memberName(itr->name.GetString());
        string memberNode = t_component + "/" + memberName;
        spdlog::debug("Type of member {} is {}",
                      memberNode.c_str(), kTypeNames[itr->value.GetType()]);

        Value *value1 = Pointer(memberNode.c_str()).Get(m_mosdex->getM_document());
        ParseComponent(m_mosdex).parse(value1, memberNode);

    }

}

#endif //PARSER_DEV_PARSEPROBLEM_H
