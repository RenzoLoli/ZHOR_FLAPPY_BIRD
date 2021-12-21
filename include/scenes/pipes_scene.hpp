#ifndef PIPES_SCENE_HPP
#define PIPES_SCENE_HPP

#include "ZHOR_ENGINE/scene.hpp"

#include "ZHOR_ENGINE/utils/random.hpp"
#include "ZHOR_ENGINE/utils/perlin_noise.hpp"

#include "scenes/pipe_scene.hpp"

class PipesScene : public Scene
{
private:
    std::vector<PipeScene *> pipes;
    PipeScene *lastPipe;

    float initXPipes;
    float pipeWidth;
    float pipesSeparation;
    float pipesSeparationSpace;
    float lPipes;

    float noiseValueX;
    float noiseValueY;
    PerlinNoise pNoise;

    Random rnd;

    unsigned int mode;

public:
    enum AppearMode
    {
        RANDOM,
        NOISE
    };
    PipesScene();
    ~PipesScene();

    void init(GameContext *context);
    void update(GameContext *context, double &dt);
    void event(GameContext *context, double &dt);
    void onDraw(sf::RenderTarget &target, sf::RenderStates states) const;

    void free();

    unsigned int getMode();

    double getNoise();

    PipeScene* getLastPipe();
    void setLastPipe(PipeScene* _pipe);
};

#endif