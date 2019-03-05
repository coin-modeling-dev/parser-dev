//
// Created by kingaj on 3/5/19.
//

#ifndef PARSER_DEV_DOPARSE_H
#define PARSER_DEV_DOPARSE_H

#include "utils.h"

using namespace rapidjson;

class DoParse {

private:
    Document _d;

public:
    explicit DoParse(const std::string &json_file) {
        auto logger = spdlog::get("console");

        try {
            FILE *fp = fopen(json_file.c_str(), "r");
            if (!fp) {
                logger->critical("File {} not found.", json_file.c_str());
                throw std::exception();
            }
            char readBuffer[65536];
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));

            _d.ParseStream(is);
            fclose(fp);
        }
        catch (std::exception &e) {
            throw e;
        }

        logger->info("Parsed file {}", json_file.c_str());
    }

    void prettyPrint() {

        StringBuffer buffer;
        buffer.Clear();

        PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        _d.Accept(writer);

        std::cout << buffer.GetString() << std::endl;

    }


};


#endif //PARSER_DEV_DOPARSE_H

