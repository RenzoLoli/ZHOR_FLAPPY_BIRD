#ifndef PIPE_SCENE_HPP
#define PIPE_SCENE_HPP

#include <SFML/Graphics.hpp>

#include "ZHOR_ENGINE/utils/random.hpp"

#include "ZHOR_ENGINE/scene.hpp"

class PipesScene;

class PipeScene : public Scene{
    PipesScene* pipes;

    float offset = 0;

    unsigned int maxPoints;

    sf::Vector2f       velPipe;
    sf::RectangleShape topPipe;
    sf::RectangleShape bottomPipe;

    float separationSpace;
    float pipesSeparation;
    float pipeWidth;
    float pipeHeight;
    float initX;
    float initY;

    int INDEX;
    float iRelPipesX;

    Random rnd;

public:
    
    PipeScene(float _pipeWidth, float _pipeInitX, float _pipesSeparation, float _separationSpace, unsigned int _mode, unsigned int INDEX);
    ~PipeScene();
    
    void init(GameContext *context);
    void update(GameContext* context, double& dt);
    void event(GameContext* context, double& dt);
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void free();

    void updatePipes();

    sf::FloatRect getTopBox() const;

    sf::FloatRect getBottonBox() const;

    float getPipeWidth();

    void setOffset(float _offset);

    float remap(float value, float istart, float istop, float ostart, float ostop);

    void recreateX();
    void recreateY();

    unsigned int passPoints(unsigned int _v);
    unsigned int getPointsToPass();

};

#endif
