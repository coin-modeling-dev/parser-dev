//
// Created by kingaj on 3/6/19.
//

#ifndef PARSER_DEV_PARSECOMPONENT_H
#define PARSER_DEV_PARSECOMPONENT_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"


void parseRoot(shared_ptr<MosdexRoot> m_mosdex);
void parseProblem(shared_ptr<MosdexRoot> m_mosdex, string t_component);

class ParseComponent {
protected:
    shared_ptr<MosdexRoot> m_mosdex;
public:
    explicit ParseComponent(shared_ptr<MosdexRoot> t_mosdex) :
            m_mosdex{t_mosdex} {
    }


    void parse(string t_component) {
        spdlog::debug("Parsing {} section", t_component);

        // transform to upper case
        string component = t_component;
        transform(component.begin(), component.end(), component.begin(), ::toupper);

        // apply appropriate parsing implementation
        if (component == "ROOT") {
            parseRoot(m_mosdex);
        }
        if (component == "/PROBLEM") {
            parseProblem(m_mosdex, t_component);
        }
    }

    void parse(Value *value, string t_component) {
        spdlog::debug("Parsing {} section", t_component);
        if (t_component == "ROOT") {
            parseRoot(m_mosdex);
        }
    }
};

#include "ParseRoot.h"
#include "ParseProblem.h"


#endif //PARSER_DEV_PARSECOMPONENT_H
