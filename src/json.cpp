#include "json.h"

struct jsonString {
    std::string value = "";
    std::string text() {
        return value;
    }
};

struct jsonBool {
    bool value;
    std::string text() {
        if (value) return "true";
        return "false";
    }
};

struct jsonNum {
    float value;
    std::string text() {
        return std::to_string(value);
    }
};

struct jsonNull {
    const char* value = "null";
    std::string text() {
        return value;
    }
};

struct invalidType {
    const char* value = "INVALID TYPE HERE";
    std::string text() {
        return value;
    }
};

union jsonTypePtr {
    json* obj;
    jsonArray* arr;
    jsonNull null;
    jsonNum num;
    jsonString str;
    jsonBool boolean;
    invalidType invalid;
};

struct jsonEntry {
    jsonTypePtr data;
    jsonType type;
};


