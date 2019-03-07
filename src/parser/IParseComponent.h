//
// Created by kingaj on 3/6/19.
//

#ifndef PARSER_DEV_IPARSECOMPONENT_H
#define PARSER_DEV_IPARSECOMPONENT_H

#include "../utils/utils.h"

using namespace rapidjson;
using namespace spdlog;
using namespace std;

class IParseComponent {
private:
    Document m_document;
    shared_ptr<logger> m_logger;

public:
    IParseComponent(Document t_document, logger t_logger = get("console")) = default;

    virtual void parse() = 0;
};

class ParseProblem : IParseComponent {
public:
    void parse(Document t_document) {


    }
};


#endif //PARSER_DEV_IPARSECOMPONENT_H
