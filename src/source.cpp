#include <vector>
#include <iostream>
#include <functional>
#include <string>

#include "aliaces.h"
#include "Renderer.h"
#include "InputHandler.h"

class Menu {
    Renderer renderer_;
    InputHandler input_handler_;

    int selected_ = 0;
    bool is_work_ = true;
    bool is_active_information = true;

    std::vector<MenuItem> main_menu_, main_config_;
    std::vector<MenuItem>* current_menu_ = &main_menu_;

    void init() {
        main_menu_ = {
            { "ПРОСМОТР ПРОГРЕССА", [this]() { return 0; } },
            { "ПРОСМОТР ФАЙЛОВ",    [this]() { return 0; } },
            { "КОНФИГУРАЦИЯ",       [this]() { current_menu_ = &main_config_; return 0; } },
            { "СПРАВКА",            [this]() { return 0; } },
            { "ВЫХОД",              [this]() { is_work_ = false; return 0; }}
        };

        main_config_ = {
            { "ВЫБОР ДИРЕКТОРИИ: null", [this]() { return 0; } },
            { "ВЫБОР: null",            [this]() { return 0; } },
            { (is_active_information ? "ПОДСКАЗКА: on" : "ПОДСКАЗКА: off"),          [this]() {  is_active_information = !is_active_information; return 0; } },
            { "НАЗАД",                  [this]() { current_menu_ = &main_menu_; return 0; } }
        };
    }

    void handle_event(InputHandler::Event event) {
        if (current_menu_->empty()) return;

        switch (event) {
            case InputHandler::Event::Up:
                selected_ = (selected_ - 1 + static_cast<int>(current_menu_->size())) % static_cast<int>(current_menu_->size());
                break;
            case InputHandler::Event::Down:
                selected_ = (selected_ + 1) % static_cast<int>(current_menu_->size());
                break;
            case InputHandler::Event::Enter:
                (*current_menu_)[selected_].second();
                break;
            case InputHandler::Event::Quit:
                is_work_ = false;
                break;
            case InputHandler::Event::None:
                break;
        }
    }

public:
    Menu()
        : renderer_{}
        , input_handler_(renderer_.get_notcurses())
    {
        init();
    }

    ~Menu() = default;

    int run() {
        while (is_work_) {
            if (current_menu_->empty()) {
                renderer_.clear();
                renderer_.refresh();
                break;
            }

            renderer_.draw_menu(*current_menu_, selected_, is_active_information);
            renderer_.refresh();

            handle_event(input_handler_.get_event());
        }
        return 0;
    }
};

int main() {
    try {
        Menu menu;
        return menu.run();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
}