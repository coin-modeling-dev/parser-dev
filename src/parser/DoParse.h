//
// Created by kingaj on 3/5/19.
//

#ifndef PARSER_DEV_DOPARSE_H
#define PARSER_DEV_DOPARSE_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"
#include "ParseComponent.h"

class DoParse {

public:
    explicit DoParse(string t_file) {
        FILE *fp = fopen(t_file.c_str(), "r");
        if (!fp) {
            string message = "Cannot open file " + t_file;
            throw runtime_error(message);
        }
        readDocumentFromFile(fp);
        fclose(fp);

        m_mosdex = make_shared<MosdexRoot>(MosdexRoot(t_file, m_document));

        parseRoot(m_mosdex);

        spdlog::info("Parsing completed.");
    }

private:
    Document m_document{};
    shared_ptr<MosdexRoot> m_mosdex{};

    void readDocumentFromFile(FILE *t_fp) {
        try {
            if (!t_fp) {
                throw std::runtime_error("Bad file pointer.");
            }
            char readBuffer[65536];
            FileReadStream is(t_fp, readBuffer, sizeof(readBuffer));

            m_document.ParseStream(is);
        }
        catch (std::exception &e) {
            throw e;
        }

        spdlog::info("Parsed file");
    }

public:
    void prettyPrint() {

        StringBuffer buffer;
        buffer.Clear();

        PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        m_document.Accept(writer);

        std::cout << buffer.GetString() << std::endl;

    }


};


#endif //PARSER_DEV_DOPARSE_H

