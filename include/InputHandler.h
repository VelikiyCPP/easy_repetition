#pragma once
#include "InputHandler.h"
#include <stdexcept>
#include <notcurses/notcurses.h>

class InputHandler {
    notcurses* nc;
    ncinput input{};

public:
    enum class Event { Up, Down, Enter, Quit, None };
    
    Event get_event();

    explicit InputHandler(notcurses*);
}; 

