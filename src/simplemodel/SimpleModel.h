//
// Created by kingaj on 3/5/19.
//

#ifndef PARSER_DEV_SIMPLEMODEL_H
#define PARSER_DEV_SIMPLEMODEL_H

#include <map>
#include "SimpleIndex.h"

class SimpleModel {

private:
    std::map<std::string, p_SMIndexed> _index{};

public:
    SimpleModel() = default;


};


#endif //PARSER_DEV_SIMPLEMODEL_H
