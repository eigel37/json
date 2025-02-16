#pragma once

#include <map>
#include <string>

union jsonTypePtr;
struct jsonEntry;

enum jsonType {
    JSONNUM,
    JSON,
    JSONARRAY,
    JSONBOOL,
    JSONNULL,
    JSONSTRING,
    INVALIDTYPE,
};

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
        std::map<std::string, jsonEntry> jsonObj;
};
