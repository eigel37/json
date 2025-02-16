#include "json.h"
#include <type_traits>

struct jsonString {
    std::string value = "";
    const std::string text() {
        return value;
    }
};

struct jsonBool {
    bool value;
    const std::string text() {
        if (value) return "true";
        return "false";
    }
};

struct jsonNum {
    long double value;
    const std::string text() {
        return std::to_string(value);
    }
};

struct jsonNull {
    static constexpr char* value = "null";
    static const std::string text() {
        return value;
    }
};

struct invalidType {
    static constexpr char* value = "INVALID TYPE HERE";
    static const std::string text() {
        return value;
    }
};

union jsonTypePtr {
    json* obj;
    jsonArray* arr;
    jsonNull* null;
    jsonNum* num;
    jsonString* str;
    jsonBool* boolean;
    invalidType* invalid;
};

struct jsonEntry {
    jsonTypePtr data;
    jsonType type;
    ~jsonEntry() {
        switch (type) {
            case JSON:
                delete data.obj;
            case JSONNULL:
                delete data.null;
            case JSONSTRING:
                delete data.str;
            case JSONNUM:
                delete data.num;
            case JSONBOOL:
                delete data.boolean;
            case JSONARRAY:
                delete data.arr;
            case INVALIDTYPE:
                delete data.invalid;
            default:
                return;
        }
    }
};


template<typename type>
int json::push_back(std::string key, type value) {
    jsonEntry newEntry;

    if (std::is_same_v<bool, type>) {
       newEntry.type = JSONBOOL;
       newEntry.data.boolean = new jsonBool{value};
    }
    else if (std::is_same_v<char, type> ||
             std::is_same_v<char16_t, type> ||
             std::is_same_v<char32_t, type> ||
             std::is_same_v<std::string, type> ||
             std::is_same_v<char*, type>
             ) {
        std::string str(value);
        if (str == "null") {
           newEntry.type = JSONNULL;
           newEntry.data.null = new jsonNull{};
        }
        else {
            newEntry.type = JSONSTRING;
            newEntry.data.str = new jsonString{str};
        }
    }
    else if (std::is_arithmetic_v<type>) {
        newEntry.type = JSONNUM;
        newEntry.data.num = new jsonNum{(long double) value};
    }
    else if (std::is_same_v<json, type>) {
        newEntry.type = JSON;
        newEntry.data.obj = &value;
    }
    else if (std::is_same_v<jsonArray, type>) {
        newEntry.type = JSONARRAY;
        newEntry.data.arr = &value;
    }
    else {
        newEntry.type = INVALIDTYPE;
        newEntry.data.invalid = new invalidType{};
    }
    return insert(key, newEntry);
}

int json::insert(std::string key, jsonEntry value) {
    if (value.type == INVALIDTYPE) return 0;
    if (json::jsonObj.contains(key)) return 0;
    json::jsonObj[key] = value;
    return 1;
}
