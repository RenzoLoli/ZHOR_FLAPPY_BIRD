#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

#include "SFML/Graphics.hpp"

#include "scene_tree.hpp"

struct GameContext{
    sf::RenderWindow*  window;
    sf::Event*         event;
    SceneTree*         sceneTree;
    sf::Clock*         deltaClock;
    double             fps;
};

#endif