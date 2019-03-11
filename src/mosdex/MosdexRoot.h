//
// Created by AlanKing on 3/8/2019.
//

#ifndef PARSER_DEV_MOSDEXROOT_H
#define PARSER_DEV_MOSDEXROOT_H

#include "../utils/utils.h"

class MosdexRoot {
private:
    string jsonFileName{};
    Document &m_document;

public:
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
