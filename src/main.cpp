// main.cpp
#include "core/rlog_core.hpp"
#include "storage/json_topic_storage.hpp"
#include <memory>
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Использование: rlog <команда> <название>\n";
        return 1;
    }

    std::string command = argv[1];
    std::string name = argv[2];

    try {
        auto storage = std::make_unique<Json_topic_storage>();
        rlog_core core(std::move(storage));

        core.run(command, name);

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная ошибка." << std::endl;
        return 1;
    }

    return 0;
}