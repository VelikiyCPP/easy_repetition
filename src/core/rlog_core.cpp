#include "rlog_core.hpp"
#include <iostream>
#include <stdexcept>

rlog_core::rlog_core(std::unique_ptr<StorageInterface> storage)
    : storage_(std::move(storage))
{
    if (!storage_) {
        throw std::invalid_argument("Storage не может быть null");
    }
}

void rlog_core::run(std::string& command, std::string& name) {
    if(command == "add") {
        add(name);
    }
}

void rlog_core::add(std::string& name) {
    if (!storage_->load()) {
        std::cerr << "Ошибка загрузки: " << storage_->path() << "\n";
        return;
    }

    topic_entry entry;
    entry.mastery = 0;
    entry.note  = "0";
    entry.path  = "0";
    entry.topic = name + ".json";

    storage_->add_entry(entry);

    if (!storage_->save(name + ".json")) {
        std::cerr << "Не удалось сохранить.\n";
        return;
    }

    std::cout << "Запись добавлена в " << storage_->path() << "\n";
}

void rlog_core::show() {
    if (!storage_->load()) {
        std::cerr << "Не удалось загрузить журнал.\n";
        return;
    }

    auto entries = storage_->get_entries();
    if (entries.empty()) {
        std::cout << "Записей нет.\n";
        return;
    }

    for (const auto& e : entries) {
        std::cout << "[" << e.timestamp << "] "
                  << e.topic << " | "
                  << e.mastery << "% | "
                  << e.path << "\n"
                  << "  → " << e.note << "\n\n";
    }
}

void rlog_core::list() {
    std::cout << "Журнал: " << storage_->path() << " → "
              << (storage_->exists() ? "существует" : "не существует")
              << "\n";
}

void rlog_core::remove() {
    std::cerr << "remove: не реализовано\n";
}

void rlog_core::log() {
    std::cerr << "log: не реализовано\n";
}

void rlog_core::note() {
    std::cerr << "note: не реализовано\n";
}
