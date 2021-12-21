#include "ZHOR_ENGINE/scene_tree.hpp"

#include "ZHOR_ENGINE/game_controller.hpp"
#include "ZHOR_ENGINE/game_context.hpp"
#include "ZHOR_ENGINE/scene.hpp"

void SceneTree::init(GameContext* context){
    this->mainScene->_init(context);
}

void SceneTree::update(GameContext *context, double &dt)
{
    this->mainScene->_update(context, dt);
}
void SceneTree::event(GameContext *context, double &dt)
{
    this->mainScene->_event(context, dt);
}
void SceneTree::free()
{
    this->mainScene->_free();
}

void SceneTree::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(*this->mainScene);
}

void SceneTree::setMainScene(Scene* _scene)
{
    if (_scene == nullptr)
        throw StringError("no hay una escena principal definida");
    this->mainScene = _scene;
    this->mainScene->sceneRoot = this;
    this->mainScene->parent = nullptr;
}

SceneTree::SceneTree()
{
    this->mainScene = nullptr;
}
SceneTree::~SceneTree()
{
    free();
}

Scene *SceneTree::findScene(std::string _path)
{

    if (_path.empty())
        throw StringError("path erroneo");
    if (_path.front() == '/')
        _path.erase(_path.begin());
    if (_path.back() == '/')
        _path.pop_back();

    std::stringstream stream(_path);
    std::string word;

    Scene *aux = nullptr;

    std::getline(stream, word, '/');
    if(word.compare("root") == 0) aux = this->mainScene;
    else throw StringError("path erroneo");
    
    while (std::getline(stream, word, '/'))
    {
        if (word.empty()) continue;
        aux = aux->getSceneChild(word);
    }

    return aux;
}

void SceneTree::reloadScene(GameContext* context){
    this->mainScene->reloadScene(context);
}

Scene* SceneTree::getRoot(){
    return this->mainScene;
}