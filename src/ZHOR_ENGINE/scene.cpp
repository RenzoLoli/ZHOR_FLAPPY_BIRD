#include "ZHOR_ENGINE/scene.hpp"

#include "ZHOR_ENGINE/game_context.hpp"
#include "ZHOR_ENGINE/scene_tree.hpp"

Scene::Scene(std::string _sceneName) : sceneName(_sceneName) {
    
    this->setOrigin({0,0});
    this->setPosition({0,0});
}

std::string Scene::getName(){return this->sceneName;}

void Scene::reloadScene(GameContext *context){
    _init(context);
}

void Scene::_init(GameContext *context)
{
    for (auto [_, child] : sceneChildren)
    {
        child->_init(context);
    }
    this->init(context);
}

void Scene::_update(GameContext *context, double &dt)
{
    for (auto [_, child] : sceneChildren)
    {
        child->_update(context, dt);
    }
    this->update(context, dt);
}

void Scene::_event(GameContext *context, double &dt)
{
    for (auto [_, child] : sceneChildren)
    {
        child->_event(context, dt);
    }
    this->event(context, dt);
}

void Scene::_free()
{
    for (auto [_, child] : sceneChildren)
    {
        child->_free();
    }
    this->free();
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::CircleShape _point;
    _point.setOrigin({5,5});
    _point.setPosition(this->getRelativeParentPos());
    _point.setFillColor(sf::Color::Red);
    _point.setRadius(5);
    onDraw(target,states);

    target.draw(_point);
}

void Scene::onDraw(sf::RenderTarget& target, sf::RenderStates states) const{
    
}

SceneTree* Scene::getSceneTree(){
    return this->sceneRoot;
}

Scene* Scene::getParent(){
    return this->parent;
}

sf::Vector2f Scene::getRelativeParentPos() const{
    sf::Vector2f _rltPos = (this->parent == nullptr)?(sf::Vector2f{0,0}):(this->parent->getPosition());
    return this->getPosition() + _rltPos;
}

std::map<std::string, Scene *>& Scene::getChildren(){
    return this->sceneChildren;
}

void Scene::addChild(Scene *nScene)
{

    if (nScene == nullptr)
        throw StringError("insertar escena hija fue NULL");

    nScene->sceneRoot = this->sceneRoot;
    nScene->parent = this;
    this->sceneChildren.insert(
        std::make_pair(nScene->sceneName, nScene)
    );
}

void Scene::eraseChild(std::string _sceneName)
{
    if (this->sceneChildren.count(_sceneName) > 0)
    {
        Scene *&dScene = this->sceneChildren[_sceneName];
        this->sceneChildren.erase(_sceneName);
    }
}

template <class SCENE>
SCENE* Scene::getChild(std::string _sceneName)
{
    if (this->sceneChildren.count(_sceneName) > 0)
    {
        return dynamic_cast<SCENE *>(this->sceneChildren[_sceneName]);
    }

    throw StringError("no existe la escena hija");
}

Scene* Scene::getSceneChild(std::string _sceneName)
{
    if (this->sceneChildren.count(_sceneName) > 0)
    {
        return this->sceneChildren[_sceneName];
    }

    throw StringError("no existe la escena hija");
}