#pragma once

#include <map>
#include <string>

union jsonTypePtr;
struct jsonEntry;

struct invalidType;

struct jsonString;

struct jsonBool;

struct jsonNum;

struct jsonNull;

class jsonArray {
    public:
    private:
};

class json {
    public:
        template<typename type>
        int push_back(std::string, type);

        bool contains(const std::string&);
        
        std::string text();
    private:
        int insert(std::string, jsonEntry);

        std::map<std::string, jsonEntry> jsonObj;
};

enum jsonType {
    JSONNUM = 0,
    JSON = 1,
    JSONARRAY = 2,
    JSONBOOL = 3,
    JSONNULL = 4,
    JSONSTRING = 5,
    INVALIDTYPE = 6,
};
