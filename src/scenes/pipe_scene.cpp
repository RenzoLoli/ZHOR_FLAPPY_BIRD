#include "scenes/pipe_scene.hpp"
#include "scenes/pipes_scene.hpp"

PipeScene::PipeScene(float _pipeWidth, float _pipeInitX, float _pipesSeparation, float _separationSpace, unsigned int _mode, unsigned int INDEX)
:Scene("pipe_" + std::to_string(INDEX)){
    this->INDEX = INDEX;
    this->iRelPipesX = _pipeInitX;
    this->pipeWidth = _pipeWidth;
    this->pipesSeparation = _pipesSeparation;

    this->separationSpace = _separationSpace;
}
PipeScene::~PipeScene(){
}
    
void PipeScene::init(GameContext *context){
    pipes = dynamic_cast<PipesScene*>(this->getParent());

    this->maxPoints = 1;
    
    recreateX();
    recreateY();

    this->setPosition({initX, 0});

    pipeHeight = context->window->getSize().y*0.9f;
    velPipe.x = -150;
    topPipe.setOrigin({pipeWidth*0.5, pipeHeight});
    topPipe.setFillColor(sf::Color::Magenta);
    topPipe.setSize({
        pipeWidth,
        pipeHeight
    });
    bottomPipe.setOrigin({ pipeWidth*0.5, pipeHeight});
    bottomPipe.setFillColor(sf::Color::Magenta);
    bottomPipe.setSize({
        pipeWidth,
        pipeHeight
    });
    updatePipes();
}
void PipeScene::update(GameContext* context, double& dt){
    
    if(this->getRelativeParentPos().x <= -this->pipeWidth){
        PipeScene* _lastPipe = pipes->getLastPipe();
        unsigned int _mode = pipes->getMode();

        this->maxPoints = 1;
        recreateY();
        float useSeparation = ((_mode == PipesScene::AppearMode::NOISE)?0:1);
        this->setPosition({
            _lastPipe->getRelativeParentPos().x + pipeWidth + (separationSpace* useSeparation),
            0
        });

        pipes->setLastPipe(this);
    }

    this->move({
        velPipe.x * dt,
        velPipe.y * dt
    });

    updatePipes();
}
void PipeScene::event(GameContext* context, double& dt){
    sf::Event e = *context->event;
}
void PipeScene::onDraw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(topPipe);
    target.draw(bottomPipe);
}
void PipeScene::free(){}
void PipeScene::updatePipes(){
    sf::Vector2f _rltPos = this->getRelativeParentPos();
    _rltPos.y += initY;
    topPipe.setPosition(_rltPos);
    _rltPos.y += pipeHeight + separationSpace;
    bottomPipe.setPosition(_rltPos);
}
sf::FloatRect PipeScene::getTopBox() const{
    sf::Vector2f _pos = this->getRelativeParentPos();
    sf::FloatRect birdBox;
    birdBox.left = _pos.x - topPipe.getOrigin().x;
    birdBox.top = _pos.y - topPipe.getOrigin().y + initY;
    birdBox.width = pipeWidth;
    birdBox.height = pipeHeight;
    return birdBox;
}
sf::FloatRect PipeScene::getBottonBox() const{
    return bottomPipe.getGlobalBounds();
}
float PipeScene::getPipeWidth(){
    return this->pipeWidth;
}
void PipeScene::setOffset(float _offset){
    this->offset = _offset;
}
float PipeScene::remap(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
void PipeScene::recreateY(){
    unsigned int _mode = pipes->getMode();
    if(_mode == PipesScene::AppearMode::RANDOM){
        this->initY = rnd.onRangeInt(0,500-separationSpace);
    }else
    if(_mode == PipesScene::AppearMode::NOISE){
        double ns = pipes->getNoise();
        this->initY = remap(ns, 0.3,0.8,0,500-separationSpace);
    }
}

void PipeScene::recreateX(){
    unsigned int _mode = pipes->getMode();
    unsigned short useSeparation = (unsigned short)((_mode == PipesScene::AppearMode::NOISE)?0:1);
    initX = iRelPipesX +
    INDEX * (pipeWidth + (this->pipesSeparation * useSeparation));
}

unsigned int PipeScene::passPoints(unsigned int _v){
        unsigned int auxPoints = this->maxPoints - _v;
        if(auxPoints < 0){
            this->maxPoints = 0;
            return this->maxPoints;
        }else if(auxPoints == 0){
            this->maxPoints = 0;
            return _v;
        }else if(auxPoints > 0){
            this->maxPoints -= _v;
            return _v;
        }
    }

unsigned int PipeScene::getPointsToPass(){
    return this->maxPoints;
}