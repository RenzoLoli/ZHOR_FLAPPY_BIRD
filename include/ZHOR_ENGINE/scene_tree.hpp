#ifndef SCENE_TREE_HPP
#define SCENE_TREE_HPP

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

#include "errors/string_error.hpp"

struct GameContext;

class Scene;
class GameController;

class SceneTree : public sf::Drawable
{
private:
    friend class GameController;
    Scene *mainScene;

    void init(GameContext *context);
    void update(GameContext *context, double &dt);
    void event(GameContext *context, double &dt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void free();

    void setMainScene(Scene *_scene);

public:
    SceneTree();
    ~SceneTree();

    Scene* getRoot();

    void reloadScene(GameContext* context);

    template <class SCENE>
    SCENE *findChild(std::string _path)
    {

        if (_path.empty())
            throw StringError("path erroneo");
        if (_path.front() == '/')
            _path.erase(_path.begin());
        if (_path.back() == '/')
            _path.pop_back();

        std::stringstream stream(_path);
        std::string word;

        Scene* aux = nullptr;

        std::getline(stream, word, '/');
        if (word.compare("root") == 0){
            aux = this->mainScene;
        }     
        else{
            throw StringError("path erroneo");
        }
  
        while (std::getline(stream, word, '/'))
        {
            
            if (word.empty())
                continue;
            aux = aux->getSceneChild(word);
        }
        
        return dynamic_cast<SCENE *>(aux);
    }
    Scene *findScene(std::string _path);
};

#endif