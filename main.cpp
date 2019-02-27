//
// Created by kingaj on 2/27/19.
//

#include <cstdio>
#include <iostream>
#include <exception>

#include <rapidjson/filereadstream.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>

using namespace rapidjson;


#define TEST_JSON_FILE "../json/inventory.json"

int main() {

    try {
        FILE *fp = fopen(TEST_JSON_FILE, "r");
        if (! fp ){
            std::cerr << "File " << TEST_JSON_FILE << " not found" << std::endl;
            throw std::exception();
        }
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));

        Document d;
        d.ParseStream(is);
        fclose(fp);

        StringBuffer buffer;

        buffer.Clear();

        PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);


        std::cout << buffer.GetString() << std::endl;
        return 0;
    }
    catch(std::exception &e) {
        return 1;
    }
}