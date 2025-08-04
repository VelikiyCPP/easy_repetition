#include "InputHandler.h"

InputHandler::InputHandler(notcurses* n) : nc(n) {
    if (!nc) {
        throw std::runtime_error("InputHandler: notcurses is null");
    }
}

InputHandler::Event InputHandler::get_event() {
    uint32_t ch = notcurses_get_blocking(nc, &input);

    switch (ch) {
        case NCKEY_UP:    return Event::Up;
        case NCKEY_DOWN:  return Event::Down;
        case NCKEY_ENTER:
        case '\n':
        case '\r':        return Event::Enter;
        case 'q':
        case 'Q':         return Event::Quit;
        default:          return Event::None;
    }
}