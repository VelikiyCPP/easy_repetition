#include "Renderer.h"

Renderer::Renderer() {
    notcurses_options opts{};
    nc = notcurses_init(&opts, nullptr);

    if (!nc) {
        throw std::runtime_error("Renderer: не удалось инициализировать notcurses");
    }

    plane = notcurses_stdplane(nc);
    if (!plane) {
        notcurses_stop(nc);
        throw std::runtime_error("Renderer: не удалось получить стандартную плоскость");
    }
}

Renderer::~Renderer() {
    if (nc) {
        notcurses_stop(nc);
    }
}

void Renderer::clear() {
    if (plane) ncplane_erase(plane);
}

void Renderer::draw_menu(const std::vector<MenuItem>& items, int selected, bool is_active = true) {
    const int last_index = static_cast<int>(items.size()) - 1;

    if (items.empty()) {
        return;
    }

    if (selected < 0) {
        selected = 0;
    }

    if (selected > last_index) { 
        selected = last_index;
    }

    clear();

    unsigned int rows, cols;
    ncplane_dim_yx(plane, &rows, &cols);

    for (std::size_t i = 0; i < items.size(); ++i) {
        const std::string& text = items[i].first;
        const char* prefix = (static_cast<int>(i) == selected) ? "► " : "  ";

        constexpr int TOP_MARGIN = 2;
        int y = static_cast<int>(i) + TOP_MARGIN;

        if (ncplane_putstr_yx(plane, y, 2, prefix) < 0) {
            // логгировать ошибку или игнорировать — зависит от политики
        }

        if (static_cast<int>(i) == selected) {
            ncplane_set_fg_rgb8(plane, 0, 255, 0);
        }

        ncplane_putstr(plane, text.c_str());
        if (static_cast<int>(i) == selected) {
            ncplane_set_fg_default(plane);
        }
    }

    if(is_active) {
        constexpr const char* PROMPT = "↑↓ — навигация, Enter — выбрать";
        constexpr int MENU_INDENT = 2;
        constexpr int PROMPT_VERTICAL_OFFSET = 3;

        int prompt_y = static_cast<int>(items.size()) + PROMPT_VERTICAL_OFFSET;
        ncplane_putstr_yx(plane, prompt_y, MENU_INDENT, PROMPT);
    }
}

void Renderer::refresh() {
    if (nc) notcurses_render(nc);
}

notcurses* Renderer::get_notcurses() const { return nc; }