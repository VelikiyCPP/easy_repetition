#pragma once
#include <notcurses/notcurses.h>
#include <vector>
#include <stdexcept>
#include "aliaces.h"

class Renderer {
    notcurses* nc = nullptr;
    ncplane* plane = nullptr;

public:
    Renderer();
    ~Renderer();

    void clear();
    void draw_menu(const std::vector<MenuItem>&, int, bool);
    void refresh();

    notcurses* get_notcurses() const;
};