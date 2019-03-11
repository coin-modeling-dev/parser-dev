//
// Created by AlanKing on 3/8/2019.
//

#ifndef PARSER_DEV_MOSDEXROOT_H
#define PARSER_DEV_MOSDEXROOT_H

#include "../utils/utils.h"

#include <map>

class MosdexRoot {
private:
    string jsonFileName{};
    Document &m_document;

    map<string, string> m_info{};
    string m_problemType{};
public:
    const string &getM_problemType() const {
        return m_problemType;
    }

    void setM_problemType(const string &m_problemType) {
        spdlog::debug("MosdexRoot: Setting problem type to {}", m_problemType);
        MosdexRoot::m_problemType = m_problemType;
    }


public:
    void setInfoValue(string t_key, string t_value){
        spdlog::debug("MosdexRoot: Setting info -- {} is {}", t_key, t_value);
        m_info.insert(make_pair(t_key, t_value));
    }

    const string &getJsonFileName() const {
        return jsonFileName;
    }

    Document &getM_document() const {
        return m_document;
    }

    MosdexRoot(string t_file, Document &t_document): jsonFileName{t_file}, m_document{t_document} {

    }



};


#endif //PARSER_DEV_MOSDEXROOT_H
