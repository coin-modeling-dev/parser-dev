//
// Created by AlanKing on 3/8/2019.
//

#ifndef PARSER_DEV_MOSDEXROOT_H
#define PARSER_DEV_MOSDEXROOT_H

#include "../utils/utils.h"
#include "MosdexTable.h"


class MosdexRoot {
private:
    string jsonFileName{};

    map<string, string> m_info{};
    string m_problemType{};

    map <string, string> m_data{};
    map<string, shared_ptr<MosdexTable>> m_table{};

public:

    shared_ptr<MosdexTable> initializeTable(string t_name) {
        spdlog::info("Initializing table {}", t_name);
        return make_shared<MosdexTable>(MosdexTable(t_name));
    }

    void createTable(string t_name){
        spdlog::info("Creating table {}", t_name);
    }

    const string &getM_problemType() const {
        return m_problemType;
    }

    void setM_problemType(const string &m_problemType) {
        spdlog::info("MosdexRoot: Setting problem type to {}", m_problemType);
        MosdexRoot::m_problemType = m_problemType;
    }

    void setInfoValue(string t_key, string t_value){
        spdlog::info("MosdexRoot: Information recorded {} : {}", t_key, t_value);
        m_info.insert(make_pair(t_key, t_value));
    }

    const string &getJsonFileName() const {
        return jsonFileName;
    }

    explicit MosdexRoot(string t_file) : jsonFileName{t_file} {}


};


#endif //PARSER_DEV_MOSDEXROOT_H
