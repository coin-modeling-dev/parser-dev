//
// Created by kingaj on 2/27/19.
//


#include "src/utils/utils.h"
#include "test/test_index.h"

#include "src/parser/DoParse.h"

using namespace rapidjson;


int main() {

    spdlog::set_level(spdlog::level::debug); // Set global log level to debug

    // tests
    testSimpleIndex();

    // parse
    string testFile("../json/test.json");
    DoParse doParse(testFile);

    //doParse.prettyPrint();

    return 0;
}