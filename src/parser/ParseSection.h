//
// Created by kingaj on 3/6/19.
//

#ifndef PARSER_DEV_PARSESECTION_H
#define PARSER_DEV_PARSESECTION_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"
#include "ParseInfo.h"
#include "ParseData.h"


class ParseSection {
private:
    Document &m_document;

public:

    explicit ParseSection(Document &t_document) : m_document{t_document} {
        spdlog::debug("Entering ParseSection");
    }

    void parse(shared_ptr<MosdexRoot> t_mosdex, string t_section) {
        // transform to upper case
        string section = t_section;
        transform(section.begin(), section.end(), section.begin(), ::toupper);

        if (section == "/PROBLEM") {
            ParseInfo(m_document).parse(t_mosdex, t_section);
        }
        if (section == "/DATA") {
            ParseData(m_document).parse(t_mosdex, t_section);
        }
    }

};


#endif //PARSER_DEV_PARSESECTION_H
