#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <iostream>

#include "window_settings.hpp"

#include "game_context.hpp"

class MainScene;
class SceneTree;

class GameController : private GameContext
{
private:
    MainScene *mainScene;
    bool windowHasCreated;

public:
    GameController(WindowSettings settings = WINDOW_SETTINGS_DEFAULT);
    ~GameController();

    bool createWindow(WindowSettings settings = WINDOW_SETTINGS_DEFAULT);

    void run();
};

#endif