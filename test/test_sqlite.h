//
// Created by AlanKing on 3/13/2019.
//

#ifndef PARSER_DEV_TEST_SQLITE_H
#define PARSER_DEV_TEST_SQLITE_H

#include "../src/utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int test_sqlite() {

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    /* Open database */
    rc = sqlite3_open(NULL, &db);

    if (rc) {
        spdlog::critical("Can't open database: {}", sqlite3_errmsg(db));
        return (0);
    } else {
        spdlog::debug("Opened database successfully");
    }

    /* Create SQL statement */
    string sql = "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        spdlog::warn("SQL error: {}", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        spdlog::debug("Table {} created successfully", "COMPANY");
    }
    sqlite3_close(db);
    return 0;
}
#endif //PARSER_DEV_TEST_SQLITE_H

