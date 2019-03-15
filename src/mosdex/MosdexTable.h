//
// Created by AlanKing on 3/14/2019.
//

#ifndef PARSER_DEV_MOSDEXTABLE_H
#define PARSER_DEV_MOSDEXTABLE_H

#include "../utils/utils.h"

class MosdexTable {
private:
    string m_tableName{};
    string m_sqlCreateString{};
    string m_sqlAddRowString{};
    vector<string> m_columnTypes{};
    vector<string> m_columnNames{};
public:
    MosdexTable(const string &t_tableName) : m_tableName(t_tableName) {
        spdlog::debug("Creating MosdexTable {}", t_tableName);
    }

    void addColumn(string t_name, string t_type) {
        m_columnNames.push_back(t_name);
        m_columnTypes.push_back(t_type);
    }

    const vector<string> &getM_columnTypes() const {
        return m_columnTypes;
    }

    const string &getM_tableName() const {
        return m_tableName;
    }

    void setM_tableName(const string &m_tableName) {
        MosdexTable::m_tableName = m_tableName;
    }

    const vector<string> &getM_columnNames() const {
        return m_columnNames;
    }


};


#endif //PARSER_DEV_MOSDEXTABLE_H
