#ifndef BIRD_SCENE_HPP
#define BIRD_SCENE_HPP

#include <cmath>
#include <map>
#include <SFML/Graphics.hpp>    

#include "scenes/pipes_scene.hpp"
#include "ZHOR_ENGINE/scene.hpp"

class BirdScene : public Scene{
public:

    Scene* _root;
    PipesScene* pipes;
    
    sf::Vector2f birdVel;
    sf::CircleShape birdCircle;

    sf::RectangleShape birdCollider;

    sf::Vector2f iPos;

    const float GRAVITY = 700;

    unsigned int points;

    BirdScene(sf::Vector2f _iPos):Scene("bird"){
        iPos = _iPos;
    }
    ~BirdScene(){}
    
    void init(GameContext *context){
        _root = this->getSceneTree()->getRoot();
        pipes = _root->findOnChild<PipesScene>("root/pipes");

        points = 0;

        float radius = 20;
        this->setPosition(iPos);

        birdVel = sf::Vector2f{
            0,
            0
        };

        birdCircle.setOrigin({radius,radius});
        birdCircle.setRotation(-45);
        birdCircle.setScale({1.5,1});
        birdCircle.setFillColor(sf::Color::Cyan);
        birdCircle.setPosition(this->getRelativeParentPos());
        birdCircle.setRadius(radius);

        birdCollider.setPosition(this->getRelativeParentPos() - birdCircle.getOrigin());
        birdCollider.setSize({
            2*birdCircle.getRadius(),
            2*birdCircle.getRadius()
        });
        birdCollider.setFillColor(sf::Color::Transparent);
        birdCollider.setOutlineColor(sf::Color::Yellow);
        birdCollider.setOutlineThickness(-1);
        birdCollider.setOrigin({0,0});

    }
    
    void update(GameContext* context, double& dt){
        
        birdVel.y += GRAVITY * dt;
        birdCircle.rotate(100*dt);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            birdVel.y = -300;
            birdCircle.setRotation(315);
        }

        this->move({
            birdVel.x * dt,
            birdVel.y * dt
        });

        sf::Vector2f _pos = this->getRelativeParentPos();
        if((_pos.y + birdCircle.getRadius() >= context->window->getSize().y) ||
           (_pos.y <= 0)){
            _root->reloadScene(context);
            return;
        }

        for(auto [name, pipeScene]: pipes->getChildren()){
            auto pipe = dynamic_cast<PipeScene*>(pipeScene);
            auto topBox = pipe->getTopBox();
            auto bottonBox = pipe->getBottonBox();

            bool _intersects = 
               topBox.intersects(getColliderRect()) 
            || bottonBox.intersects(getColliderRect());
            
            if(_intersects){
                _root->reloadScene(context);
                return;
            }

            float limitToPoint = pipe->getRelativeParentPos().x;

            if(pipe->getPointsToPass() > 0 
            && this->getRelativeParentPos().x >= pipe->getRelativeParentPos().x){
                this->addPoints(pipe->passPoints(1));
            }

        }

        updateBird(_pos);

    }
    void event(GameContext* context, double& dt){
    }

    void free(){

    }

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(birdCircle);

        target.draw(getCollider());
    }

    void updateBird(sf::Vector2f _pos){

        birdCircle.setPosition(_pos);

        birdCollider.setPosition({
            _pos.x - birdCircle.getOrigin().x,  
            _pos.y - birdCircle.getOrigin().y
        });
        birdCollider.setSize({
            2*birdCircle.getRadius(),
            2*birdCircle.getRadius()
        });
    }

    sf::FloatRect getColliderRect() const{
        return birdCollider.getGlobalBounds();
    }

    sf::RectangleShape getCollider() const{
        return birdCollider;
    }

    void addPoints(unsigned int _v){
        this->points += _v;
    }

    unsigned int getPoints(){
        return this->points;
    }

};

#endif