#include <filesystem>
#include <fstream>
#include <sstream>

#include "ConfigReader.hpp"

ConfigReader::ConfigReader(const ConfigMap& map) : m_configMap(map) {}

ConfigReader::ConfigReader(const ConfigReader& other)
    : m_configFilename(other.m_configFilename), m_configMap(other.m_configMap) {}

ConfigReader::ConfigReader(ConfigReader&& other) noexcept
    : m_configFilename(std::move(other.m_configFilename)), m_configMap(std::move(other.m_configMap)) {}

ConfigReader& ConfigReader::operator=(const ConfigReader& other) {
    if (this != &other) {
        m_configFilename = other.m_configFilename;
        m_configMap = other.m_configMap;
    }
    return *this;
}

ConfigReader& ConfigReader::operator=(ConfigReader&& other) noexcept {
    if (this != &other) {
        m_configFilename = std::move(other.m_configFilename);
        m_configMap = std::move(other.m_configMap);
    }
    return *this;
}

void ConfigReader::ReadConfig() {
    if (!m_configFilename.has_value())
        throw ConfigReaderException("Config filename not provided");

    if (!std::filesystem::exists(*m_configFilename))
        throw ConfigReaderException("Failed to open config file");

    std::ifstream configFile(*m_configFilename);
    std::string line;
    while (std::getline(configFile, line)) {
        RemoveComment(line);

        if (!line.empty())
            ProcessLine(line);
    }
}

void ConfigReader::RemoveComment(std::string& line) {
    size_t commentPos = line.find('#');
    if (commentPos != std::string::npos)
        line.erase(commentPos);
}

void ConfigReader::ProcessLine(const std::string& line) {
    size_t delimiterPos = line.find('=');
    if (delimiterPos != std::string::npos) {
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        Trim(key);
        Trim(value);
        StoreLine(key, value);
    }
}

void ConfigReader::Trim(std::string& str) {
    auto start = str.find_first_not_of(" \t");
    auto end = str.find_last_not_of(" \t");

    if (start != std::string::npos && end != std::string::npos)
        str = str.substr(start, end - start + 1);
    else
        str.clear();
}

void ConfigReader::SetConfigFilename(const std::string& filename) {
    m_configFilename = filename;
}

std::string ConfigReader::GetValue(const std::string& key) const {
    auto it = m_configMap.find(key);
    if (it != m_configMap.end())
        return it->second;
    else
        throw ConfigReaderException("Key \'" + key + "\' not found in config");
}

void ConfigReader::StoreLine(const std::string& key, const std::string& value) {
    auto it = m_configMap.find(key);
    if (it != m_configMap.end())
        it->second = value;
    else
        m_configMap.emplace(key, value);
}
