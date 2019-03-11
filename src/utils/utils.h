//
// Created by kingaj on 3/5/19.
//

#ifndef PARSER_DEV_UTILS_H
#define PARSER_DEV_UTILS_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <cstdio>
#include <iostream>
#include <exception>

#include <rapidjson/filereadstream.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

using namespace rapidjson;
using namespace spdlog;
using namespace std;

static const char *kTypeNames[] =
        {"Null", "False", "True", "Object", "Array", "String", "Number"};


#endif //PARSER_DEV_UTILS_H
