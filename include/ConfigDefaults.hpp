#pragma once

#ifndef CONFIG_DEFAULTS_H_
#define CONFIG_DEFAULTS_H_

#include <unordered_map>
#include <string>

namespace ConfigDefaults {

typedef std::unordered_map<std::string, std::string> ConfigMap;

struct Empty {
    static const ConfigMap& values() {
        static const ConfigMap instance = {};
        return instance;
    }
};

struct Example {
    static const ConfigMap& values() {
        static const ConfigMap instance = {
            {"line", "1"},
            {"color", "black"}
        };
        return instance;
    }
};

}

#endif
