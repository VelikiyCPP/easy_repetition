#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include "../interface/storage_interface.hpp"

class Json_topic_storage : public StorageInterface {
    std::filesystem::path file_path_;
    nlohmann::json data_;

    std::string current_timestamp() const;
    void ensure_structure();

public:
    explicit Json_topic_storage();

    [[nodiscard]] bool load() override;
    [[nodiscard]] bool save(std::string name) override;
    [[nodiscard]] bool add_entry(const topic_entry& entry) override;
    [[nodiscard]] bool exists() const override;

    std::vector<topic_entry> get_entries() const override;
    std::string path() const noexcept override;
};