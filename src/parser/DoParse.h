//
// Created by kingaj on 3/5/19.
//

#ifndef PARSER_DEV_DOPARSE_H
#define PARSER_DEV_DOPARSE_H

#include "../utils/utils.h"
#include "../mosdex/MosdexRoot.h"
#include "ParseDocument.h"

class DoParse {

private:
    Document &m_document;
    shared_ptr<MosdexRoot> m_mosdex{};

public:
    explicit DoParse(Document &t_document) : m_document{t_document} {}

    void parse(string t_file) {
        FILE *fp = fopen(t_file.c_str(), "r");
        if (!fp) {
            string message = "Cannot open file " + t_file;
            throw runtime_error(message);
        }
        readDocumentFromFile(fp);
        fclose(fp);

        spdlog::info("Document read, checking number of sections ...");
        spdlog::info("Document has {} sections", m_document.MemberCount());

        // Create Mosdex data structure
        m_mosdex = make_shared<MosdexRoot>(MosdexRoot(t_file));

        // Parse document into Mosdex data structure
        ParseDocument(m_document).parse(m_mosdex);

        spdlog::info("Parsing completed.");
    }

private:

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

