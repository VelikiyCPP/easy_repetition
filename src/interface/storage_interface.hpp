#pragma once

#include <string>
#include <vector>
#include "../common/topic_entry.hpp"

class StorageInterface {
public:
    virtual ~StorageInterface() = default;

    virtual bool load() = 0;
    virtual bool save(std::string name) = 0;
    virtual bool add_entry(const topic_entry& entry) = 0;
    virtual bool exists() const = 0;

    virtual std::vector<topic_entry> get_entries() const = 0;
    virtual std::string path() const noexcept = 0;
};