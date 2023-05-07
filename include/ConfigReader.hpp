#pragma once

#define CONFIG_READER_H_
#ifdef CONFIG_READER_H_

#include <unordered_map>
#include <stdexcept>
#include <string>
#include <optional>
#include <filesystem>

#include "ConfigDefaults.hpp"

typedef std::unordered_map<std::string, std::string> ConfigMap;

class ConfigReaderException : public std::runtime_error {
public:
    explicit ConfigReaderException(const std::string& message) : std::runtime_error(message) {}

};

class ConfigReader {
public:
    ConfigReader(const ConfigMap& map = ConfigDefaults::Empty::values());
    ~ConfigReader() = default;
    ConfigReader(const ConfigReader& other);
    ConfigReader(ConfigReader&& other) noexcept;

    void ReadConfig();
    void SetConfigFilename(const std::string& filename);
    std::string GetValue(const std::string& key) const;

    ConfigReader& operator=(const ConfigReader& other);
    ConfigReader& operator=(ConfigReader&& other) noexcept;

private:
    void RemoveComment(std::string& line);
    void ProcessLine(const std::string& line);
    void StoreLine(const std::string& key, const std::string& value);
    void Trim(std::string& str);

    std::optional<std::filesystem::path> m_configFilename;
    ConfigMap m_configMap;

};

#endif
