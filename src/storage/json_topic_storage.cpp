// storage/json_topic_storage.cpp
#include "json_topic_storage.hpp"
#include <fstream>
#include <iomanip>

#include <chrono>
#include <format>
#include <iostream>

// время в формате ISO 8601 (UTC) "2025-04-05T12:30:45Z"
std::string Json_topic_storage::current_timestamp() const {
    return std::format("{:%FT%TZ}", std::chrono::utc_clock::now());
}

void Json_topic_storage::ensure_structure() {
    if (!data_.contains("entries")) {
        data_["entries"] = nlohmann::json::array();
    }
}

Json_topic_storage::Json_topic_storage()
    : file_path_(""), data_({})
{
}

bool Json_topic_storage::load() {
    const std::string settings_file = "setting/setting.json";

    if (!std::filesystem::exists(settings_file)) {
        std::cerr << "Settings file not found: " << settings_file << "\n";
        return false;
    }

    std::ifstream file(settings_file, std::ios::in | std::ios::binary);
    file.exceptions(std::ios::failbit | std::ios::badbit);

    try {
        nlohmann::json j;
        file >> j;

        if (!j.contains("setting") || !j["setting"].contains("path")) {
            std::cerr << "Missing 'setting.path' in JSON\n";
            return false;
        }

        auto& path_val = j["setting"]["path"];
        if (!path_val.is_string()) {
            std::cerr << "'setting.path' is not a string\n";
            return false;
        }

        file_path_ = std::string(path_val);

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Error reading settings: " << e.what() << "\n";
        return false;
    }
}

bool Json_topic_storage::add_entry(const topic_entry& entry) {
    ensure_structure();

    nlohmann::json j;
    j["path"] = entry.path;
    j["topic"] = entry.topic;
    j["mastery"] = entry.mastery;
    j["note"] = entry.note;
    j["timestamp"] = entry.timestamp.empty() ? current_timestamp() : entry.timestamp;

    data_["entries"].push_back(j);

    std::cout << entry.topic << std::endl;

    return true; // TODO: позже вернуться сюда
}

// Получить все записи
std::vector<topic_entry> Json_topic_storage::get_entries() const {
    std::vector<topic_entry> entries;

    if (!data_.contains("entries")) {
        return entries;
    }

    for (const auto& item : data_["entries"]) {
        topic_entry entry;
        entry.path = item.value("path", "unknown");
        entry.topic = item.value("topic", "unknown");
        entry.mastery = item.value("mastery", 0);
        entry.note = item.value("note", "");
        entry.timestamp = item.value("timestamp", "unknown");
        entries.push_back(entry);
    }

    return entries;
}

bool Json_topic_storage::save(std::string name) {
    ensure_structure();
    
    try {
        std::ofstream file(file_path_ / name, std::ios::out | std::ios::binary);
        file.exceptions(std::ios::failbit | std::ios::badbit);
        file << std::setw(2) << data_ << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << std::format("Save error: {}\n", e.what());
        return false;
    }
}

// Проверить, существует ли файл
bool Json_topic_storage::exists() const {
    return std::filesystem::exists(file_path_);
}

// Вернуть путь к файлу как строку
std::string Json_topic_storage::path() const noexcept {
    return file_path_;
}