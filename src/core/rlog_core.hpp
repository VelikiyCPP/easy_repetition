#pragma once

#include "../interface/output_interface.hpp"
#include "../interface/storage_interface.hpp"

#include <memory>
#include <string>

class rlog_core {
    std::unique_ptr<StorageInterface> storage_;
    // console& console_;
public:
    explicit rlog_core(std::unique_ptr<StorageInterface> storage);

    void run(std::string& command, std::string& name);

    void add(std::string&);
    void remove();
    void list();
    void log();
    void note();
    void show();
};