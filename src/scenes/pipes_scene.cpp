#include "scenes/pipes_scene.hpp"

PipesScene::PipesScene() : Scene("pipes")
{
    mode = AppearMode::RANDOM;
    initXPipes = 550;
    pipeWidth = 85;
    pipesSeparation = 210;
    pipesSeparationSpace = 250;
    lPipes = 15;

    noiseValueX = rnd.onRangeDouble(0, 1);
    noiseValueY = rnd.onRangeDouble(0, 0.5);

    for (unsigned int i = 0; i < lPipes; i++)
    {
        PipeScene *nPipe = new PipeScene(pipeWidth, initXPipes, pipesSeparation, pipesSeparationSpace, mode, i);
        pipes.push_back(nPipe);
        this->addChild(nPipe);
    }
}
PipesScene::~PipesScene()
{
    for (auto _pipe : pipes)
    {
        delete _pipe;
    }
}

void PipesScene::init(GameContext *context)
{
    lastPipe = pipes[lPipes - 1];
}

void PipesScene::update(GameContext *context, double &dt)
{
}
void PipesScene::event(GameContext *context, double &dt){

}
void PipesScene::onDraw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto pipe : pipes)
    {
        target.draw(*pipe);
    }
}

void PipesScene::free()
{
}

unsigned int PipesScene::getMode()
{
    return mode;
}

double PipesScene::getNoise()
{
    double ns = pNoise.noise(noiseValueX, noiseValueY, 0);

    noiseValueX += 0.05;
    noiseValueY += 0.05;

    return ns;
}

PipeScene* PipesScene::getLastPipe(){
    return lastPipe;
}

void PipesScene::setLastPipe(PipeScene* _pipe){
    lastPipe = _pipe;
}