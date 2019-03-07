//
// Created by kingaj on 3/5/19.
//

#ifndef PARSER_DEV_DOPARSE_H
#define PARSER_DEV_DOPARSE_H

#include "../utils/utils.h"
#include "ParseFactory.h"

using namespace rapidjson;
using namespace spdlog;
using namespace std;

class DoParse {

private:
    Document m_document{};

public:
    explicit DoParse(FILE *t_fp) {
        readDocumentFromFile(t_fp);
        parseDocument();
    }

private:
    void parseDocument() {
        spdlog::debug("Entering parseDocument");
        if (!m_document.IsObject()) {
            throw runtime_error("Bad JSON document");
        }

        ParseFactory parseFactory;

        for (Value::ConstMemberIterator itr = m_document.MemberBegin();
             itr != m_document.MemberEnd(); ++itr) {
            string memberName(itr->name.GetString());
            transform(memberName.begin(), memberName.end(), memberName.begin(), ::toupper);
            spdlog::debug("Type of member {} is {}",
                          memberName.c_str(), kTypeNames[itr->value.GetType()]);


        }
    }

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
