//
// Created by kingaj on 2/27/19.
//


#include "src/utils/utils.h"
#include "test/test_index.h"

#include "src/parser/DoParse.h"

using namespace rapidjson;


int main() {

    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug

    // tests
    testSimpleIndex();

    // parse
    FILE *fp = fopen("../json/test.json", "r");
    DoParse doParse(fp);
    fclose(fp);

    //doParse.prettyPrint();

    return 0;
}