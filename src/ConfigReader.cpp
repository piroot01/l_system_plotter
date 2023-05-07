#include <filesystem>
#include <fstream>
#include <sstream>

#include "ConfigReader.hpp"

ConfigReader::ConfigReader(const std::string& filename) : m_configFilename(filename) {}

ConfigReader::ConfigReader(const ConfigReader& other)
    : m_configFilename(other.m_configFilename), m_config(other.m_config) {}

ConfigReader::ConfigReader(ConfigReader&& other) noexcept
    : m_configFilename(std::move(other.m_configFilename)), m_config(std::move(other.m_config)) {}

ConfigReader& ConfigReader::operator=(const ConfigReader& other) {
    if (this != &other) {
        m_configFilename = other.m_configFilename;
        m_config = other.m_config;
    }
    return *this;
}

ConfigReader& ConfigReader::operator=(ConfigReader&& other) noexcept {
    if (this != &other) {
        m_configFilename = std::move(other.m_configFilename);
        m_config = std::move(other.m_config);
    }
    return *this;
}

void ConfigReader::ReadConfig() {
    if (!m_configFilename.has_value())
        throw ConfigReaderException("Config filename not provided");

    if (!std::filesystem::exists(*m_configFilename))
        throw ConfigReaderException("Failed to open config file");

    try {
        boost::property_tree::read_json(m_configFilename->string(), m_config);
    } catch (const boost::property_tree::json_parser::json_parser_error& e) {
        throw ConfigReaderException(std::string("Error parsing JSON: ") + e.what());
    }
}

void ConfigReader::SetConfigFilename(const std::string& filename) {
    m_configFilename = filename;
}
/*
std::string ConfigReader::GetValue(const std::string& key) const {
    auto& node = m_config.get_child(key);
    ValidateSingleNode(node, key);
    return node.get_value<std::string>();
}

std::unordered_set<std::string> ConfigReader::GetValues(const std::string& key) const {
    std::unordered_set<std::string> values;
    auto& node = m_config.get_child(key);

    if (node.empty()) {
        values.insert(node.get_value<std::string>());
    } else {
        ValidateArrayNode(node, key);
        for (const auto& [key, value] : node)
            values.insert(value.get_value<std::string>());
    }

    return values;
}
*/
const boost::property_tree::ptree& ConfigReader::GetRawValues(const std::string& key) const {
    return m_config.get_child(key);
}
/*
void ConfigReader::ValidateSingleNode(const boost::property_tree::ptree& node, const std::string& key) const {
    if (node.empty())
        return;

    throw ConfigReaderException("Error: The value for key '" + key + "' is not a single value.");
}

void ConfigReader::ValidateArrayNode(const boost::property_tree::ptree& node, const std::string& key) const {
    if (!node.empty() && node.begin()->second.empty())
        return;

    throw ConfigReaderException("Error: The value for key '" + key + "' is not an array.");
}
*/
bool ConfigReader::IsInConfig(const std::string& key) const {
    auto child = m_config.get_child_optional(key);
    return static_cast<bool>(child);
}
