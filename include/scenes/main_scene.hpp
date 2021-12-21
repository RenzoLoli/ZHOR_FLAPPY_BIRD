#ifndef MAIN_SCENE_HPP
#define MAIN_SCENE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

#include "ZHOR_ENGINE/scene.hpp"

#include "scenes/bird_scene.hpp"
#include "scenes/pipes_scene.hpp"

class MainScene : public Scene{
public:

    BirdScene* bird;
    PipesScene* pipes;

    sf::Font font;

    sf::Text pointsText;
    
    MainScene();
    ~MainScene();
    
    void init(GameContext *context);
    void update(GameContext* context, double& dt);
    void event(GameContext* context, double& dt);
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void free();

    void create(GameContext *context);

};

#endif