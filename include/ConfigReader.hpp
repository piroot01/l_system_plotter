#pragma once

#define CONFIG_READER_H_
#ifdef CONFIG_READER_H_

#include <unordered_set>
#include <stdexcept>
#include <string>
#include <optional>
#include <filesystem>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

typedef std::unordered_map<std::string, std::string> ConfigMap;

class ConfigReaderException : public std::runtime_error {
public:
    explicit ConfigReaderException(const std::string& message) : std::runtime_error(message) {}

};

class ConfigReader {
public:
    ConfigReader();
    ConfigReader(const std::string& filename);
    ~ConfigReader() = default;
    ConfigReader(const ConfigReader& other);
    ConfigReader(ConfigReader&& other) noexcept;

    void ReadConfig();
    void SetConfigFilename(const std::string& filename);
    //std::string GetValue(const std::string& key) const;
    //std::unordered_set<std::string> GetValues(const std::string& key) const;
    const boost::property_tree::ptree& GetRawValues(const std::string& key) const;
    bool IsInConfig(const std::string& key) const;

    ConfigReader& operator=(const ConfigReader& other);
    ConfigReader& operator=(ConfigReader&& other) noexcept;

private:
    //void ValidateSingleNode(const boost::property_tree::ptree& node, const std::string& key) const;
    //void ValidateArrayNode(const boost::property_tree::ptree& node, const std::string& key) const;

    std::optional<std::filesystem::path> m_configFilename;
    boost::property_tree::ptree m_config;

};

#endif
