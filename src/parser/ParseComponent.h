//
// Created by kingaj on 3/6/19.
//

#ifndef PARSER_DEV_PARSECOMPONENT_H
#define PARSER_DEV_PARSECOMPONENT_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"
#include "ParseProblem.h"


class ParseComponent {
public:

    ParseComponent() = default;

    void parse(shared_ptr<MosdexRoot> t_mosdex, string t_component) {
        spdlog::debug("Parsing {} section", t_component);

        // transform to upper case
        string section = t_component;
        transform(section.begin(), section.end(), section.begin(), ::toupper);

        if (section == "/PROBLEM") {
            ParseProblem(t_mosdex).parse(t_component);
        }
        if (section == "/DATA") {
            ParseProblem(t_mosdex).parse(t_component);
        }
    }

};

#include "ParseRoot.h"
#include "ParseProblem.h"


#endif //PARSER_DEV_PARSECOMPONENT_H
