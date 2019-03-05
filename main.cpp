//
// Created by kingaj on 2/27/19.
//


#include "src/utils.h"
#include "test/test_index.h"

#include "src/DoParse.h"

using namespace rapidjson;


int main() {

    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");

    if (testSimpleIndex() == 0)
        console->info("Test SimpleIndex succeeded");
    else
        err_logger->critical("Test SimpleIndex failed");

    std::string TEST_JSON_FILE = "../../stoprog-dev/json/v2-newsvendor/newsvendor.json";

    DoParse doParse(TEST_JSON_FILE);
    doParse.prettyPrint();

    return 0;
}