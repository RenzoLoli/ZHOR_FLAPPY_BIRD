#ifndef WINDOW_SETTINGS_HPP
#define WINDOW_SETTINGS_HPP

#include <string>
#include <cstdint>

#include "SFML/Graphics.hpp"

struct WindowSettings{
    sf::Vector2i windowSize;
    sf::Vector2f windowPos;

    std::string title;
    uint16_t style;
    uint16_t fps;

    sf::ContextSettings contextSettings;
};

const WindowSettings WINDOW_SETTINGS_DEFAULT{
    sf::Vector2i{
        500,
        500
    },
    sf::Vector2f{
        .5,
        .5
    },
    "game",
    sf::Style::Close,
    120,
    sf::ContextSettings{}
};


#endif