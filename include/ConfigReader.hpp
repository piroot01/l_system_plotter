#pragma once

#define CONFIG_READER_H_
#ifdef CONFIG_READER_H_

#include <unordered_map>
#include <stdexcept>
#include <string>
#include <optional>
#include <filesystem>

typedef std::unordered_map<std::string, std::string> ConfigMap;

class ConfigReaderException : public std::runtime_error {
public:
    explicit ConfigReaderException(const std::string& message) : std::runtime_error(message) {}

};

class ConfigDefaults {
public:
    static const ConfigMap defaultValues;

private:
    static ConfigMap InitializeDefaultValues();

};

class ConfigReader {
public:
    static ConfigReader& Instance();

    void ReadConfig();
    void SetConfigFilename(const std::string& filename);
    std::string GetValue(const std::string& key) const;

private:
    ConfigReader() = default;
    ConfigReader(const ConfigReader&) = delete;
    ConfigReader(ConfigReader&&) = delete;
    ConfigReader& operator=(const ConfigReader&) = delete;
    ConfigReader& operator=(ConfigReader&&) = delete;

    void RemoveComment(std::string& line);
    void ProcessLine(const std::string& line);
    void StoreLine(const std::string& key, const std::string& value);
    void Trim(std::string& str);

    std::optional<std::filesystem::path> m_configFilename;
    ConfigMap m_configMap;

};

#endif
