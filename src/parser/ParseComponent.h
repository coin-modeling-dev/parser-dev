//
// Created by kingaj on 3/6/19.
//

#ifndef PARSER_DEV_PARSECOMPONENT_H
#define PARSER_DEV_PARSECOMPONENT_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"

#include "ParseRoot.h"

using namespace rapidjson;
using namespace spdlog;
using namespace std;

class ParseComponent {
protected:
    Document &m_document;
    shared_ptr<MosdexRoot> m_mosdex;
public:
    ParseComponent(Document &t_document, shared_ptr<MosdexRoot> t_mosdex) :
            m_document{t_document}, m_mosdex{t_mosdex} {
        if (!t_document.IsObject()) {
            throw runtime_error("Bad JSON document");
        }
    }

    void parse(string t_component) {
        spdlog::debug("Parsing {} section", t_component);
        if (t_component == "ROOT") {
           parseRoot(m_document, m_mosdex, t_component);
        }
    }

};


#endif //PARSER_DEV_PARSECOMPONENT_H
